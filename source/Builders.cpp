#include "Builders.hpp"
#include <SDL2TK/Vector.hpp>
using namespace SDL2TK;

static const float RootTwo = 1.414213562f;

static const Vector4F Black(0.0f, 0.0f, 0.0f, 1.0f);
static const Vector4F Red(1.0f, 0.0f, 0.0f, 1.0f);
static const Vector4F Green(0.0f, 1.0f, 0.0f, 1.0f);
static const Vector4F Blue(0.0f, 0.0f, 1.0f, 1.0f);
static const Vector4F Yellow(1.0f, 1.0f, 0.0f, 1.0f);
static const Vector4F Magenta(1.0f, 0.0f, 1.0f, 1.0f);
static const Vector4F Cyan(0.0f, 1.0f, 1.0f, 1.0f);

SimpleBufferObject BuildCube()
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

SimpleBufferObject BuildPyramid()
{
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

SimpleBufferObject BuildSquarePyramid()
{
    const float N = 1.0f;
    const float Z = N / RootTwo;

    Vector3F positions[5];

    positions[0] = Vector3F(N, N, -Z);
    positions[1] = Vector3F(N, -N, -Z);
    positions[2] = Vector3F(-N, -N, -Z);
    positions[3] = Vector3F(-N, N, -Z);
    positions[4] = Vector3F(0.0f, 0.0f, Z);

    SimpleBuilder builder;

    builder.Add(positions[0], Red);
    builder.Add(positions[1], Red);
    builder.Add(Vector3F(0.0f, 0.0f, Z), Red);

    builder.Add(positions[1], Green);
    builder.Add(positions[2], Green);
    builder.Add(Vector3F(0.0f, 0.0f, Z), Green);

    builder.Add(positions[2], Blue);
    builder.Add(positions[3], Blue);
    builder.Add(Vector3F(0.0f, 0.0f, Z), Blue);

    builder.Add(positions[3], Yellow);
    builder.Add(positions[0], Yellow);
    builder.Add(Vector3F(0.0f, 0.0f, Z), Yellow);

    builder.Add(positions[3], Black);
    builder.Add(positions[2], Black);
    builder.Add(positions[1], Black);

    builder.Add(positions[3], Black);
    builder.Add(positions[1], Black);
    builder.Add(positions[0], Black);

    return SimpleBufferObject(builder);
}

SimpleBufferObject BuildLines()
{
    SimpleBuilder builder;

    builder.Add(Vector3F(-7.0f, 0.0f, 0.0f), Black);
    builder.Add(Vector3F(7.0f, 0.0f, 0.0f), Black);
    builder.Add(Vector3F(0.0f, -7.0f, 0.0f), Black);
    builder.Add(Vector3F(0.0f, 7.0f, 0.0f), Black);

    return SimpleBufferObject(builder);
}
