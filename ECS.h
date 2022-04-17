#pragma once

#ifndef ECS_H
#define ECS_H

#include <bits/stdc++.h>
// #include <array>

using ComponentID = std::size_t;
using Group = std::size_t;

class Component;
class Entity;

class Manager
{
private:
    // std::vector<std::unique_ptr<Entity>> entities;
    std::vector<Entity *> entities;
    std::vector<Entity *> groups[32];

public:
    void update();
    void draw();
    void refresh();
    void addGroup(Entity *ent, Group g);
    std::vector<Entity *> &getGroup(Group g);
    Entity &addEntity();
};

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

using ComponentBitset = std::bitset<32>;
using GroupBitset = std::bitset<32>;
using ComponentArray = std::array<Component *, 32>;

class Component
{
public:
    Entity *entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
};

class Entity
{
private:
    Manager &manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitset componentBitset;
    GroupBitset groupBitset;

public:
    Entity(Manager &m) : manager(m) {}
    void update()
    {
        for (auto &c : components)
        {
            c->update();
        }
    }
    void draw()
    {
        for (auto &c : components)
        {
            c->draw();
        }
    }

    bool isActive() const { return active; }
    bool destroy() { active = false; }

    bool hasGroup(Group g)
    {
        return groupBitset[g];
    }

    void addGroup(Group g)
    {
        groupBitset[g] = true;
        manager.addGroup(this, g);
    }

    void delGroup(Group g)
    {
        groupBitset[g] = false;
    }

    template <typename T>
    bool hasComponent() const
    {
        return componentBitset[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>

    T &addComponent(TArgs &&...margs)
    {
        T *c(new T(std::forward<TArgs>(margs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template <typename T>
    T &getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }
};

#endif