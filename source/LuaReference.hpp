#ifndef LUAREFERENCE_HPP
#define LUAREFERENCE_HPP

#include <lua.hpp>

class LuaReference
{
    public:
        LuaReference(lua_State* state = nullptr);
        LuaReference(LuaReference&& other);
        ~LuaReference();

        LuaReference& operator=(LuaReference&& other);

        inline bool HasReference() const { return _reference != LUA_NOREF; }

        void Push();

    protected:
    private:
        LuaReference(const LuaReference&) = delete;
        LuaReference& operator=(const LuaReference&) = delete;

        lua_State* _state;
        int _reference;
};

#endif
