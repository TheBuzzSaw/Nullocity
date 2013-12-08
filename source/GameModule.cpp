#include "GameModule.hpp"
#include "Builders.hpp"
#include <SDL2TK/Matrix4x4.hpp>
using namespace std;
using namespace SDL2TK;

GameModule::GameModule()
{
    //(void)BuildPyramid;
    _cubeObject = BuildCube();
    _linesObject = BuildLines();

    _camera.Distance(32.0f);
    _camera.Vertical(RotationF::FromDegrees(-45.0f));
}

GameModule::~GameModule()
{
}

void GameModule::OnOpen()
{
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glLineWidth(8.0f);

    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

void GameModule::OnClose()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

void GameModule::OnLoop()
{
    Matrix4x4F matrix;
    _camera.Apply(matrix);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program.Open();

    for (int i = 0; i < AsteroidCount; ++i)
    {
        Asteroid& asteroid = _asteroids[i];
        Vector2F position = asteroid.Position();
        glLoadMatrixf(
            Matrix4x4F(matrix)
                .Translate(position.X(), position.Y(), 0.0f)
                .RotateX(asteroid.RotationX())
                .RotateY(asteroid.RotationY())
                );
        _program.Draw(_cubeObject, GL_TRIANGLES);
    }

    glLoadMatrixf(matrix);
    _program.Draw(_linesObject, GL_LINES);

    _program.Close();
}

void GameModule::OnPulse()
{
    auto horizontal = _camera.Horizontal();
    _camera.Horizontal(horizontal + RotationF::FromDegrees(1.0f));

    for (int i = 0; i < AsteroidCount; ++i)
        _asteroids[i].Update();
}

void GameModule::OnSecond(Uint32 framesPerSecond)
{
}

void GameModule::OnResize(int width, int height)
{
    float aspectRatio = float(width) / float(height);

    glViewport(0, 0, width, height);

    Matrix4x4F matrix;
    matrix.Perspective(RotationF::FromDegrees(30.0f), aspectRatio, 1.0f,
        100.0f);
    //matrix.Orthographic(8.0f, aspectRatio);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
}
