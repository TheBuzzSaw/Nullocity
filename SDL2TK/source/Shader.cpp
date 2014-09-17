#include "../include/SDL2TK/OpenGL/Shader.hpp"
#include <memory>

namespace SDL2TK
{
    Shader::Shader()
        : _shader(0)
    {
    }

    Shader::Shader(Type type, const char* source)
        : _shader(0)
    {
        // http://www.opengl.org/sdk/docs/man/xhtml/glCreateShader.xml
        _shader = glCreateShader(static_cast<GLenum>(type));

        if (_shader)
        {
            glShaderSource(_shader, 1, &source, nullptr);
            glCompileShader(_shader);

            GLint compiled;
            glGetShaderiv(_shader, GL_COMPILE_STATUS, &compiled);

            if (!compiled)
            {
                GLint length;
                glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

                if (length > 0)
                {
                    // Replace with smart pointer, please. :(
                    char* buffer = new char[length + 1];
                    glGetShaderInfoLog(_shader, length, nullptr, buffer);
                    buffer[length] = '\0';
                    _errors = buffer;
                    delete [] buffer;
                }
                else
                {
                    _errors = "failed to compile (OpenGL provided no logs)";
                }

                glDeleteShader(_shader);
                _shader = 0;
            }
        }
        else
        {
            _errors = "failed on glCreateShader";
        }
    }

    Shader::Shader(Shader&& other)
        : _shader(other._shader)
        , _errors(std::move(other._errors))
    {
        other._shader = 0;
    }

    Shader::~Shader()
    {
        // http://www.opengl.org/sdk/docs/man/xhtml/glDeleteShader.xml
        glDeleteShader(_shader); // Safe to call on 0.
    }

    Shader& Shader::operator=(Shader&& other)
    {
        if (this != &other)
        {
            glDeleteShader(_shader);
            _shader = other._shader;
            _errors = std::move(other._errors);
            other._shader = 0;
        }

        return *this;
    }
}
