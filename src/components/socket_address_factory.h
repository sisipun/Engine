#ifndef SOCKET_ADDRESS_FACTORY_H
#define SOCKET_ADDRESS_FACTORY_H

#include "socket_address.h"

class SockerAddressFactory
{
public:
    static SocketAddressPtr CreateFromString(const std::string &inString, int inFamily = AF_INET)
    {
        auto pos = inString.find_last_of(':');
        std::string host, service;
        if (pos != std::string::npos)
        {
            host = inString.substr(0, pos);
            service = inString.substr(pos + 1);
        }
        else
        {
            host = inString;
            service = "0";
        }
        addrinfo hint;
        memset(&hint, 0, sizeof(hint));
        hint.ai_family = inFamily;

        addrinfo *result;
        int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
        if (error != 0 && result != nullptr)
        {
            freeaddrinfo(result);
            return nullptr;
        }

        while (!result->ai_addr && result->ai_next)
        {
            result = result->ai_next;
        }

        if (!result->ai_addr)
        {
            freeaddrinfo(result);
            return nullptr;
        }

        auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
        freeaddrinfo(result);
        return toRet;
    }
};

#endif