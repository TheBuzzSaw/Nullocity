#ifndef AUDIOCONTEXT_HPP
#define AUDIOCONTEXT_HPP

#include "AudioDevice.hpp"

namespace SDL2TK
{
    class AudioContext
    {
        public:
            AudioContext(const AudioDevice& device);
            AudioContext(AudioContext&& other);
            ~AudioContext();

            AudioContext& operator=(AudioContext&& other);

            bool MakeCurrent() const;

            inline bool IsOpen() const { return _context != nullptr; }

        private:
            AudioContext(const AudioContext&) = delete;
            AudioContext& operator=(const AudioContext&) = delete;

            ALCcontext* _context;
    };
}

#endif
