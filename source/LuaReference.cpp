#include "LuaReference.hpp"

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
        if (_state) luaL_unref(_state, LUA_REGISTRYINDEX, _reference);

        _state = other._state;
        _reference = other._reference;

        other._state = nullptr;
        other._reference = LUA_NOREF;
    }

    return *this;
}

void LuaReference::Push()
{
    lua_rawgeti(_state, LUA_REGISTRYINDEX, _reference);
}
