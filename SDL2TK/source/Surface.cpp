#include "../include/SDL2TK/Surface.hpp"
#include <utility>

namespace SDL2TK
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    static const Uint32 RedMask   = 0xff000000;
    static const Uint32 GreenMask = 0x00ff0000;
    static const Uint32 BlueMask  = 0x0000ff00;
    static const Uint32 AlphaMask = 0x000000ff;
#else
    static const Uint32 RedMask   = 0x000000ff;
    static const Uint32 GreenMask = 0x0000ff00;
    static const Uint32 BlueMask  = 0x00ff0000;
    static const Uint32 AlphaMask = 0xff000000;
#endif

    static SDL_Surface* CopySurface(SDL_Surface* surface)
    {
        return SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    }

    Surface::Surface()
        : _surface(nullptr)
    {
    }

    Surface::Surface(const char* filename)
        : _surface(nullptr)
    {
        if (filename && *filename)
        {
            // Needs to be updated to use SDL2_image.
            SDL_Surface* raw = SDL_LoadBMP(filename);

            if (raw)
            {
                // Convert the image from its native format to our desired
                // format.

                _surface = CopySurface(raw);
                SDL_FreeSurface(raw);
            }
        }
    }

    Surface::Surface(int width, int height)
        : _surface(nullptr)
    {
        if (width > 0 && height > 0)
        {
            _surface = SDL_CreateRGBSurface(0, width, height, 32, RedMask,
                GreenMask, BlueMask, AlphaMask);
        }
    }

    Surface::Surface(SDL_Surface* surface)
        : _surface(surface)
    {
    }

    Surface::Surface(Surface&& other)
        : _surface(other._surface)
    {
        other._surface = nullptr;
    }

    Surface::Surface(const Surface& other)
        : _surface(nullptr)
    {
        if (other._surface)
        {
            _surface = CopySurface(other._surface);
        }
    }

    Surface::~Surface()
    {
        SDL_FreeSurface(_surface);
    }

    Surface& Surface::operator=(Surface&& other)
    {
        if (this != &other)
        {
            SDL_FreeSurface(_surface);
            _surface = other._surface;
            other._surface = nullptr;
        }

        return *this;
    }

    Surface& Surface::operator=(const Surface& other)
    {
        if (this != &other)
        {
            SDL_FreeSurface(_surface);
            _surface = CopySurface(other._surface);
        }

        return *this;
    }

    void Surface::LoadIntoTexture(GLenum target) const
    {
        if (_surface)
        {
            glTexImage2D(target, 0, GL_RGBA, _surface->w, _surface->h, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, _surface->pixels);
        }
    }
}
