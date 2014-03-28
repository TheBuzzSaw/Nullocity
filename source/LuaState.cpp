#include "LuaState.hpp"
#include <algorithm>
#include <iostream>

static const int KeyBase = 0xBADC0DE;
static constexpr void* GetKey() { return (void*)&KeyBase; }

static LuaState& GetThis(lua_State* state)
{
    lua_pushlightuserdata(state, GetKey());
    lua_gettable(state, LUA_REGISTRYINDEX);
    return *reinterpret_cast<LuaState*>(lua_touserdata(state, -1));
}

LuaState::LuaState()
{
    _state = luaL_newstate();
    luaL_openlibs(_state);

    lua_pushnil(_state);
    lua_setglobal(_state, "io");

    lua_newtable(_state);

    lua_pushcfunction(_state, Test);
    lua_setfield(_state, 1, "Test");

    lua_setglobal(_state, "Nullocity");

    lua_pushlightuserdata(_state, GetKey());
    lua_pushlightuserdata(_state, this);
    lua_settable(_state, LUA_REGISTRYINDEX);
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
    auto status = luaL_loadstring(_state, command);

    if (status)
        ReportErrors();
    else
        Execute();
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

void LuaState::InternalTest()
{
    std::cout << "Internal test FTW!" << std::endl;
}

int LuaState::Test(lua_State* state)
{
    std::cerr << "Successful call!\n";

    LuaState& object = GetThis(state);
    object.InternalTest();

    return 0;
}