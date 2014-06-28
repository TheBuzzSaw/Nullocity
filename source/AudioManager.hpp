#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "LuaState.hpp"
#include <SDL2TK/OpenAL/AudioSource.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class AudioManager
{
    public:
        AudioManager(std::size_t sourceCount, LuaState& lua);
        ~AudioManager();

        const SDL2TK::AudioBuffer* GetBuffer(std::string path);
        void Play(const SDL2TK::AudioBuffer* buffer);

        void InitializeLua();

    protected:
    private:
        AudioManager(const AudioManager&) = delete;
        AudioManager(AudioManager&&) = delete;

        AudioManager& operator=(const AudioManager&) = delete;
        AudioManager& operator=(AudioManager&&) = delete;

        LuaState& _lua;

        std::vector<SDL2TK::AudioSource> _sources;
        std::unordered_set<const SDL2TK::AudioBuffer*> _buffers;
        std::unordered_map<std::string, SDL2TK::AudioBuffer> _buffersByPath;
        std::size_t _nextSource;

        static const int LuaKeyBase;
        static AudioManager& FromLua(lua_State* state);
        static int GetAudioBuffer(lua_State* state);
        static int PlayAudioBuffer(lua_State* state);
};

#endif
