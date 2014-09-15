#include "../include/SDL2TK/Network/Port.hpp"
#include <winsock2.h>

namespace SDL2TK
{
    Uint16 Port::HostValue() const
    {
        return htons(_port);
    }

    const Port Port::FromHostValue(Uint16 hostValue)
    {
        return Port(htons(hostValue));
    }
}
