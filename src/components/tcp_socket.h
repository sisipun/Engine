#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "socket_address.h"

#include <sys/socket.h>
#include <memory>

class TCPSocket
{
public:
    ~TCPSocket();
    TCPSocket(int inSocket) : mSocket(inSocket) {}
    int Connect(const SocketAddress &inAddress);
    int Bind(const SocketAddress &inBindAddress);
    int Listen(int inBackLog = 32);
    std::shared_ptr<TCPSocket> Accept(SocketAddress &inFromAddress);
    int Send(const void *inData, int inLen);
    int Receive(void *inBuffer, int inLen);

private:
    int mSocket;
};

typedef std::shared_ptr<TCPSocket> TCPSocketPtr;

#endif