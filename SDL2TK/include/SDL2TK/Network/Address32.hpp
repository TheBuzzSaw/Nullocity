#ifndef ADDRESS32_HPP
#define ADDRESS32_HPP

#include <SDL_stdinc.h>
#include <cstdint>
#include <iostream>

namespace SDL2TK
{
    class Address32
    {
        public:
            constexpr Address32() : _address(0) {}
            Address32(Uint8 a, Uint8 b, Uint8 c, Uint8 d);
            constexpr Address32(const Address32&) = default;
            ~Address32() = default;

            Address32& operator=(const Address32&) = default;

            Uint8& operator[](size_t offset)
            {
                return reinterpret_cast<Uint8*>(&_address)[offset];
            }

            Uint8 operator[](size_t offset) const
            {
                return reinterpret_cast<const Uint8*>(&_address)[offset];
            }

        private:
            explicit constexpr Address32(Uint32 address)
                : _address(address) {}

            Uint32 _address;
    };

    std::ostream& operator<<(std::ostream& stream, const Address32& address32);
}

#endif

