#ifndef MODULE_HPP
#define MODULE_HPP

#include "TimeSpan.hpp"
#include <SDL.h>

namespace SDL2TK
{
    class Module
    {
        public:
            friend class Engine;

            Module();
            virtual ~Module();

            inline bool IsRunning() const
            {
                return _isRunning;
            }

            inline const TimeSpan PulseInterval() const
            {
                return _pulseInterval;
            }

            void OnEvent(const SDL_Event& event);

            /// module operation
            virtual void OnOpen();
            virtual void OnClose();
            virtual void OnLoop();
            virtual void OnPulse();
            virtual void OnSecond(int framesPerSecond);

            /// input events
            virtual void OnInputFocus();
            virtual void OnInputBlur();
            virtual void OnKeyDown(const SDL_Keysym& keysym);
            virtual void OnKeyRepeat(const SDL_Keysym& keysym);
            virtual void OnKeyUp(const SDL_Keysym& keysym);
            virtual void OnMouseFocus();
            virtual void OnMouseBlur();
            virtual void OnMouseMove(const SDL_MouseMotionEvent& event);
            virtual void OnMouseWheel(const SDL_MouseWheelEvent& event);
            virtual void OnMouseButtonDown(const SDL_MouseButtonEvent& event);
            virtual void OnMouseButtonUp(const SDL_MouseButtonEvent& event);
            virtual void OnJoyAxis(const SDL_JoyAxisEvent& event);
            virtual void OnJoyButtonDown(const SDL_JoyButtonEvent& event);
            virtual void OnJoyButtonUp(const SDL_JoyButtonEvent& event);
            virtual void OnJoyHat(const SDL_JoyHatEvent& event);
            virtual void OnJoyBall(const SDL_JoyBallEvent& event);
            virtual void OnMinimize();
            virtual void OnMaximize();
            virtual void OnRestore();
            virtual void OnResize(int width, int height);
            virtual void OnExpose();
            virtual void OnExit();
            virtual void OnUser(const SDL_UserEvent& event);

        protected:
            inline void Stop() { _isRunning = false; }
            inline void SuppressSwap() { _suppressSwap = true; }
            inline void PulseInterval(TimeSpan interval)
            {
                _pulseInterval = interval;
            }

        private:
            Module(const Module&);
            Module(Module&&);

            Module& operator=(const Module&);
            Module& operator=(Module&&);

            bool _isRunning;
            bool _suppressSwap;
            TimeSpan _pulseInterval;

            friend class Window;
    };

}

#endif
