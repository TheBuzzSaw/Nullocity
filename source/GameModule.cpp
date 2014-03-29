#include "Builders.hpp"
#include "GameModule.hpp"
#include <SDL2TK/Matrix4x4.hpp>
#include <SDL2TK/Rotation.hpp>
#include <SDL2TK/Vector.hpp>
#include <random>

using namespace std;
using namespace SDL2TK;

static const RotationF TurnSpeed = RotationF::FromDegrees(4.0f);
static const float Max = 16.0f;

const int GameModule::KeyBase = 0xBADC0DE;

GameModule::GameModule()
{
    //(void)BuildPyramid;
    _cubeObject = BuildCube();
    _squarePyramidObject = BuildSquarePyramid();
    _linesObject = BuildLines();

    _camera.Distance(32.0f);
    _camera.Vertical(RotationF::FromDegrees(-45.0f));

    _lua.SetUserData((void*)&KeyBase, this);
    _lua.AddFunction(AddEntity, "AddEntity");
    _lua.AddFunction(SetPosition, "SetPosition");
    _lua.AddFunction(SetVelocity, "SetVelocity");
    _lua.AddFunction(SetRotation, "SetRotation");
    _lua.AddFunction(SetTorque, "SetTorque");
    _lua.AddFunction(GetRandom, "GetRandom");
}

GameModule::~GameModule()
{
    for (auto i : _asteroids) delete i;
}

void GameModule::OnOpen()
{
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glLineWidth(8.0f);

    const float N = 1.0f / 8.0f;
    glClearColor(N, N, N, 1.0f);

    _lua.ExecuteFile("main.lua");
}

void GameModule::OnClose()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

void GameModule::OnLoop()
{
    Matrix4x4F matrix;
    _camera.Apply(matrix);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program.Open();

    glLoadMatrixf(
        Matrix4x4F(matrix)
            .RotateZ(_playerRotation)
            .RotateX(RotationF::FromDegrees(-90.0f))
            .Scale(1.0f, 0.5f, 2.0f));

    _program.Draw(_squarePyramidObject, GL_TRIANGLES);

    for (auto& asteroid : _asteroids)
    {
        Vector2F position = asteroid->Position();
        glLoadMatrixf(
            Matrix4x4F(matrix)
                .Translate(position.X(), position.Y(), 0.0f)
                .RotateX(asteroid->RotationX())
                .RotateY(asteroid->RotationY())
                );

        _program.Draw(_cubeObject, GL_TRIANGLES);
    }

    glLoadMatrixf(matrix);
    _program.Draw(_linesObject, GL_LINES);

    _program.Close();
}

void GameModule::OnPulse()
{
    _playerRotation += _playerTorque;
    _camera.Horizontal(-_playerRotation);

    for (auto asteroid : _asteroids)
    {
        asteroid->Update();
        FixPosition(*asteroid);
    }

    LHC.CheckCollisions();
}

void GameModule::OnSecond(int framesPerSecond)
{
}

void GameModule::OnKeyDown(const SDL_Keysym& keysym)
{
    switch (keysym.sym)
    {
        case SDLK_ESCAPE:
            Stop();
            break;

        case SDLK_LEFT:
            _playerTorque = TurnSpeed;
            break;

        case SDLK_RIGHT:
            _playerTorque = -TurnSpeed;
            break;

        case SDLK_w:
            break;

        case SDLK_a:
            break;

        default:
            break;
    }
}

void GameModule::OnKeyUp(const SDL_Keysym& keysym)
{
    switch (keysym.sym)
    {
        case SDLK_LEFT:
            if (_playerTorque.ToRadians() > 0.0f)
                _playerTorque = RotationF();
            break;

        case SDLK_RIGHT:
            if (_playerTorque.ToRadians() < 0.0f)
                _playerTorque = RotationF();
            break;

        case SDLK_w:
            break;

        case SDLK_a:
            break;

        default:
            break;
    }
}

void GameModule::OnResize(int width, int height)
{
    float aspectRatio = float(width) / float(height);

    glViewport(0, 0, width, height);

    Matrix4x4F matrix;
    matrix.Perspective(RotationF::FromDegrees(30.0f), aspectRatio, 1.0f,
        100.0f);
    //matrix.Orthographic(8.0f, aspectRatio);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void GameModule::FixPosition(Entity& entity)
{
    SDL2TK::Vector2F position = entity.Position();
    SDL2TK::Vector2F velocity = entity.Velocity();
    float x = position.X();
    bool jumpPosition = false;
    if (velocity.X() > 0.0f && x > Max)
    {
        position.X(x - Max - Max);
        jumpPosition = true;
    }
    else if (velocity.X() < 0.0f && x < -Max)
    {
        position.X(x + Max + Max);
        jumpPosition = true;
    }

    float y = position.Y();
    if (velocity.Y() > 0.0f && y > Max)
    {
        position.Y(y - Max - Max);
        jumpPosition = true;
    }
    else if (velocity.Y() < 0.0f && y < -Max)
    {
        position.X(y + Max + Max);
        jumpPosition = true;
    }

    if (jumpPosition)
    {
        entity.SetPositon(position);
    }
}

GameModule& GameModule::FromLua(lua_State* state)
{
    void* raw = LuaState::GetUserData(state, (void*)&KeyBase);
    return *reinterpret_cast<GameModule*>(raw);
}

int GameModule::AddEntity(lua_State* state)
{
    GameModule& gm = GameModule::FromLua(state);

    Entity* entity = new Entity(gm._cubeObject);
    gm._asteroids.insert(entity);
    gm.LHC.AddEntity(*entity);

    lua_pushlightuserdata(state, entity);

    return 1;
}

int GameModule::SetPosition(lua_State* state)
{
    GameModule& gm = GameModule::FromLua(state);

    auto argc = lua_gettop(state);
    if (argc > 2 && lua_isuserdata(state, 1) && lua_isnumber(state, 2)
        && lua_isnumber(state, 3))
    {
        Entity* entity = (Entity*)lua_touserdata(state, 1);

        if (gm._asteroids.count(entity) > 0)
        {
            auto x = lua_tonumber(state, 2);
            auto y = lua_tonumber(state, 3);
            entity->SetPositon(SDL2TK::Vector2F(x, y));
        }
    }

    return 0;
}

int GameModule::SetVelocity(lua_State* state)
{
    GameModule& gm = GameModule::FromLua(state);

    auto argc = lua_gettop(state);
    if (argc > 2 && lua_isuserdata(state, 1) && lua_isnumber(state, 2)
        && lua_isnumber(state, 3))
    {
        Entity* entity = (Entity*)lua_touserdata(state, 1);

        if (gm._asteroids.count(entity) > 0)
        {
            auto x = lua_tonumber(state, 2);
            auto y = lua_tonumber(state, 3);
            entity->SetVelocity(SDL2TK::Vector2F(x, y));
        }
    }

    return 0;
}

int GameModule::SetRotation(lua_State* state)
{
    GameModule& gm = GameModule::FromLua(state);

    auto argc = lua_gettop(state);
    if (argc > 2 && lua_isuserdata(state, 1) && lua_isnumber(state, 2)
        && lua_isnumber(state, 3))
    {
        Entity* entity = (Entity*)lua_touserdata(state, 1);

        if (gm._asteroids.count(entity) > 0)
        {
            auto x = lua_tonumber(state, 2);
            auto y = lua_tonumber(state, 3);
            entity->SetRotation(SDL2TK::RotationF::FromDegrees(x),
                SDL2TK::RotationF::FromDegrees(y));
        }
    }

    return 0;
}

int GameModule::SetTorque(lua_State* state)
{
    GameModule& gm = GameModule::FromLua(state);

    auto argc = lua_gettop(state);
    if (argc > 2 && lua_isuserdata(state, 1) && lua_isnumber(state, 2)
        && lua_isnumber(state, 3))
    {
        Entity* entity = (Entity*)lua_touserdata(state, 1);

        if (gm._asteroids.count(entity) > 0)
        {
            auto x = lua_tonumber(state, 2);
            auto y = lua_tonumber(state, 3);
            entity->SetTorque(SDL2TK::RotationF::FromDegrees(x),
                SDL2TK::RotationF::FromDegrees(y));
        }
    }

    return 0;
}

int GameModule::GetRandom(lua_State* state)
{
    auto argc = lua_gettop(state);
    if (argc > 1 && lua_isnumber(state, 1) && lua_isnumber(state, 2))
    {
        GameModule& gm = GameModule::FromLua(state);
        auto low = lua_tonumber(state, 1);
        auto high = lua_tonumber(state, 2);

        std::uniform_real_distribution<decltype(low)> distribution(low, high);
        auto result = distribution(gm._generator);
        lua_pushnumber(state, result);
    }
    else
    {
        lua_pushnil(state);
    }

    return 1;
}
