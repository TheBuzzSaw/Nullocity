#include <SDL2TK/Window.hpp>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    {
        SDL2TK::Window window;
        SDL2TK::Module module;
        window.Run(module);
    }
    SDL_Quit();

    return 0;
}
