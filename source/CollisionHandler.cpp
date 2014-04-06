#include "CollisionHandler.hpp"
#include <iostream>

const int CollisionHandler::LuaKeyBase = 0xF00D;

CollisionHandler::CollisionHandler(LuaState& lua)
    : _lua(lua)
    , _quadtree(4)
{
    Rectangle area(SDL2TK::Vector2F(0, 0), SDL2TK::Vector2F(64, 64));
    _quadtree.SetArea(area);
    _quadtree.Clear();
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::CheckCollisions(bool debugDump)
{
    if (_callback.HasReference())
    {
        for (auto i : _entities) _quadtree.Add(*i);

        for (auto i : _entities)
        {
            const std::vector<Entity*>& collisions =
                _quadtree.GetCollisions(*i);

            for (auto j : collisions)
            {
                auto state = _lua.Raw();
                _callback.Push();
                lua_pushlightuserdata(state, i);
                lua_pushlightuserdata(state, j);
                _lua.Call(2, 0);
            }
        }

        if (debugDump)
            _quadtree.DebugDump(std::cout);

        _quadtree.Clear();
    }
}

CollisionHandler& CollisionHandler::FromLua(lua_State* state)
{
    auto raw = LuaState::GetUserData(state, (void*)&LuaKeyBase);
    return *reinterpret_cast<CollisionHandler*>(raw);
}

int CollisionHandler::SetCollisionCallback(lua_State* state)
{
    auto argc = lua_gettop(state);
    if (argc > 0 && lua_isfunction(state, 1))
    {
        lua_settop(state, 1);
        CollisionHandler& ch = CollisionHandler::FromLua(state);
        ch._callback = LuaReference(state);
    }

    return 0;
}
