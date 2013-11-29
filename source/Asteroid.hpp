#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <SDL2TK/Rotation.hpp>
#include <SDL2TK/Vector.hpp>

class Asteroid
{
    public:
        Asteroid();
        ~Asteroid();
    protected:
    private:
        SDL2TK::Vector2F _position;
};

#endif
