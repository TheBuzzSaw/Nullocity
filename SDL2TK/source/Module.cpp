#include "../include/SDL2TK/Module.hpp"

namespace SDL2TK
{
    Module::Module()
        : _isRunning(false)
        , _suppressSwap(false)
    {
        PulseInterval(TimeSpan::FromSeconds(1) / 30);
    }

    Module::~Module()
    {
    }

    void Module::OnOpen()
    {
    }

    void Module::OnClose()
    {
    }

    void Module::OnLoop()
    {
    }

    void Module::OnPulse()
    {
    }

    void Module::OnSecond(int framesPerSecond)
    {
        (void)framesPerSecond;
    }

    void Module::OnEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_ENTER: OnMouseFocus(); break;
                    case SDL_WINDOWEVENT_LEAVE: OnMouseBlur(); break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED: OnInputFocus(); break;
                    case SDL_WINDOWEVENT_FOCUS_LOST: OnInputBlur(); break;
                    case SDL_WINDOWEVENT_RESTORED: OnRestore(); break;
                    case SDL_WINDOWEVENT_MINIMIZED: OnMinimize(); break;
                    case SDL_WINDOWEVENT_MAXIMIZED: OnMaximize(); break;
                    case SDL_WINDOWEVENT_EXPOSED: OnExpose(); break;

                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        OnResize(event.window.data1, event.window.data2);
                        break;

                    default: break;
                }

                break;
            }

            case SDL_KEYDOWN:
                if (event.key.repeat)
                    OnKeyRepeat(event.key.keysym);
                else
                    OnKeyDown(event.key.keysym);
                break;

            case SDL_KEYUP: OnKeyUp(event.key.keysym); break;
            case SDL_MOUSEMOTION: OnMouseMove(event.motion); break;
            case SDL_MOUSEWHEEL: OnMouseWheel(event.wheel); break;
            case SDL_MOUSEBUTTONDOWN: OnMouseButtonDown(event.button); break;
            case SDL_MOUSEBUTTONUP: OnMouseButtonUp(event.button); break;

            case SDL_JOYAXISMOTION: OnJoyAxis(event.jaxis); break;
            case SDL_JOYBALLMOTION: OnJoyBall(event.jball); break;
            case SDL_JOYHATMOTION: OnJoyHat(event.jhat); break;
            case SDL_JOYBUTTONDOWN: OnJoyButtonDown(event.jbutton); break;
            case SDL_JOYBUTTONUP: OnJoyButtonUp(event.jbutton); break;
            case SDL_QUIT: OnExit(); break;
            case SDL_SYSWMEVENT: break;

            default: OnUser(event.user);break;
        }
    }

    void Module::OnInputFocus()
    {
    }

    void Module::OnInputBlur()
    {
    }

    void Module::OnKeyDown(const SDL_Keysym& keysym)
    {
        if (keysym.sym == SDLK_ESCAPE) Stop();
    }

    void Module::OnKeyRepeat(const SDL_Keysym& keysym)
    {
        (void)keysym;
    }

    void Module::OnKeyUp(const SDL_Keysym& keysym)
    {
        (void)keysym;
    }

    void Module::OnMouseFocus()
    {
    }

    void Module::OnMouseBlur()
    {
    }

    void Module::OnMouseMove(const SDL_MouseMotionEvent& event)
    {
        (void)event;
    }

    void Module::OnMouseWheel(const SDL_MouseWheelEvent& event)
    {
        (void)event;
    }

    void Module::OnMouseButtonDown(const SDL_MouseButtonEvent& event)
    {
        (void)event;
    }

    void Module::OnMouseButtonUp(const SDL_MouseButtonEvent& event)
    {
        (void)event;
    }

    void Module::OnJoyAxis(const SDL_JoyAxisEvent& event)
    {
        (void)event;
    }

    void Module::OnJoyButtonDown(const SDL_JoyButtonEvent& event)
    {
        (void)event;
    }

    void Module::OnJoyButtonUp(const SDL_JoyButtonEvent& event)
    {
        (void)event;
    }

    void Module::OnJoyHat(const SDL_JoyHatEvent& event)
    {
        (void)event;
    }

    void Module::OnJoyBall(const SDL_JoyBallEvent& event)
    {
        (void)event;
    }

    void Module::OnMinimize()
    {
    }

    void Module::OnMaximize()
    {
    }

    void Module::OnRestore()
    {
    }

    void Module::OnResize(int width, int height)
    {
        (void)width;
        (void)height;
    }

    void Module::OnExpose()
    {
    }

    void Module::OnExit()
    {
        Stop();
    }

    void Module::OnUser(const SDL_UserEvent& event)
    {
        (void)event;
    }
}
