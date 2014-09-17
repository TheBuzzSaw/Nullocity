#include "../include/SDL2TK/OpenAL/AudioSource.hpp"

namespace SDL2TK
{
    AudioSource::AudioSource()
        : _source(0)
    {
        alGenSources(1, &_source);
    }

    AudioSource::AudioSource(AudioSource&& other)
        : _source(other._source)
    {
        other._source = 0;
    }

    AudioSource::~AudioSource()
    {
        if (_source != 0) alDeleteSources(1, &_source);
    }

    AudioSource& AudioSource::operator=(AudioSource&& other)
    {
        if (this != &other)
        {
            if (_source != 0) alDeleteSources(1, &_source);
            _source = other._source;
            other._source = 0;
        }

        return *this;
    }

    AudioSource& AudioSource::Bind(const AudioBuffer& buffer)
    {
        alSourcei(_source, AL_BUFFER, buffer._buffer);
        return *this;
    }

    AudioSource& AudioSource::Play()
    {
        alSourcePlay(_source);
        return *this;
    }

    AudioSource& AudioSource::Pause()
    {
        alSourcePause(_source);
        return *this;
    }

    AudioSource& AudioSource::Stop()
    {
        alSourceStop(_source);
        return *this;
    }

    AudioSource& AudioSource::Rewind()
    {
        alSourceRewind(_source);
        return *this;
    }
}
