#include <SDL2TK/Window.hpp>
#include <SDL_image.h>
#include "GameModule.hpp"
#include <iostream>
using namespace std;

void Start()
{
    SDL2TK::WindowSettings settings;
    settings.Title("Nullocity 0.1");
    settings.Width(800);
    settings.Height(600);

    SDL2TK::Window window(std::move(settings));
    GameModule module;
    window.Run(module);
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);

    Start();

    IMG_Quit();
    SDL_Quit();

    return 0;
}
