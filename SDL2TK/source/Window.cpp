#include "../include/SDL2TK/Window.hpp"

namespace SDL2TK
{
    Window::Window()
        : Window(WindowSettings())
    {
    }

    Window::Window(WindowSettings settings)
        : _window(nullptr)
        , _context(nullptr)
        , _settings(std::move(settings))
    {
        _window = SDL_CreateWindow(
            _settings.Title().c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _settings.Width(),
            _settings.Height(),
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        _context = (SDL_GLContext*)SDL_GL_CreateContext(_window);
        SDL_GL_SetSwapInterval(1);

        GLenum e = glewInit();
        (void)e;
    }

    Window::Window(Window&& other)
        : _window(other._window)
        , _context(other._context)
        , _settings(std::move(other._settings))
    {
        other._window = nullptr;
        other._context = nullptr;
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(_context);
        SDL_DestroyWindow(_window);
    }

    Window& Window::operator=(Window&& other)
    {
        if (this != &other)
        {
            _window = other._window;
            _context = other._context;
            other._window = nullptr;
            other._context = nullptr;
        }

        return *this;
    }

    void Window::SetIcon(const Surface& surface)
    {
        SDL_SetWindowIcon(_window, surface._surface);
    }

    void Window::Run(Module& module)
    {
        module._isRunning = true;
        module.OnOpen();
        module.OnResize(_settings.Width(), _settings.Height());

        TimeSpan lastPulse = TimeSpan::FromSDL();
        while (module.IsRunning())
        {
            module._suppressSwap = false;
            SDL_Event event;

            while (SDL_PollEvent(&event)) module.OnEvent(event);

            TimeSpan interval = TimeSpan::FromSDL() - lastPulse;

            while (interval >= module.PulseInterval())
            {
                module.OnPulse();
                interval -= module.PulseInterval();
                lastPulse += module.PulseInterval();
            }

            module.OnLoop();

            if (!module._suppressSwap) SDL_GL_SwapWindow(_window);

            SDL_Delay(1);
        }

        module.OnClose();
    }
}
