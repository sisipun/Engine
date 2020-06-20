#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "socket_address.h"

#include <sys/socket.h>
#include <memory>

class UDPSocket
{
public:
    ~UDPSocket();
    UDPSocket(int inSocket) : mSocket(inSocket) {}
    int Bind(const SocketAddress &inBindAddress);
    int SentTo(const void *inData, int inLen, const SocketAddress &inTo);
    int ReceiveFrom(void *inBuffer, int inLen, SocketAddress &outFrom);
    int SetNonBlockingMode(bool inShouldBeNonBlocking);

private:
    int mSocket;
};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

#endif