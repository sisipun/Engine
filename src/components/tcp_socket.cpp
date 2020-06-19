#include "tcp_socket.h"
#include <unistd.h>

TCPSocket::~TCPSocket()
{
    close(mSocket);
}

int TCPSocket::Bind(const SocketAddress &inBindAddress)
{
    return bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
}

int TCPSocket::Connect(const SocketAddress &inBindAddress)
{
    return connect(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
}

int TCPSocket::Listen(int inBackLog)
{
    return listen(mSocket, inBackLog);
}

TCPSocketPtr TCPSocket::Accept(SocketAddress &inFromAddress)
{
    socklen_t length = inFromAddress.GetSize();
    int newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);
    if (newSocket > 0)
    {
        return TCPSocketPtr(new TCPSocket(newSocket));
    }
    else
    {
        return nullptr;
    }
}

int TCPSocket::Send(const void *inData, int inLen)
{
    int bytesSentCount = send(mSocket, static_cast<const char *>(inData), inLen, 0);
    if (bytesSentCount < 0)
    {
        return -1;
    }
    else
    {
        return bytesSentCount;
    }
}

int TCPSocket::Receive(void *inData, int inLen)
{
    int bytesReceivedCount = recv(mSocket, static_cast<char *>(inData), inLen, 0);
    if (bytesReceivedCount < 0)
    {
        return -1;
    }
    else
    {
        return bytesReceivedCount;
    }
}