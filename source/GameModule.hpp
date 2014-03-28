#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

#include "SimpleProgram.hpp"
#include "Asteroid.hpp"
#include "Entity.hpp"
#include "LuaState.hpp"
#include "CollisionHandler.hpp"
#include <SDL2TK/Module.hpp>
#include <SDL2TK/Camera.hpp>
#include <unordered_set>

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
        SimpleProgram _program;
        SimpleBufferObject _linesObject;
        SimpleBufferObject _cubeObject;
        SimpleBufferObject _squarePyramidObject;

        CollisionHandler LHC;

        std::unordered_set<Entity*> _asteroids;
        SDL2TK::Camera<GLfloat> _camera;

        SDL2TK::RotationF _playerRotation;
        SDL2TK::RotationF _playerTorque;

        LuaState _lua;

        void FixPosition(Entity& entity);

        static const int KeyBase;
        static GameModule& FromLua(lua_State* state);
        static int AddEntity(lua_State* state);
};

#endif
