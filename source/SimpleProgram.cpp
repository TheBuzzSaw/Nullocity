#include "SimpleProgram.hpp"
#include <SDL2TK/Tools.hpp>
#include <SDL2TK/OpenGL/ProgramBuilder.hpp>
#include <iostream>
using namespace std;

SimpleProgram::SimpleProgram()
{
    SDL2TK::Shader vertexShader(SDL2TK::Shader::Type::Vertex,
        SDL2TK::FileToString("simple.vertex.shader").c_str());

    if (vertexShader.HasErrors())
        cout << "vertex shader errors: " << vertexShader.Errors() << endl;

    SDL2TK::Shader fragmentShader(SDL2TK::Shader::Type::Fragment,
        SDL2TK::FileToString("simple.fragment.shader").c_str());

    if (fragmentShader.HasErrors())
        cout << "fragment shader errors: " << fragmentShader.Errors() << endl;

    SDL2TK::ProgramBuilder builder;
    builder.Attach(vertexShader);
    builder.Attach( fragmentShader);

    _program = builder.Link();

    if (_program.HasErrors())
    {
        cout << "program errors: " << _program.Errors() << endl;
    }
    else
    {
        _positionAttribute = _program.GetAttributeLocation("position");
        _colorAttribute = _program.GetAttributeLocation("color");
    }
}

SimpleProgram::~SimpleProgram()
{
}

void SimpleProgram::Open()
{
    _program.Use();
    glEnableVertexAttribArray(_positionAttribute);
    glEnableVertexAttribArray(_colorAttribute);
}

void SimpleProgram::Close()
{
    glDisableVertexAttribArray(_colorAttribute);
    glDisableVertexAttribArray(_positionAttribute);
}

void SimpleProgram::Draw(const SimpleBufferObject& object, GLenum mode) const
{
    object.Draw(mode, _positionAttribute, _colorAttribute);
}
