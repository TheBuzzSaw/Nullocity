#include "Asteroid.hpp"
#include <random>
using namespace SDL2TK;

static const float Max = 16.0f;

Asteroid::Asteroid()
{
    static std::mt19937 generator;
    std::uniform_real_distribution<float> distribution(-Max, Max);

    _position.X(distribution(generator));
    _position.Y(distribution(generator));

    _velocity.X(distribution(generator) / 64.0f);
    _velocity.Y(distribution(generator) / 64.0f);

    distribution = std::uniform_real_distribution<float>(-RotationF::Pi,
        RotationF::Pi);

    _rotation.X(distribution(generator));
    _rotation.Y(distribution(generator));

    _torque.X(distribution(generator) / 40.0f);
    _torque.Y(distribution(generator) / 40.0f);
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
{
    _position += _velocity;

    float x = _position.X();
    if (_velocity.X() > 0.0f && x > Max)
        _position.X(x - Max - Max);
    else if (_velocity.X() < 0.0f && x < -Max)
        _position.X(x + Max + Max);

    float y = _position.Y();
    if (_velocity.Y() > 0.0f && y > Max)
        _position.Y(y - Max - Max);
    else if (_velocity.Y() < 0.0f && y < -Max)
        _position.X(y + Max + Max);

    RotationF rx = RotationF::FromRadians(_rotation.X());
    rx += RotationF::FromRadians(_torque.X());
    _rotation.X(rx.ToRadians());

    RotationF ry = RotationF::FromRadians(_rotation.Y());
    ry += RotationF::FromRadians(_torque.Y());
    _rotation.Y(ry.ToRadians());
}
