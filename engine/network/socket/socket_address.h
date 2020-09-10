#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include <sys/socket.h>
#include <netdb.h>
#include <memory>
#include <string>

class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort);
    SocketAddress(const sockaddr &inSockAddr);
    size_t GetSize() const;
    friend class UDPSocket;
    friend class TCPSocket;

private:
    sockaddr mSockAddr;
    sockaddr_in *GetAsSockAddrIn();
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

#endif