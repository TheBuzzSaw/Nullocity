#include "GameModule.hpp"
#include <SDL2TK/Matrix4x4.hpp>
#include <cmath>
using namespace std;
using namespace SDL2TK;

static const Vector4F Black(0.0f, 0.0f, 0.0f, 1.0f);
static const Vector4F Red(1.0f, 0.0f, 0.0f, 1.0f);
static const Vector4F Green(0.0f, 1.0f, 0.0f, 1.0f);
static const Vector4F Blue(0.0f, 0.0f, 1.0f, 1.0f);
static const Vector4F Yellow(1.0f, 1.0f, 0.0f, 1.0f);
static const Vector4F Magenta(1.0f, 0.0f, 1.0f, 1.0f);
static const Vector4F Cyan(0.0f, 1.0f, 1.0f, 1.0f);

static SimpleBufferObject BuildCube()
{
    const float N = 1.0f;

    SimpleBuilder builder;
    builder.Reserve(36);

    builder.Add(Vector3F(N, N, N), Red);
    builder.Add(Vector3F(N, N, -N), Red);
    builder.Add(Vector3F(N, -N, -N), Red);

    builder.Add(Vector3F(N, N, N), Red);
    builder.Add(Vector3F(N, -N, -N), Red);
    builder.Add(Vector3F(N, -N, N), Red);

    builder.Add(Vector3F(N, N, N), Green);
    builder.Add(Vector3F(N, -N, N), Green);
    builder.Add(Vector3F(-N, -N, N), Green);

    builder.Add(Vector3F(N, N, N), Green);
    builder.Add(Vector3F(-N, -N, N), Green);
    builder.Add(Vector3F(-N, N, N), Green);

    builder.Add(Vector3F(N, N, N), Blue);
    builder.Add(Vector3F(-N, N, N), Blue);
    builder.Add(Vector3F(-N, N, -N), Blue);

    builder.Add(Vector3F(N, N, N), Blue);
    builder.Add(Vector3F(-N, N, -N), Blue);
    builder.Add(Vector3F(N, N, -N), Blue);

    builder.Add(Vector3F(-N, -N, -N), Cyan);
    builder.Add(Vector3F(-N, N, -N), Cyan);
    builder.Add(Vector3F(-N, N, N), Cyan);

    builder.Add(Vector3F(-N, -N, -N), Cyan);
    builder.Add(Vector3F(-N, N, N), Cyan);
    builder.Add(Vector3F(-N, -N, N), Cyan);

    builder.Add(Vector3F(-N, -N, -N), Magenta);
    builder.Add(Vector3F(N, -N, -N), Magenta);
    builder.Add(Vector3F(N, N, -N), Magenta);

    builder.Add(Vector3F(-N, -N, -N), Magenta);
    builder.Add(Vector3F(N, N, -N), Magenta);
    builder.Add(Vector3F(-N, N, -N), Magenta);

    builder.Add(Vector3F(-N, -N, -N), Yellow);
    builder.Add(Vector3F(-N, -N, N), Yellow);
    builder.Add(Vector3F(N, -N, N), Yellow);

    builder.Add(Vector3F(-N, -N, -N), Yellow);
    builder.Add(Vector3F(N, -N, N), Yellow);
    builder.Add(Vector3F(N, -N, -N), Yellow);

    return SimpleBufferObject(builder);
}

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
    (void)BuildPyramid;
    _cubeObject = BuildCube();

    SimpleBuilder builder;

    builder.Add(Vector3F(-7.0f, 0.0f, 0.0f), Black);
    builder.Add(Vector3F(7.0f, 0.0f, 0.0f), Black);
    builder.Add(Vector3F(0.0f, -7.0f, 0.0f), Black);
    builder.Add(Vector3F(0.0f, 7.0f, 0.0f), Black);

    _linesObject = SimpleBufferObject(builder);

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
                //.Scale(0.125f, 1.0f, 0.5f)
                //.RotateX(RotationF::FromDegrees(45.0f))
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
