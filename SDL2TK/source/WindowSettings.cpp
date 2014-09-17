#include "../include/SDL2TK/WindowSettings.hpp"

namespace SDL2TK
{
    WindowSettings::WindowSettings()
        : _title("CYBORUS SDL2TK")
        , _width(640)
        , _height(480)
    {
    }

    WindowSettings::WindowSettings(WindowSettings&& other)
        : _title(std::move(other._title))
        , _width(other._width)
        , _height(other._height)
    {
    }

    WindowSettings::WindowSettings(const WindowSettings& other)
        : _title(other._title)
        , _width(other._width)
        , _height(other._height)
    {
    }

    WindowSettings::~WindowSettings()
    {
    }

    WindowSettings& WindowSettings::operator=(WindowSettings&& other)
    {
        if (this != &other)
        {
            _title = std::move(other._title);
            _width = other._width;
            _height = other._height;
        }

        return *this;
    }

    WindowSettings& WindowSettings::operator=(const WindowSettings& other)
    {
        if (this != &other)
        {
            _title = other._title;
            _width = other._width;
            _height = other._height;
        }

        return *this;
    }
}
