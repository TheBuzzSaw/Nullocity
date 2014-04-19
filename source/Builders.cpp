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

    const float N = 16.0f;
    const int LineCount = 5;
    const int LaneCount = LineCount - 1;

    for (int i = 0; i < LineCount; ++i)
    {
        float ratio = float(i) / float(LaneCount);
        float n = N * (2.0f * ratio - 1.0f);

        builder.Add(Vector3F(-N, n, 0.0f), Black);
        builder.Add(Vector3F(N, n, 0.0f), Black);
        builder.Add(Vector3F(n, -N, 0.0f), Black);
        builder.Add(Vector3F(n, N, 0.0f), Black);
    }

    return SimpleBufferObject(builder);
}

static const GLfloat IX = 0.525731112119133606f;
static const GLfloat IZ = 0.850650808352039932f;

static const Vector3F IV[12] = {
    Vector3F(-IX, 0.0f, IZ),
    Vector3F(IX, 0.0f, IZ),
    Vector3F(-IX, 0.0f, -IZ),
    Vector3F(IX, 0.0f, -IZ),
    Vector3F(0.0f, IZ, IX),
    Vector3F(0.0f, IZ, -IX),
    Vector3F(0.0f, -IZ, IX),
    Vector3F(0.0f, -IZ, -IX),
    Vector3F(IZ, IX, 0.0f),
    Vector3F(-IZ, IX, 0.0f),
    Vector3F(IZ, -IX, 0.0f),
    Vector3F(-IZ, -IX, 0.0)
    };

static const int II[20][3] =
    {{1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4},
     {1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2},
     {3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0},
     {10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7}};

void Subdivide(SimpleBuilder& builder, const Vector3F& a, const Vector3F& b,
    const Vector3F& c, int detail)
{
    if (detail-- > 0)
    {
        Vector3F ab = ((a + b) / 2.0f).Normalized();
        Vector3F bc = ((b + c) / 2.0f).Normalized();
        Vector3F ca = ((c + a) / 2.0f).Normalized();

        Subdivide(builder, a, ab, ca, detail);
        Subdivide(builder, b, bc, ab, detail);
        Subdivide(builder, c, ca, bc, detail);
        Subdivide(builder, ab, bc, ca, detail);
    }
    else
    {
        builder.Add(a, Red);
        builder.Add(b, Green);
        builder.Add(c, Blue);
    }
}

SimpleBufferObject BuildSphere(int detail)
{
    SimpleBuilder builder;

    for (int i = 0; i < 20; ++i)
        Subdivide(builder, IV[II[i][2]], IV[II[i][1]], IV[II[i][0]], detail);

    return SimpleBufferObject(builder);
}

SimpleBufferObject BuildSphere()
{
    return BuildSphere(2);
}

SimpleBufferObject BuildIcosahedron()
{
    return BuildSphere(0);
}
