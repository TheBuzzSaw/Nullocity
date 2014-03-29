#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Entity.hpp"
#include "LuaState.hpp"
#include <vector>
#include <algorithm>

class CollisionHandler
{
    public:
        CollisionHandler(LuaState& lua);
        ~CollisionHandler();

        void AddEntity(Entity& entity) { Collidables.push_back(&entity); }
        void RemoveEntity(Entity& entity)
        {
            auto i = std::find(Collidables.begin(), Collidables.end(), &entity);

            if (i != Collidables.end())
                Collidables.erase(i);
        }

        void CheckCollisions();
    protected:
    private:
        std::vector<Entity*> Collidables;
        LuaState& _lua;
        int _luaCollisionCallback;

        static const int LuaKeyBase;
        static CollisionHandler& FromLua(lua_State* state);
        static int SetCollisionCallback(lua_State* state);
};

#endif
