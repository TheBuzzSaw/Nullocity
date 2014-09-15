#include "../include/SDL2TK/Network/Address32.hpp"

namespace SDL2TK
{
    Address32::Address32(Uint8 a, Uint8 b, Uint8 c, Uint8 d)
    {
        auto address = reinterpret_cast<Uint8*>(&_address);
        address[0] = a;
        address[1] = b;
        address[2] = c;
        address[3] = d;
    }

    std::ostream& operator<<(std::ostream& stream, const Address32& address32)
    {
        return stream
            << static_cast<int>(address32[0])
            << '.' << static_cast<int>(address32[1])
            << '.' << static_cast<int>(address32[2])
            << '.' << static_cast<int>(address32[3]);
    }
}
