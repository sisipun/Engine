#include "udp_socket.h"
#include <unistd.h>
#include <fcntl.h>

UDPSocket::~UDPSocket()
{
    close(mSocket);
}

int UDPSocket::Bind(const SocketAddress &inBindAddress)
{
    return bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
}

int UDPSocket::SentTo(const void *inData, int inLen, const SocketAddress &inTo)
{
    int byteSentCount = sendto(mSocket, static_cast<const char *>(inData), inLen, 0, &inTo.mSockAddr, inTo.GetSize());
    if (byteSentCount >= 0)
    {
        return byteSentCount;
    }
    else
    {
        return -1;
    }
}

int UDPSocket::ReceiveFrom(void *inBuffer, int inLen, SocketAddress &outFrom)
{
    socklen_t fromLength = outFrom.GetSize();
    int readByteCount = recvfrom(mSocket, static_cast<char *>(inBuffer), inLen, 0, &outFrom.mSockAddr, &fromLength);
    if (readByteCount >= 0)
    {
        return readByteCount;
    }
    else
    {
        return -1;
    }
}

int UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
    int flags = fcntl(mSocket, F_GETFL, 0);
    flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    int result = fcntl(mSocket, F_SETFL, flags);
    if (result < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}