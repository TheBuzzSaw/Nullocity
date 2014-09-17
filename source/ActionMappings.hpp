#ifndef ACTIONMAPPINGS_HPP
#define ACTIONMAPPINGS_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <SDL.h>
#include "LuaReference.hpp"
#include "LuaState.hpp"

class ActionMappings
{
    public:
        ActionMappings(LuaState& lua);
        ~ActionMappings();
        ActionMappings(const ActionMappings& other) = delete;
        ActionMappings& operator=(const ActionMappings& other) = delete;

        bool CreateAction(std::string name, LuaReference keyCallback);
        bool CreateAction(
            std::string name,
            LuaReference keyDownCallback,
            LuaReference keyUpCallback);

        void AddActionKey(std::string actionName, SDL_Keycode key);

        void FireActionKeyDown(SDL_Keycode key, int value);
        void FireActionKeyUp(SDL_Keycode key, int value);

        void DestroyState()
        {
            _actionKeys.clear();
            _actionCallbacks.clear();
        }

        void InitializeLua()
        {
            _lua.SetUserData((void*)&LuaKeyBase, this);
            _lua.AddFunction(AddActionCallback, "AddActionCallback");
        }

    protected:
    private:
        struct Action
        {
            public:
                Action(LuaReference keyDownCallback, LuaReference keyUpCallback)
                    : _keyDownCallback(std::move(keyDownCallback))
                    , _keyUpCallback(std::move(keyUpCallback))
                {
                }

                Action(LuaReference keyCallback)
                    : _keyDownCallback(std::move(keyCallback))
                {
                }

                void FireKeyDown(LuaState& lua, int value)
                {
                    if (_keyDownCallback.HasReference())
                    {
                        auto state = lua.Raw();
                        _keyDownCallback.Push();
                        lua_pushnumber(state, value);
                        lua.Call(1, 0);
                    }
                }

                void FireKeyUp(LuaState& lua, int value)
                {
                    if (_keyUpCallback.HasReference())
                    {
                        auto state = lua.Raw();
                        _keyDownCallback.Push();
                        lua_pushnumber(state, value);
                        lua.Call(1, 0);
                    }
                    else
                    {
                        FireKeyDown(lua, value);
                    }
                }

            private:
                LuaReference _keyDownCallback;
                LuaReference _keyUpCallback;
        };

        std::unordered_map<SDL_Keycode, Action*> _actionCallbacks;
        std::unordered_map<std::string, Action> _actionKeys;

        LuaState& _lua;

        static const int LuaKeyBase;
        static ActionMappings& FromLua(lua_State* state);
        static int AddActionCallback(lua_State* state);


};

#endif
