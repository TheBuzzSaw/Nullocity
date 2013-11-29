#include <SDL2TK/Window.hpp>
#include "GameModule.hpp"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    {
        SDL2TK::WindowSettings settings;
        settings.Title("Nullocity");

        SDL2TK::Window window(std::move(settings));
        GameModule module;
        window.Run(module);
    }
    SDL_Quit();

    return 0;
}
