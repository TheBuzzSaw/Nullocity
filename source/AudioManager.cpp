#include "AudioManager.hpp"

const int AudioManager::LuaKeyBase = 0xBADC0DE;

AudioManager::AudioManager(std::size_t sourceCount, LuaState& lua)
    : _lua(lua)
    , _nextSource(0)
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

void AudioManager::InitializeLua()
{
    _lua.SetUserData((void*)&LuaKeyBase, this);
    _lua.AddFunction(GetAudioBuffer, "GetAudioBuffer");
    _lua.AddFunction(PlayAudioBuffer, "PlayAudioBuffer");
}

AudioManager& AudioManager::FromLua(lua_State* state)
{
    void* raw = LuaState::GetUserData(state, (void*)&LuaKeyBase);
    return *reinterpret_cast<AudioManager*>(raw);
}

int AudioManager::GetAudioBuffer(lua_State* state)
{
    const SDL2TK::AudioBuffer* buffer = nullptr;
    auto argc = lua_gettop(state);

    if (argc > 0 && lua_isstring(state, 1))
    {
        const char* path = lua_tostring(state, 1);
        AudioManager& am = AudioManager::FromLua(state);

        buffer = am.GetBuffer(path);
    }

    if (buffer)
        lua_pushlightuserdata(state, (void*)buffer);
    else
        lua_pushnil(state);

    return 1;
}

int AudioManager::PlayAudioBuffer(lua_State* state)
{
    auto argc = lua_gettop(state);
    if (argc > 0 && lua_islightuserdata(state, 1))
    {
        auto buffer =
            (const SDL2TK::AudioBuffer*)lua_touserdata(state, 1);

        AudioManager& am = AudioManager::FromLua(state);
        am.Play(buffer);
    }
    return 0;
}
