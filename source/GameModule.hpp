#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

#include "SimpleProgram.hpp"
#include "Asteroid.hpp"
#include "Entity.hpp"
#include <SDL2TK/Module.hpp>
#include <SDL2TK/Camera.hpp>
#include <vector>

const int AsteroidCount = 64;

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
        std::vector<Entity> _asteroids;
        SDL2TK::Camera<GLfloat> _camera;

        SDL2TK::RotationF _playerRotation;
        SDL2TK::RotationF _playerTorque;
};

#endif
