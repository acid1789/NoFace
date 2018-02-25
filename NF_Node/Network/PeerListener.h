#pragma once
#include <vector>

class Thread;
class Mutex;
class Socket;
class PeerListener
{
public:
    PeerListener(int port);
    ~PeerListener();


    void Listen();

    bool HasPendingConnections() { return _acceptedConnections.size() > 0; }
    void GetPendingConnections(std::vector<Socket*>& connections);

private:
    Socket* _socket;
    int _port;
    Thread* _listenThread;

    std::vector<Socket*> _acceptedConnections;
    Mutex* _connectionsLock;
};

