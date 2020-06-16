#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include "stdint.h"
#include "udp_socket.h"
#include <sys/socket.h>
#include <memory>

struct in_addr
{
    union {
        struct
        {
            uint8_t s_b1, s_b2, s_b3, s_b4;
        } S_un_b;
        struct
        {
            uint16_t s_w1, s_w2;
        } S_un_w;
        uint32_t S_addr;
    } S_un;
};

struct sockaddr_in
{
    short sin_family;
    uint16_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort);
    SocketAddress(const sockaddr &inSockAddr);
    size_t GetSize() const;

private:
    friend class UDPSocket;
    sockaddr mSockAddr;
    sockaddr_in *GetAsSockAddrIn();
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

#endif