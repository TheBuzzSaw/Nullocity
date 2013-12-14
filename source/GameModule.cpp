#include "GameModule.hpp"
#include "Builders.hpp"
#include <SDL2TK/Matrix4x4.hpp>
using namespace std;
using namespace SDL2TK;

GameModule::GameModule()
{
    //(void)BuildPyramid;
    _cubeObject = BuildCube();
    _squarePyramidObject = BuildSquarePyramid();
    _linesObject = BuildLines();

    _camera.Distance(32.0f);
    _camera.Vertical(RotationF::FromDegrees(-45.0f));
    //PulseInterval(SDL2TK::TimeSpan::FromSeconds(1) / 60);
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

    const float N = 1.0f / 8.0f;
    glClearColor(N, N, N, 1.0f);
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

    glLoadMatrixf(
        Matrix4x4F(matrix)
            .RotateX(RotationF::FromDegrees(-90.0f))
            .Scale(1.0f, 0.5f, 2.0f));

    _program.Draw(_squarePyramidObject, GL_TRIANGLES);

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

    //glLoadMatrixf(matrix);
    //_program.Draw(_linesObject, GL_LINES);

    _program.Close();
}

void GameModule::OnPulse()
{
    auto horizontal = _camera.Horizontal();
    //_camera.Horizontal(horizontal + RotationF::FromDegrees(1.0f));

    for (int i = 0; i < AsteroidCount; ++i)
        _asteroids[i].Update();
}

void GameModule::OnSecond(int framesPerSecond)
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
