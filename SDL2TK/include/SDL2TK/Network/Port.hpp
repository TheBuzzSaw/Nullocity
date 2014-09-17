#ifndef PORT_HPP
#define PORT_HPP

#include <SDL_stdinc.h>

namespace SDL2TK
{
    class Port
    {
        public:
            constexpr Port() : _port(0) {}
            constexpr Port(const Port&) = default;
            ~Port() = default;

            Port& operator=(const Port&) = default;

            constexpr Uint16 NetworkValue() const { return _port; }
            Uint16 HostValue() const;

            static const Port FromHostValue(Uint16 networkValue);

            static constexpr const Port FromNetworkValue(Uint16 hostValue)
            {
                return Port(hostValue);
            }

        private:
            explicit constexpr Port(Uint16 hostValue) : _port(hostValue) {}
            Uint16 _port;
    };
}

#endif
