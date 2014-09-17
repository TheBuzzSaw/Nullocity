#include <SDL2TK/Window.hpp>
#include <SDL2TK/OpenAL/AudioContext.hpp>
#include <SDL2TK/Network/Port.hpp>
#include <SDL2TK/Network/Address32.hpp>
#include "GameModule.hpp"
#include <iostream>
using namespace std;

void Start()
{
    SDL2TK::WindowSettings settings;
    settings.Title("Nullocity 0.2");
    settings.Width(1024);
    settings.Height(768);

    SDL2TK::Window window(std::move(settings));
    GameModule module;
    window.Run(module);
}

void TestNetwork()
{
    SDL2TK::Address32 home(127, 0, 0, 1);
    SDL2TK::Port a = SDL2TK::Port::FromHostValue(555);
    cout << home << endl;
    cout << a.HostValue() << endl;
    cout << a.NetworkValue() << endl;
}

int main(int argc, char** argv)
{
    TestNetwork();

    SDL2TK::AudioDevice device;
    if (device.IsOpen())
    {
        SDL2TK::AudioContext context(device);

        if (context.IsOpen())
        {
            cerr << "OpenAL context is open.\n";
        }

        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

        Start();

        SDL_Quit();
    }
    else
    {
        cerr << "Failed to open audio device.\n";
    }

    return 0;
}
