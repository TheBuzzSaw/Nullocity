#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <SDL2TK/Rotation.hpp>
#include <SDL2TK/Vector.hpp>

class Asteroid
{
    public:
        Asteroid();
        ~Asteroid();

        void Update();

        const SDL2TK::Vector2F Position() const { return _position; }
        const SDL2TK::RotationF RotationX() const { return _rotationX; }
        const SDL2TK::RotationF RotationY() const { return _rotationY; }

    protected:
    private:
        SDL2TK::Vector2F _position;
        SDL2TK::RotationF _rotationX;
        SDL2TK::RotationF _rotationY;

        SDL2TK::Vector2F _velocity;
        SDL2TK::RotationF _torqueX;
        SDL2TK::RotationF _torqueY;
};

#endif
