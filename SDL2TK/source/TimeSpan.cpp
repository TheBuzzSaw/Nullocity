#include "../include/SDL2TK/TimeSpan.hpp"
#include <SDL.h>

namespace SDL2TK
{
    TimeSpan& TimeSpan::operator=(const TimeSpan& other)
    {
        _ticks = other._ticks;
        return *this;
    }

    TimeSpan& TimeSpan::operator+=(const TimeSpan& other)
    {
        _ticks += other._ticks;
        return *this;
    }

    TimeSpan& TimeSpan::operator-=(const TimeSpan& other)
    {
        _ticks -= other._ticks;
        return *this;
    }

    TimeSpan& TimeSpan::operator*=(int64_t multiplier)
    {
        _ticks *= multiplier;
        return *this;
    }

    TimeSpan& TimeSpan::operator/=(int64_t divisor)
    {
        _ticks /= divisor;
        return *this;
    }

    const TimeSpan TimeSpan::FromSDL()
    {
        return FromMilliseconds(SDL_GetTicks());
    }
}
