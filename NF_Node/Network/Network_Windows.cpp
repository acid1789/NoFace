#include "Network.h"

#include <winsock2.h>

int Network::Platform_Init()
{
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    return err;
}