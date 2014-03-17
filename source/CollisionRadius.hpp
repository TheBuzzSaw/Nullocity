#ifndef COLLISIONRADIUS_HPP
#define COLLISIONRADIUS_HPP

#include <SDL2TK/Vector.hpp>

template<typename T>
class CollisionRadius
{
    public:
        constexpr CollisionRadius() : _radius(0) {}
        constexpr CollisionRadius(const CollisionRadius&) = default;
        ~CollisionRadius() = default;

        CollisionRadius& operator=(const CollisionRadius&) = default;

        inline void Position(const SDL2TK::Vector2<T>& position)
        {
            _position = position;
        }

        inline void AdjustPosition(const SDL2TK::Vector2<T>& position)
        {
            _position += position;
        }

        constexpr const SDL2TK::Vector2<T>& Position() const
        {
            return _position;
        }

        inline void Radius(T radius) { _radius = radius; }
        constexpr T Radius() const { return _radius; }
        constexpr T RadiusSquared() const { return _radius * _radius; }

        bool Collides(const CollisionRadius& other) const
        {
            T radiusSquared = RadiusSquared() + other.RadiusSquared();

            auto rawDistance = _position - other._position;

            return rawDistance.LengthSquared() <= radiusSquared;
        }

    private:
        SDL2TK::Vector2<T> _position;
        T _radius;
};

#endif
