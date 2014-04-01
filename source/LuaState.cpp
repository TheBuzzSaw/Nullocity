#include "LuaState.hpp"
#include <algorithm>
#include <iostream>

static const char* const PackageName = "Nullocity";

LuaState::LuaState()
{
    _state = luaL_newstate();
    luaL_openlibs(_state);

    // Experimenting with disabling libraries.
    //lua_pushnil(_state);
    //lua_setglobal(_state, "io");

    lua_newtable(_state);
    lua_setglobal(_state, PackageName);

    AddFunction(Test, "Test");
}

LuaState::LuaState(LuaState&& other)
    : _state(other._state)
{
    other._state = nullptr;
}

LuaState::~LuaState()
{
    if (_state) lua_close(_state);
}

LuaState& LuaState::operator=(LuaState&& other)
{
    if (this != &other)
    {
        if (_state) lua_close(_state);
        _state = other._state;
        other._state = nullptr;
    }

    return *this;
}

void LuaState::AddFunction(lua_CFunction callback, const char* name)
{
    lua_getglobal(_state, PackageName);
    lua_pushcfunction(_state, callback);
    lua_setfield(_state, -2, name);
    lua_pop(_state, -1);
}

void LuaState::Execute(const char* command)
{
    auto status = luaL_loadstring(_state, command);

    if (status)
        ReportErrors();
    else
        Execute();
}

void LuaState::ExecuteFile(const char* path)
{
    auto status = luaL_dofile(_state, path);
    if (status) ReportErrors();
}

void LuaState::SetUserData(void* key, void* value)
{
    lua_pushlightuserdata(_state, key);
    lua_pushlightuserdata(_state, value);
    lua_settable(_state, LUA_REGISTRYINDEX);
}
void LuaState::Execute()
{
    auto status = lua_pcall(_state, 0, LUA_MULTRET, 0);
    if (status) ReportErrors();
}

void LuaState::ReportErrors()
{
    std::cerr << "Lua error: " << lua_tostring(_state, -1) << '\n';
    lua_pop(_state, 1);
}

void* LuaState::GetUserData(lua_State* state, void* key)
{
    lua_pushlightuserdata(state, key);
    lua_gettable(state, LUA_REGISTRYINDEX);
    void* result = lua_touserdata(state, -1);
    lua_pop(state, 1);
    return result;
}

int LuaState::Test(lua_State* state)
{
    std::cerr << "Successful call!\n";

    return 0;
}
