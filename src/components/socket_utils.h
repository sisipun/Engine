#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <sys/socket.h>

enum SocketAddressFamily
{
    INET = AF_INET,
    INET6 = AF_INET6
}

class SocketUtils
{
public:
    static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);
    static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily);
}

#endif