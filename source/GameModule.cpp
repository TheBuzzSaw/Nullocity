#include "GameModule.hpp"
#include <SDL2TK/Matrix4x4.hpp>

int puts(const char* text);

GameModule::GameModule()
{
    SimpleBuilder builder;
    builder.Add(SDL2TK::Vector3<GLfloat>(-1.0f, -1.0f, 0.0f),
        SDL2TK::Vector4<GLfloat>(1.0f, 0.0f, 0.0f, 1.0f));
    builder.Add(SDL2TK::Vector3<GLfloat>(0.0f, 1.0f, 0.0f),
        SDL2TK::Vector4<GLfloat>(0.0f, 1.0f, 0.0f, 1.0f));
    builder.Add(SDL2TK::Vector3<GLfloat>(1.0f, -1.0f, 0.0f),
        SDL2TK::Vector4<GLfloat>(0.0f, 0.0f, 1.0f, 1.0f));

    _object = SimpleBufferObject(builder);
}

GameModule::~GameModule()
{
}

void GameModule::OnOpen()
{
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

void GameModule::OnClose()
{
}

void GameModule::OnLoop()
{
    glClear(GL_COLOR_BUFFER_BIT);

    _program.Open();
    _program.Draw(_object);
    _program.Close();
}

void GameModule::OnPulse()
{
    _rotation += SDL2TK::Rotation<GLfloat>::FromDegrees(2.0f);

    SDL2TK::Matrix4x4<GLfloat> matrix;
    matrix.Scale(4.0f);
    matrix.RotateZ(_rotation);
    glLoadMatrixf(matrix);
}

void GameModule::OnSecond(Uint32 framesPerSecond)
{
}

void GameModule::OnResize(int width, int height)
{
    float aspectRatio = float(width) / float(height);

    glViewport(0, 0, width, height);

    SDL2TK::Matrix4x4<float> matrix;
    matrix.Orthographic(8.0f, aspectRatio);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
}
