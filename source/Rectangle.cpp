#include "Rectangle.hpp"

Rectangle::Rectangle(SDL2TK::Vector2F center, SDL2TK::Vector2F radii)
    : _center(center)
    , _radii(radii)
{
}

const Rectangle Rectangle::UpperLeft() const
{
    auto radii = _radii / 2.0f;
    SDL2TK::Vector2F center(_center.X() - radii.X(), _center.Y() + radii.Y());
    return Rectangle(center, radii);
}

const Rectangle Rectangle::UpperRight() const
{
    auto radii = _radii / 2.0f;
    SDL2TK::Vector2F center(_center.X() + radii.X(), _center.Y() + radii.Y());
    return Rectangle(center, radii);
}

const Rectangle Rectangle::LowerLeft() const
{
    auto radii = _radii / 2.0f;
    SDL2TK::Vector2F center(_center.X() - radii.X(), _center.Y() - radii.Y());
    return Rectangle(center, radii);
}

const Rectangle Rectangle::LowerRight() const
{
    auto radii = _radii / 2.0f;
    SDL2TK::Vector2F center(_center.X() + radii.X(), _center.Y() - radii.Y());
    return Rectangle(center, radii);
}
