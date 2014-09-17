#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

#include "SimpleProgram.hpp"
#include "Entity.hpp"
#include "LuaState.hpp"
#include "LuaReference.hpp"
#include "CollisionHandler.hpp"
#include "ActionMappings.hpp"
#include "ModelLoader.hpp"
#include "AudioManager.hpp"
#include <SDL2TK/Module.hpp>
#include <SDL2TK/Camera.hpp>
#include <unordered_set>
#include <unordered_map>
#include <random>

class GameModule : public SDL2TK::Module
{
    public:
        GameModule();
        virtual ~GameModule();

        virtual void OnOpen();
        virtual void OnClose();
        virtual void OnLoop();
        virtual void OnPulse();
        virtual void OnSecond(int framesPerSecond);

        virtual void OnKeyDown(const SDL_Keysym& keysym);
        virtual void OnKeyUp(const SDL_Keysym& keysym);

        virtual void OnResize(int width, int height);

    protected:
    private:
        void InitializeLua();
        void DestroyState();

        SimpleProgram _program;
        SimpleBufferObject _linesObject;
        SimpleBufferObject _squarePyramidObject;

        std::unordered_set<Entity*> _entities;
        std::vector<Entity*> _deadEntities;
        SDL2TK::Camera<GLfloat> _camera;

        SDL2TK::RotationF _playerRotation;
        SDL2TK::RotationF _playerTorque;

        LuaState _lua;
        LuaReference _updateCallback;
        std::mt19937_64 _generator;
        CollisionHandler _collisionHandler;
        ModelLoader _modelLoader;

        float _distance;
        float _distanceDelta;

        ActionMappings _actions;

        AudioManager _audioManager;
        const SDL2TK::AudioBuffer* _sound;

        static const int LuaKeyBase;
        static GameModule& FromLua(lua_State* state);

        static int SetUpdateCallback(lua_State* state);
        static int AddEntity(lua_State* state);
        static int RemoveEntity(lua_State* state);

        static int SetPosition(lua_State* state);
        static int SetVelocity(lua_State* state);
        static int SetRotation(lua_State* state);
        static int SetTorque(lua_State* state);
        static int SetRadius(lua_State* state);
        static int SetScale(lua_State* state);

        static int GetPosition(lua_State* state);
        static int GetVelocity(lua_State* state);
        static int GetRotation(lua_State* state);
        static int GetTorque(lua_State* state);
        static int GetRadius(lua_State* state);
        static int GetScale(lua_State* state);

        static int GetRandom(lua_State* state);

        static int SetCameraPosition(lua_State* state);
        static int SetCameraHorizontal(lua_State* state);
        static int SetCameraVertical(lua_State* state);
        static int SetCameraDistance(lua_State* state);

        static int AddLuaFile(lua_State* state);
};

#endif
