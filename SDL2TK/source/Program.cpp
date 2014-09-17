#include "../include/SDL2TK/OpenGL/Program.hpp"
#include <cassert>

namespace SDL2TK
{
    Program::Program()
        : _program(0)
    {
    }

    Program::Program(GLuint& program, std::vector<GLuint>&& shaders)
        : _program(program)
        , _shaders(std::move(shaders))

    {
        assert(shaders.size() < 1);

        if (_program)
        {
            program = 0;
            glLinkProgram(_program);

            GLint linked;
            glGetProgramiv(_program, GL_LINK_STATUS, &linked);

            if (!linked)
            {
                GLint length;
                glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);

                if (length > 0)
                {
                    // Replace with smart pointer, please. :(
                    char* buffer = new char[length + 1];
                    glGetProgramInfoLog(_program, length, nullptr, buffer);
                    buffer[length] = '\0';
                    _errors = buffer;
                    delete [] buffer;
                }
                else
                {
                    _errors = "failed to link (OpenGL provided no logs)";
                }
            }
        }
        else
        {
            _errors = "failed on glCreateProgram";
        }
    }

    Program::Program(Program&& other)
        : _program(other._program)
        , _shaders(std::move(other._shaders))
        , _errors(std::move(other._errors))
    {
    }

    Program::~Program()
    {
        for (GLuint i : _shaders) glDetachShader(_program, i);
        glDeleteProgram(_program);
    }

    Program& Program::operator=(Program&& other)
    {
        if (this != &other)
        {
            for (GLuint i : _shaders) glDetachShader(_program, i);
            glDeleteProgram(_program);

            _program = other._program;
            _shaders = std::move(other._shaders);
            _errors = std::move(other._errors);
            other._program = 0;
        }

        return *this;
    }

    GLint Program::GetUniformLocation(const GLchar* name)
    {
        // http://www.opengl.org/sdk/docs/man/xhtml/glGetUniformLocation.xml

        GLint result = -1;

        if (_program && name && *name)
            result = glGetUniformLocation(_program, name);

        return result;
    }

    GLint Program::GetAttributeLocation(const GLchar* name)
    {
        // http://www.opengl.org/sdk/docs/man/xhtml/glGetUniformLocation.xml

        GLint result = -1;

        if (_program && name && *name)
            result = glGetAttribLocation(_program, name);

        return result;
    }
}
