#include "../include/SDL2TK/Network/Port.hpp"

#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif

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
