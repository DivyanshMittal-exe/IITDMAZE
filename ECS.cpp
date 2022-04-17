#pragma once

#include "ECS.h"

void Manager::update()
{
    for (auto &c : entities)
    {
        c->update();
    }
}
void Manager::draw()
{
    for (auto &c : entities)
    {
        c->draw();
    }
}

void Manager::refresh()
{
    for (auto i = entities.begin(); i != entities.end(); i++)
    {
        if ((*i)->isActive() == false)
        {
            entities.erase(i);
        }
    }

    for (int j = 0; j < 32; j++)
    {
        for (auto i = groups[j].begin(); i != groups[j].end(); i++)
        {
            if ((*i)->isActive() == false || (*i)->hasGroup(j) == false)
            {
                groups[j].erase(i);
            }
        }
    }
}

void Manager::addGroup(Entity *ent, Group g)
{
    groups[g].emplace_back(ent);
}

std::vector<Entity *> &Manager::getGroup(Group g)
{
    return groups[g];
}

Entity &Manager::addEntity()
{
    Entity *newEnt = new Entity(*this);
    // std::unique_ptr<Entity> newEntPtr(newEnt);
    // entities.emplace_back(std::move(newEntPtr));
    entities.emplace_back(newEnt);
    return *newEnt;
}