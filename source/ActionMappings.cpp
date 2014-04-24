#include "ActionMappings.hpp"

const int ActionMappings::LuaKeyBase = 0xAC;

ActionMappings::ActionMappings(LuaState& lua)
    : _lua(lua)
{
    //ctor
}

ActionMappings::~ActionMappings()
{
    //dtor
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
    std::pair<std::unordered_map<std::string, Action>::iterator, bool> wasEmplaced =
        _actionKeys.emplace(name, Action(std::move(keyCallback)));

    return wasEmplaced.second;
}

bool ActionMappings::CreateAction(std::string name, LuaReference keyDownCallback, LuaReference keyUpCallback)
{
    std::pair<std::unordered_map<std::string, Action>::iterator, bool> wasEmplaced =
        _actionKeys.emplace(name, Action(std::move(keyDownCallback), std::move(keyUpCallback)));

    return wasEmplaced.second;
}

ActionMappings& ActionMappings::FromLua(lua_State* state)
{
    auto raw = LuaState::GetUserData(state, (void*)&LuaKeyBase);
    return *reinterpret_cast<ActionMappings*>(raw);
}

int ActionMappings::AddActionCallbacks(lua_State* state)
{
    auto argc = lua_gettop(state);

    if (argc > 2
        && lua_isstring(state, 1)
        && lua_isstring(state, 2)
        && lua_isfunction(state, 3))
    {
        ActionMappings& module = ActionMappings::FromLua(state);
        auto actionName = lua_tostring(state, 1);
        auto defaultKey = lua_tostring(state, 2);
        if (argc > 3
            && lua_isfunction(state, 4))
        {
            lua_settop(state, 4);

        }
        lua_settop(state, 3);
        module.CreateAction(actionName, LuaReference(state));
        module.AddActionKey(actionName, SDLK_SPACE);
//        module._actionCallbacks[SDLK_SPACE] = LuaReference(state);
    }
    return 0;
}
