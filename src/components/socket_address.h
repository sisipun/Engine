#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include "udp_socket.h"
#include "tcp_socket.h"

#include <sys/socket.h>
#include <netdb.h>
#include <memory>
#include <string>

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

class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort);
    SocketAddress(const sockaddr &inSockAddr);
    size_t GetSize() const;

private:
    friend class UDPSocket;
    friend class TCPSocket;
    sockaddr mSockAddr;
    sockaddr_in *GetAsSockAddrIn();
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

#endif