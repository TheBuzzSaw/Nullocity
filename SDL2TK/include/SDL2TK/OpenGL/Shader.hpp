#ifndef SHADER_HPP
#define SHADER_HPP

#include "glew.h"
#include <string>

namespace SDL2TK
{
    class Shader
    {
        public:
            enum class Type : GLenum
            {
                Vertex = GL_VERTEX_SHADER,
                Geometry = GL_GEOMETRY_SHADER,
                Fragment = GL_FRAGMENT_SHADER
            };

            Shader();
            Shader(Type type, const char* source);
            Shader(Shader&& other);
            ~Shader();

            Shader& operator=(Shader&& other);

            inline const std::string& Errors() const { return _errors; }
            inline bool HasErrors() const { return _errors.length() > 0; }
            inline bool IsGood() const { return _errors.length() < 1; }

        private:
            Shader(const Shader& other) = delete;
            Shader& operator=(const Shader& other) = delete;

            GLuint _shader;
            std::string _errors;

            friend class ProgramBuilder;
    };
}

#endif
