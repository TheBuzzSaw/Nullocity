#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP

#include "AudioBuffer.hpp"

namespace SDL2TK
{
    class AudioSource
    {
        public:
            AudioSource();
            AudioSource(AudioSource&& other);
            ~AudioSource();

            AudioSource& operator=(AudioSource&& other);

            AudioSource& Bind(const AudioBuffer& buffer);
            AudioSource& Play();
            AudioSource& Pause();
            AudioSource& Stop();
            AudioSource& Rewind();

        private:
            AudioSource(const AudioSource&) = delete;
            AudioSource& operator=(const AudioSource&) = delete;

            ALuint _source;
    };
}

#endif
