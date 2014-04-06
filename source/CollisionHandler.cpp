#include "CollisionHandler.hpp"
#include <iostream>

const int CollisionHandler::LuaKeyBase = 0xF00D;

CollisionHandler::CollisionHandler(LuaState& lua)
    : _lua(lua)
    , _quadtree(4)
{
    Rectangle area(SDL2TK::Vector2F(0, 0), SDL2TK::Vector2F(16, 16));
    _quadtree.SetArea(area);
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::CheckCollisions()
{
    if (_callback.HasReference())
    {
        for (auto i : _entities) _quadtree.Add(*i);

        auto size = _entities.size();
        for (decltype(size) i = 0; i < size; i++)
        {
            for (decltype(size) j = i + 1; j < size; j++)
            {
                if (_entities[i]->Overlaps(*_entities[j]))
                {
                    auto state = _lua.Raw();
                    _callback.Push();
                    lua_pushlightuserdata(state, _entities[i]);
                    lua_pushlightuserdata(state, _entities[j]);
                    _lua.Call(2, 0);
                }
            }
        }

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
