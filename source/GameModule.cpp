#include "GameModule.hpp"
#include <SDL2TK/Matrix4x4.hpp>
using namespace std;
using namespace SDL2TK;

GameModule::GameModule()
{
    SimpleBuilder builder;

    Vector3F top(0.0f, 1.0f, 0.0f);
    RotationF rotation = RotationF::FromDegrees(-120.0f);

    Vector3F left;
    {
        Matrix4x4F matrix;
        matrix.RotateZ(-rotation);
        matrix.Transform(top, left);
    }

    Vector3F right;
    {
        Matrix4x4F matrix;
        matrix.RotateZ(rotation);
        matrix.Transform(top, right);
    }

    cout << rotation.ToDegrees() << endl;
    cout << top << '\n' << right << '\n' << left << endl;

    builder.Add(top, Vector4F(1.0f, 0.0f, 0.0f, 1.0f));
    builder.Add(right, Vector4F(0.0f, 1.0f, 0.0f, 1.0f));
    builder.Add(left, Vector4F(0.0f, 0.0f, 1.0f, 1.0f));

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
    _rotation += Rotation<GLfloat>::FromDegrees(2.0f);

    Matrix4x4F matrix;
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

    Matrix4x4F matrix;
    matrix.Orthographic(8.0f, aspectRatio);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
}
