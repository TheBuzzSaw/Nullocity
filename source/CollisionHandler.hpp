#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Entity.hpp"
#include "LuaState.hpp"
#include "LuaReference.hpp"
#include "Quadtree.hpp"
#include <vector>

class CollisionHandler
{
    public:
        CollisionHandler(LuaState& lua);
        ~CollisionHandler();

        void InitializeLua();

        void AddEntity(Entity& entity);
        void RemoveEntity(Entity& entity);

        void DestroyState()
        {
            _quadtree.Clear();
            _callback = LuaReference();
        }

        void CheckCollisions(bool debugDump);

    protected:
    private:
        LuaState& _lua;
        LuaReference _callback;
        std::vector<Entity*> _entities;
        Quadtree _quadtree;

        static const int LuaKeyBase;
        static CollisionHandler& FromLua(lua_State* state);
        static int SetCollisionCallback(lua_State* state);
};

#endif
