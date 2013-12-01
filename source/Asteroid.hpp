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

        SDL2TK::Vector2F Position() const { return _position; }
        SDL2TK::Vector2F Rotation() const { return _rotation; }

    protected:
    private:
        SDL2TK::Vector2F _position;
        SDL2TK::Vector2F _rotation;

        SDL2TK::Vector2F _velocity;
        SDL2TK::Vector2F _torque;
};

#endif
