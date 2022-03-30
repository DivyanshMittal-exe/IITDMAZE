#ifndef ECS_H
#define ECS_H

#include <bits/stdc++.h>


class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponenetTypeID(){
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponenetTypeID() noexcept
{
    static ComponentID typeID = getComponenetTypeID();
    return typeID();
}

constexpr std::size_t maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*,maxComponents>;

class Component{
    public:
        Entity* entity;
        virtual void init(){}
        virtual void update(){}
        virtual void draw(){}

};

class Entity{
    private:
        bool active = true;
        std::vector<std::unique_ptr<Component>> components;

        ComponentArray componentArray;
        ComponentBitset componentBitset;

    public:
        void update(){
            for(auto&c: components) {
                c->update();
            }
            for(auto&c: components) {
                c->draw();
            }
        }
        void draw(){}

        bool isActive() const { return active;}
        bool destroy() { active = false;}

        template <typename T> bool hasComponent() const {
            return componentBitset[getComponenetTypeID<T>()];
        }

        template <typename T,typename...  TArgs>

        T& addComponent(TArgs&&... margs){
            T* c(new T(std::forward<TArgs>(margs)...));
            c->entity = this;
            std::unique_ptr<Component> uPtr{c}
            components.emplace_back(std::move(uPtr));

            componentArray[getComponenetTypeID<T>()] = c;
            componentBitset[getComponenetTypeID<T>()] = true;

            c->init();
            return *c;
        }

        template <typename T> T& getComponenet() const{
            auto ptr(componentArray[getComponenetTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }

};


class Manager{

private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update(){
        for(auto&c: entities){
            c->update();
        }
    }
    void draw(){
        for(auto&c: entities){
            c->draw();
        }
    }

    void refresh(){ 
        
    }
}




#endif