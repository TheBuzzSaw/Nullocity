#include "LuaState.hpp"
#include <algorithm>
#include <iostream>

#define LDB std::cerr << "YARR -- " << __LINE__ << '\n'

LuaState::LuaState()
{
    _state = luaL_newstate();
    luaL_openlibs(_state);

    //lua_newtable(_state);

    //lua_pushcfunction(_state, Test);
    //lua_setfield(_state, -1, "Test");

    //lua_setglobal(_state, "Nullocity");
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

void LuaState::Execute(const char* command)
{
    LDB;
    auto status = luaL_loadstring(_state, command);
    LDB;
    //std::cerr << "loadstring -- " << status << '\n';

    if (status)
        ReportErrors();
    else
        Execute();

    LDB;
}

void LuaState::Execute()
{
    LDB;
    auto status = lua_pcall(_state, 0, LUA_MULTRET, 0);
    LDB;
    if (status) ReportErrors();
    LDB;
}

void LuaState::ReportErrors()
{
    LDB;
    std::cerr << "Lua error: " << lua_tostring(_state, -1) << '\n';
    LDB;
    lua_pop(_state, 1);
    LDB;
}

int LuaState::Test(lua_State* state)
{
    std::cerr << "Successful call!\n";

    return 0;
}
