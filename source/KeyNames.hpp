#ifndef KEYNAMES_HPP
#define KEYNAMES_HPP

#include <SDL_keycode.h>

struct KeyName
{
    const char* name;
    SDL_Keycode keycode;
};

const KeyName* GetKeyNames();

#endif
