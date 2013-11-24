#ifndef SIMPLEPROGRAM_HPP
#define SIMPLEPROGRAM_HPP

#include <SDL2TK/OpenGL/Program.hpp>

class SimpleProgram
{
    public:
        SimpleProgram();
        ~SimpleProgram();

        void Use();

    protected:
    private:
        SDL2TK::Program _program;
        GLint _vertexAttribute;
        GLint _colorAttribute;
};

#endif
