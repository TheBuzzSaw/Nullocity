#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "OpenGL/glew.h"
#include "Surface.hpp"
#include "Module.hpp"
#include "WindowSettings.hpp"

namespace SDL2TK
{
    class Window
    {
        public:
            Window();
            Window(WindowSettings settings);
            Window(Window&& other);
            ~Window();

            Window& operator=(Window&& other);

            void SetIcon(const Surface& surface);
            void Run(Module& module);

        private:
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

            SDL_Window* _window;
            SDL_GLContext* _context;
            WindowSettings _settings;
    };
}

#endif
