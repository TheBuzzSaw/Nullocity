#include "../include/SDL2TK/OpenAL/AudioBuffer.hpp"
#include "../include/SDL2TK/Tools.hpp"
#include <cstring>

namespace SDL2TK
{
    AudioBuffer::AudioBuffer()
        : _buffer(0)
    {
    }

    AudioBuffer::AudioBuffer(AudioBuffer&& other)
        : _buffer(other._buffer)
    {
        other._buffer = 0;
    }

    AudioBuffer::~AudioBuffer()
    {
        alDeleteBuffers(1, &_buffer);
    }

    AudioBuffer& AudioBuffer::operator=(AudioBuffer&& other)
    {
        if (this != &other)
        {
            alDeleteBuffers(1, &_buffer);
            _buffer = other._buffer;
            other._buffer = 0;
        }

        return *this;
    }

    AudioBuffer AudioBuffer::FromWavFile(const char* path)
    {
        AudioBuffer result;

        auto content = GetFileContent(path);
        char* data = content.data();

        if (content.size() > 44
            && !memcmp(data, "RIFF", 4)
            && !memcmp(data + 8, "WAVEfmt ", 8))
        {
            int format = Convert<short>(data + 20);
            //int channels = Convert<short>(data + 22);
            int sampleRate = Convert<int>(data + 24);
            //int byteRate = Convert<int>(data + 28);
            int bitsPerSample = Convert<short>(data + 34);

            size_t offset = 0;

            if (bitsPerSample != 16)
                offset = Convert<short>(data + 36);

            if (!memcmp(data + 36 + offset, "data", 4))
            {
                int dataChunkSize = Convert<int>(data + 40 + offset);

                if (dataChunkSize > 0)
                {
                    alGenBuffers(1, &result._buffer);

                    ALenum alFormat =
                        format == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

                    alBufferData(
                        result._buffer,
                        alFormat,
                        data + 44 + offset,
                        dataChunkSize,
                        sampleRate * 2);
                }
            }
        }

        return std::move(result);
    }
}
