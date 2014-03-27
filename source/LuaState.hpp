#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <lua.hpp>

class LuaState
{
    public:
        LuaState();
        LuaState(LuaState&& other);
        ~LuaState();

        LuaState& operator=(LuaState&& other);

        void Execute(const char* command);

    protected:
    private:
        LuaState(const LuaState&) = delete;
        LuaState& operator=(const LuaState&) = delete;

        void Execute();
        void ReportErrors();

        lua_State* _state;

        static int Test(lua_State* state);
};

#endif
