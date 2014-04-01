#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Entity.hpp"
#include "LuaState.hpp"
#include "LuaReference.hpp"
#include <vector>
#include <algorithm>

class CollisionHandler
{
    public:
        CollisionHandler(LuaState& lua);
        ~CollisionHandler();

        void AddEntity(Entity& entity) { _entities.push_back(&entity); }
        void RemoveEntity(Entity& entity)
        {
            auto i = std::find(_entities.begin(), _entities.end(), &entity);

            if (i != _entities.end())
                _entities.erase(i);
        }

        void CheckCollisions();
    protected:
    private:
        std::vector<Entity*> _entities;
        LuaState& _lua;
        LuaReference _callback;

        static const int LuaKeyBase;
        static CollisionHandler& FromLua(lua_State* state);
        static int SetCollisionCallback(lua_State* state);
};

#endif
