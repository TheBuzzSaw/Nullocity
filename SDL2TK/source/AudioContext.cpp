#include "../include/SDL2TK/OpenAL/AudioContext.hpp"

namespace SDL2TK
{
    AudioContext::AudioContext(const AudioDevice& device)
        : _context(alcCreateContext(device._device, nullptr))
    {
        MakeCurrent();
    }

    AudioContext::AudioContext(AudioContext&& other)
        : _context(other._context)
    {
        other._context = nullptr;
    }

    AudioContext::~AudioContext()
    {
        if (_context != nullptr)
        {
            if (alcGetCurrentContext() == _context)
                alcMakeContextCurrent(nullptr);

            alcDestroyContext(_context);
        }
    }

    AudioContext& AudioContext::operator=(AudioContext&& other)
    {
        if (this != &other)
        {
            if (_context != nullptr)
            {
                if (alcGetCurrentContext() == _context)
                    alcMakeContextCurrent(nullptr);

                alcDestroyContext(_context);
            }

            _context = other._context;
            other._context = nullptr;
        }

        return *this;
    }

    bool AudioContext::MakeCurrent() const
    {
        return alcMakeContextCurrent(_context) == ALC_TRUE;
    }
}
