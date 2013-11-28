#ifndef SIMPLEPROGRAM_HPP
#define SIMPLEPROGRAM_HPP

#include "SimpleBufferObject.hpp"
#include <SDL2TK/OpenGL/Program.hpp>

class SimpleProgram
{
    public:
        SimpleProgram();
        ~SimpleProgram();

        void Open();
        void Close();

        void Draw(const SimpleBufferObject& object) const;

    protected:
    private:
        SDL2TK::Program _program;
        GLint _positionAttribute;
        GLint _colorAttribute;
};

#endif
