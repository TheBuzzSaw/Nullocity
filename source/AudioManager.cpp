#include "AudioManager.hpp"

AudioManager::AudioManager(std::size_t sourceCount)
    : _nextSource(0)
{
    _sources.resize(sourceCount);
}

AudioManager::~AudioManager()
{
}

const SDL2TK::AudioBuffer* AudioManager::GetBuffer(std::string path)
{
    SDL2TK::AudioBuffer* result = nullptr;
    auto i = _buffersByPath.find(path);

    if (i == _buffersByPath.end())
    {
        SDL2TK::AudioBuffer buffer =
            SDL2TK::AudioBuffer::FromWavFile(path.c_str());

        if (buffer.HasContent())
        {
            SDL2TK::AudioBuffer& insertion =
                (_buffersByPath[std::move(path)] = std::move(buffer));

            result = &insertion;
            _buffers.insert(result);
        }
    }
    else
    {
        result = &i->second;
    }

    return result;
}

void AudioManager::Play(const SDL2TK::AudioBuffer* buffer)
{
    if (_buffers.count(buffer) == 1)
    {
        _sources[_nextSource].Bind(*buffer).Play();
        _nextSource = (_nextSource + 1) % _sources.size();
    }
}
