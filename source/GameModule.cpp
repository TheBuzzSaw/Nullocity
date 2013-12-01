#include "GameModule.hpp"
#include <SDL2TK/Matrix4x4.hpp>
#include <cmath>
using namespace std;
using namespace SDL2TK;

static SimpleBufferObject BuildPyramid()
{
    const float RootTwo = 1.414213562f;
    const float Z = 1.0f / RootTwo;

    Vector3F positions[4];

    positions[0] = Vector3F(1.0f, 0.0f, -Z);
    positions[1] = Vector3F(-1.0f, 0.0f, -Z);
    positions[2] = Vector3F(0.0f, 1.0f, Z);
    positions[3] = Vector3F(0.0f, -1.0f, Z);

    SimpleBuilder builder;
    builder.Reserve(12);

    const Vector4F Red(1.0f, 0.0f, 0.0f, 1.0f);
    const Vector4F Green(0.0f, 1.0f, 0.0f, 1.0f);
    const Vector4F Blue(0.0f, 0.0f, 1.0f, 1.0f);
    const Vector4F Yellow(1.0f, 1.0f, 0.0f, 1.0f);

    builder.Add(positions[0], Red);
    builder.Add(positions[2], Red);
    builder.Add(positions[1], Red);

    builder.Add(positions[0], Green);
    builder.Add(positions[1], Green);
    builder.Add(positions[3], Green);

    builder.Add(positions[1], Blue);
    builder.Add(positions[2], Blue);
    builder.Add(positions[3], Blue);

    builder.Add(positions[0], Yellow);
    builder.Add(positions[3], Yellow);
    builder.Add(positions[2], Yellow);

    return SimpleBufferObject(builder);
}

GameModule::GameModule()
{
    _object[0] = BuildPyramid();

    SimpleBuilder builder;

    Vector4F black;

    builder.Add(Vector3F(-7.0f, 0.0f, 0.0f), black);
    builder.Add(Vector3F(7.0f, 0.0f, 0.0f), black);
    builder.Add(Vector3F(0.0f, -7.0f, 0.0f), black);
    builder.Add(Vector3F(0.0f, 7.0f, 0.0f), black);

    _object[1] = SimpleBufferObject(builder);
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
    matrix
        .Translate(0.0f, 0.0f, -30.0f)
        ;//.RotateX(RotationF::FromDegrees(-45.0f))
        //.RotateZ(RotationF::FromDegrees(-45.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program.Open();

    //glLoadMatrixf(Matrix4x4F(matrix).Scale(4.0f).RotateX(_rotation).RotateZ(_rotation));
    //_program.Draw(_object[0], GL_TRIANGLES);

    for (int i = 0; i < AsteroidCount; ++i)
    {
        Asteroid& asteroid = _asteroids[i];
        Vector2F position = asteroid.Position();
        Vector2F rotation = asteroid.Rotation();
        glLoadMatrixf(
            Matrix4x4F(matrix)
                .Translate(position.X(), position.Y(), 0.0f)
                .RotateX(RotationF::FromRadians(rotation.X()))
                .RotateY(RotationF::FromRadians(rotation.Y()))
                );
        _program.Draw(_object[0], GL_TRIANGLES);
    }

    glLoadMatrixf(matrix);
    _program.Draw(_object[1], GL_LINES);

    _program.Close();
}

void GameModule::OnPulse()
{
    _rotation += RotationF::FromDegrees(2.0f);

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
