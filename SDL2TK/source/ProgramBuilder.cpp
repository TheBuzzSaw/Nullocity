#include "../include/SDL2TK/OpenGL/ProgramBuilder.hpp"

namespace SDL2TK
{
    ProgramBuilder::ProgramBuilder()
        : _program(0)
    {
    }

    ProgramBuilder::~ProgramBuilder()
    {
        for (GLuint i : _shaders) glDetachShader(_program, i);

        // http://www.opengl.org/sdk/docs/man/xhtml/glDeleteProgram.xml
        glDeleteProgram(_program); // Safe to call on 0.
    }

    void ProgramBuilder::Attach(const Shader& shader)
    {
        if (shader.IsGood())
        {
            CreateProgram();
            _shaders.push_back(shader._shader);
            glAttachShader(_program, shader._shader);
        }
    }

    void ProgramBuilder::BindAttributeLocation(GLuint index, const GLchar* name)
    {
        if (name && *name)
        {
            CreateProgram();
            glBindAttribLocation(_program, index, name);
        }
    }

    Program ProgramBuilder::Link()
    {
        return Program(_program, std::move(_shaders));
    }

    void ProgramBuilder::CreateProgram()
    {
        if (!_program)
            _program = glCreateProgram();
    }
}
