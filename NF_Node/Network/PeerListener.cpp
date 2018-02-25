#include "PeerListener.h"
#include "Socket.h"
#include "../System/Thread.h"
#include "../System/Mutex.h"

#include <stdio.h>

void PeerListenerThread(void* param)
{
    ((PeerListener*)param)->Listen();
}

PeerListener::PeerListener(int port)
{
    _socket = new Socket();
    _port = port;
    _connectionsLock = new Mutex();
    
    _listenThread = new Thread(PeerListenerThread, this);
}


PeerListener::~PeerListener()
{
}

void PeerListener::Listen()
{
    int err = _socket->Bind(_port);    
    if (err != 0)
    {
        printf("Failed to bind to port: %d\n", _port);
        return;
    }

    while (true)
    {
        int err = _socket->Listen(10);
        if (err != 0)
        {
            printf("Listen failure: %d\n", err);
            return;
        }

        Socket* newSocket = _socket->Accept();
        if (newSocket)
        {
            _connectionsLock->Lock();
            _acceptedConnections.push_back(newSocket);
            _connectionsLock->Unlock();
        }
    }
}

void PeerListener::GetPendingConnections(std::vector<Socket*>& connections)
{
    if (_connectionsLock->Lock(0))
    {
        for (auto c : _acceptedConnections)
            connections.push_back(c);
        _acceptedConnections.clear();

        _connectionsLock->Unlock();
    }
}
