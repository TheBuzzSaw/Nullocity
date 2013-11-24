#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

#include "SimpleProgram.hpp"
#include <SDL2TK/Module.hpp>

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
};

#endif
