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

        lua_State* Raw() const { return _state; }

        void AddFunction(lua_CFunction callback, const char* name);
        void Execute();
        void ReportErrors();
        void Execute(const char* command);
        void ExecuteFile(const char* path);
        void SetUserData(void* key, void* value);

        int GetReference();
        void PushReference(int luaReference);
        void ClearReference(int& luaReference);

        static void* GetUserData(lua_State* state, void* key);

    protected:
    private:
        LuaState(const LuaState&) = delete;
        LuaState& operator=(const LuaState&) = delete;

        lua_State* _state;

        static int Test(lua_State* state);
};

#endif
