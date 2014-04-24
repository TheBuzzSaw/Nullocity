#ifndef KEYNAMES_HPP
#define KEYNAMES_HPP

#include <SDL.h>

struct KeyName
{
    const char* name;
    SDL_Keycode keycode;
};

const KeyName* GetKeyNames();

#endif
