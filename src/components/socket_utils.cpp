#include "socket_utils.h"
#include "udp_socket.h"

UDPSocketPtr SocketUtils::CreateUDPSocket(SocketAddressFamily inFamily)
{
    int s = socket(inFamily, SOCK_DGRAM, 0);
    if (s >= 0)
    {
        return UDPSocketPtr(new UDPSocket(s));
    }
    else
    {
        return nullptr;
    }
}