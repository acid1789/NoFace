#include "Socket.h"

#ifdef WINDOWS
#include <WinSock2.h>
#else
#define closesocket close
#endif

Socket::Socket(int existingHandle)
{
    _socketHandle = existingHandle;
}

Socket::Socket()
{
    _socketHandle = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::~Socket()
{
    Close();
}

int Socket::Bind(int port)
{
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    int err = bind(_socketHandle, (const sockaddr*)&address, sizeof(address));
    return err;
}

int Socket::Listen(int backlog)
{
    return listen(_socketHandle, 10);
}

Socket* Socket::Accept()
{
    sockaddr_in address;
    int sockAddrSize = sizeof(sockaddr_in);
    int newSocket = accept(_socketHandle, (sockaddr*)&address, &sockAddrSize);
    if (newSocket > 0)
    {
        return new Socket(newSocket);
    }
    return nullptr;
}

void Socket::Close()
{
    if (_socketHandle > 0)
        closesocket(_socketHandle);
}

bool Socket::Connect(const char* address, int port)
{
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr = 
	connect(_socketHandle, saddr, sizeof(saddr));
}