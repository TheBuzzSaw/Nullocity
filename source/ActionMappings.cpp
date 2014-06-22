#include "ActionMappings.hpp"
#include "KeyNames.hpp"
#include <cstring>

const int ActionMappings::LuaKeyBase = 0xAC;

ActionMappings::ActionMappings(LuaState& lua)
    : _lua(lua)
{
}

ActionMappings::~ActionMappings()
{
}

//ActionMappings::ActionMappings(const ActionMappings& other)
//{
//    //copy ctor
//}
//
//ActionMappings& ActionMappings::operator=(const ActionMappings& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//    //assignment operator
//    return *this;
//}

void ActionMappings::AddActionKey(std::string actionName, SDL_Keycode key)
{
    auto actionIt = _actionKeys.find(actionName);

    if (actionIt != _actionKeys.end())
    {
        _actionCallbacks[key] = &actionIt->second;
    }
}

void ActionMappings::FireActionKeyDown(SDL_Keycode key, int value)
{
    auto actionIt = _actionCallbacks.find(key);

    if (actionIt != _actionCallbacks.end())
    {
        actionIt->second->FireKeyDown(_lua, value);
    }
}


bool ActionMappings::CreateAction(std::string name, LuaReference keyCallback)
{
    const auto& emplacement =
        _actionKeys.emplace(
            name,
            Action(std::move(keyCallback)));

    return emplacement.second;
}

bool ActionMappings::CreateAction(
    std::string name,
    LuaReference keyDownCallback,
    LuaReference keyUpCallback)
{
    const auto& emplacement =
        _actionKeys.emplace(
            name,
            Action(std::move(keyDownCallback), std::move(keyUpCallback)));

    return emplacement.second;
}

ActionMappings& ActionMappings::FromLua(lua_State* state)
{
    auto raw = LuaState::GetUserData(state, (void*)&LuaKeyBase);
    return *reinterpret_cast<ActionMappings*>(raw);
}

int ActionMappings::AddActionCallback(lua_State* state)
{
    auto argc = lua_gettop(state);

    if (argc > 2
        && lua_isstring(state, 1)
        && lua_isstring(state, 2)
        && lua_isfunction(state, 3))
    {
        ActionMappings& am = ActionMappings::FromLua(state);
        auto actionName = lua_tostring(state, 1);
        auto defaultKey = lua_tostring(state, 2);

        if (argc > 3
            && lua_isfunction(state, 4))
        {
            lua_settop(state, 4);
        }

        lua_settop(state, 3);

        SDL_Keycode result = SDLK_UNKNOWN;

        // Because arrays are freakin' fast!
        for (const KeyName* i = GetKeyNames(); i->name; ++i)
        {
            if (!strcmp(defaultKey, i->name))
            {
                result = i->keycode;
                break;
            }
        }

        if (result != SDLK_UNKNOWN)
        {
            am.CreateAction(actionName, LuaReference(state));
            am.AddActionKey(actionName, result);
        }
    }
    return 0;
}
