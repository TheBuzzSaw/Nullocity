#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "glew.h"
#include <vector>
#include <string>

namespace SDL2TK
{
    class Program
    {
        public:
            Program();
            Program(Program&& other);
            ~Program();

            Program& operator=(Program&& other);

            inline void Use() { glUseProgram(_program); }
            GLint GetUniformLocation(const GLchar* name);
            GLint GetAttributeLocation(const GLchar* name);

            inline const std::string& Errors() const { return _errors; }
            inline bool HasErrors() const { return _errors.length() > 0; }

        private:
            Program(GLuint& program, std::vector<GLuint>&& shaders);

            Program(const Program&) = delete;
            Program& operator=(const Program&) = delete;

            GLuint _program;
            std::vector<GLuint> _shaders;
            std::string _errors;

            friend class ProgramBuilder;
    };
}

#endif

