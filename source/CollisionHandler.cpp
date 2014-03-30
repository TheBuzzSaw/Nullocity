#include "CollisionHandler.hpp"
#include <iostream>

const int CollisionHandler::LuaKeyBase = 0xF00D;

CollisionHandler::CollisionHandler(LuaState& lua)
    : _lua(lua)
    , _luaCollisionCallback(LUA_NOREF)
{
    _lua.SetUserData((void*)LuaKeyBase, this);
    _lua.AddFunction(SetCollisionCallback, "SetCollisionCallback");
}

CollisionHandler::~CollisionHandler()
{
    _lua.ClearReference(_luaCollisionCallback);
}

void CollisionHandler::CheckCollisions()
{
    if (_luaCollisionCallback != LUA_NOREF)
    {
        auto size = _entities.size();
        for (decltype(size) i = 0; i < size; i++)
        {
            for (decltype(size) j = i + 1; j < size; j++)
            {
                SDL2TK::Vector2F object1Pos = _entities[i]->Position();
                SDL2TK::Vector2F object2Pos = _entities[j]->Position();
                float object1Rad = _entities[i]->Radius();
                float object2Rad = _entities[j]->Radius();
                float minimumDistance = object1Rad + object2Rad;
                minimumDistance *= minimumDistance;
                float distance = (object1Pos - object2Pos).LengthSquared()
                    - minimumDistance;

                if (distance <= 0)
                {
                    auto state = _lua.Raw();
                    _lua.PushReference(_luaCollisionCallback);
                    lua_pushlightuserdata(state, _entities[i]);
                    lua_pushlightuserdata(state, _entities[j]);
                    auto status = lua_pcall(state, 2, 0, 0);
                    if (status) _lua.ReportErrors();
                }
            }
        }
    }
}

CollisionHandler& CollisionHandler::FromLua(lua_State* state)
{
    auto raw = LuaState::GetUserData(state, (void*)LuaKeyBase);
    return *reinterpret_cast<CollisionHandler*>(raw);
}

int CollisionHandler::SetCollisionCallback(lua_State* state)
{
    auto argc = lua_gettop(state);
    if (argc > 0 && lua_isfunction(state, 1))
    {
        lua_settop(state, 1);
        CollisionHandler& ch = CollisionHandler::FromLua(state);
        ch._luaCollisionCallback = ch._lua.GetReference();
    }

    return 0;
}
