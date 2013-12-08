#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

#include "SimpleProgram.hpp"
#include "Asteroid.hpp"
#include <SDL2TK/Module.hpp>
#include <SDL2TK/Camera.hpp>

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
        virtual void OnSecond(Uint32 framesPerSecond);

        virtual void OnResize(int width, int height);

    protected:
    private:
        SimpleProgram _program;
        SimpleBufferObject _linesObject;
        SimpleBufferObject _cubeObject;
        Asteroid _asteroids[AsteroidCount];
        SDL2TK::Camera<GLfloat> _camera;
};

#endif
