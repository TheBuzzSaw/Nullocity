#include "GameModule.hpp"
#include <SDL2TK/Matrix4x4.hpp>

GameModule::GameModule()
{
}

GameModule::~GameModule()
{
}

void GameModule::OnOpen()
{
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

void GameModule::OnClose()
{
}

void GameModule::OnLoop()
{
    SDL2TK::Matrix4x4<float> matrix;
    glLoadMatrixf(matrix);

    glClear(GL_COLOR_BUFFER_BIT);
}

void GameModule::OnPulse()
{
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
