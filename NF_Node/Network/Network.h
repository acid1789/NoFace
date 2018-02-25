#pragma once
#include <vector>
 

class PeerListener;
class PeerConnection;
class KnownPeerManager;
class Thread;
class Mutex;
class Network
{
private:
    Network(int port, unsigned int maxConnections);
    ~Network();

public:
    void Update();

    void FindPeers();

private:
	void UpdatePendingConnections();
    
private:
    int _port;
    unsigned int _maxConnections;
    PeerListener* _listener;
    std::vector<PeerConnection*> _peers;
	Mutex* _peerLock;
    KnownPeerManager* _kpm;
    Thread* _peerFinder;

private:
    static Network* s_Instance;

public:
    static Network* Init(int port, int maxConnections);
    static void Shutdown();
    static Network* Instance();
    
private:
    static int Platform_Init();
};

