#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <SDL.h>
#include <SDL_opengl.h>

namespace SDL2TK
{
    class Surface
    {
        public:
            Surface();
            Surface(const char* filename);
            Surface(int width, int height);
            Surface(Surface&& other);
            Surface(const Surface& other);
            ~Surface();

            Surface& operator=(Surface&& other);
            Surface& operator=(const Surface& other);

            inline operator bool() const
            {
                return _surface != nullptr;
            }

            inline int Width() const
            {
                return _surface ? _surface->w : 0;
            }

            inline int Height() const
            {
                return _surface ? _surface->h : 0;
            }

            void LoadIntoTexture(GLenum target) const;

        private:
            Surface(SDL_Surface* surface);

            SDL_Surface* _surface;

            friend class Window;
    };
}

#endif

