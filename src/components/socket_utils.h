#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include "tcp_socket.h"
#include "udp_socket.h"

#include <sys/socket.h>

enum SocketAddressFamily
{
    INET = AF_INET,
    INET6 = AF_INET6
}

class SocketUtils
{
public:
    static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily)
    {
        int s = socket(inFamily, SOCK_DGRAM, 0);
        if (s >= 0)
        {
            return TCPSocketPtr(new TCPSocket(s));
        }
        else
        {
            return nullptr;
        }
    }
    
    static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily)
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
}

#endif