#include "LuaReference.hpp"
#include <algorithm>

LuaReference::LuaReference(lua_State* state)
    : _state(state)
    , _reference(LUA_NOREF)
{
    if (_state) _reference = luaL_ref(_state, LUA_REGISTRYINDEX);
}

LuaReference::LuaReference(LuaReference&& other)
    : _state(other._state)
    , _reference(other._reference)
{
    other._state = nullptr;
    other._reference = LUA_NOREF;
}

LuaReference::~LuaReference()
{
    if (_state) luaL_unref(_state, LUA_REGISTRYINDEX, _reference);
}

LuaReference& LuaReference::operator=(LuaReference&& other)
{
    if (this != &other)
    {
        std::swap(_state, other._state);
        std::swap(_reference, other._reference);
    }

    return *this;
}

bool LuaReference::Get() const
{
    if (IsSet())
    {
        lua_rawgeti(_state, LUA_REGISTRYINDEX, _reference);
        return true;
    }

    return false;
}
