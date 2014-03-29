#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Entity.hpp"
#include "LuaState.hpp"
#include <vector>

class CollisionHandler
{
    public:
        CollisionHandler(LuaState& lua);
        ~CollisionHandler();

        void AddEntity(Entity& entity) { Collidables.push_back(&entity); }

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
