#include "PeerConnection.h"
#include "Socket.h"


PeerConnection::PeerConnection(Socket* connection)
{
    _socket = connection;
}

PeerConnection::~PeerConnection()
{
    if (_socket)
    {
        delete _socket;
        _socket = nullptr;
    }
}

bool PeerConnection::Update()
{
    return true;
}
