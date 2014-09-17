#ifndef PROGRAMBUILDER_HPP
#define PROGRAMBUILDER_HPP

#include "Shader.hpp"
#include "Program.hpp"
#include <vector>
#include <string>

namespace SDL2TK
{
    class ProgramBuilder
    {
        public:
            ProgramBuilder();
            ~ProgramBuilder();

            void Attach(const Shader& shader);
            void BindAttributeLocation(GLuint index, const GLchar* name);
            Program Link();

        private:
            ProgramBuilder(ProgramBuilder&&) = delete;
            ProgramBuilder(const ProgramBuilder&) = delete;
            ProgramBuilder& operator=(ProgramBuilder&&) = delete;
            ProgramBuilder& operator=(const ProgramBuilder&&) = delete;

            void CreateProgram();

            GLuint _program;
            std::vector<GLuint> _shaders;
    };
}

#endif
