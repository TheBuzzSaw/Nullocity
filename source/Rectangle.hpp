#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2TK/Vector.hpp>

class Rectangle
{
    public:
        Rectangle() = default;
        Rectangle(SDL2TK::Vector2F center, SDL2TK::Vector2F radii);
        Rectangle(const Rectangle&) = default;
        ~Rectangle() = default;

        Rectangle& operator=(const Rectangle&) = default;

        float Bottom() const { return _center.Y() - _radii.Y(); }
        float Top() const { return _center.Y() + _radii.Y(); }
        float Left() const { return _center.X() - _radii.X(); }
        float Right() const { return _center.X() + _radii.X(); }

        bool Contains(const Rectangle& other) const
        {
            return Top() >= other.Top()
                && Bottom() <= other.Bottom()
                && Right() >= other.Right()
                && Left() <= other.Left();
        }

        bool Avoids(const Rectangle& other) const
        {
            return (Top() < other.Bottom() || Bottom() > other.Top())
                && (Right() < other.Left() || Left() > other.Right());
        }

        const Rectangle UpperLeft() const;
        const Rectangle UpperRight() const;
        const Rectangle LowerLeft() const;
        const Rectangle LowerRight() const;

        const SDL2TK::Vector2F& Center() const { return _center; }
        const SDL2TK::Vector2F& Radii() const { return _radii; }

    protected:
    private:
        SDL2TK::Vector2F _center;
        SDL2TK::Vector2F _radii;
};

#endif
