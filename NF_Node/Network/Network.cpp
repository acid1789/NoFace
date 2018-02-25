#include "Network.h"
#include "PeerListener.h"
#include "PeerConnection.h"
#include "KnownPeerManager.h"
#include "Socket.h"

#include "../System/Thread.h"
#include "../System/Mutex.h"

#include <stdio.h>
#include <algorithm>

Network* Network::s_Instance = nullptr;

Network* Network::Instance()
{
    return s_Instance;
}

Network* Network::Init(int port, int maxConnections)
{
    if (!s_Instance)
    {
        int err = Platform_Init();
        if (err != 0)
        {
            printf("Platform_Init failed with error: %d\n", err);
            return nullptr;
        }
        s_Instance = new Network(port, maxConnections);
    }
    return s_Instance;
}

void Network::Shutdown()
{
    if (s_Instance)
    {
        delete s_Instance;
        s_Instance = nullptr;
    }
}

void PeerFinderThread(void* network)
{
    Network* n = (Network*)network;
    n->FindPeers();
}

Network::Network(int port, unsigned int maxConnections)
{
    _port = port;
    _maxConnections = maxConnections;
	_peerLock = new Mutex();
    _kpm = new KnownPeerManager();
    _listener = new PeerListener(_port);
    _peerFinder = new Thread(PeerFinderThread, this);
}

Network::~Network()
{
	if (_peerFinder)
	{
		delete _peerFinder;
		_peerFinder = nullptr;
	}
	if (_peerLock)
	{
		delete _peerLock;
		_peerLock = nullptr;
	}
    if (_kpm)
    {
        delete _kpm;
        _kpm = nullptr;
    }
    if (_listener)
    {
        delete _listener;
        _listener = nullptr;
    }
}

void Network::Update()
{
    // Check for pending connections
	UpdatePendingConnections();

    // Process all existing connections
    std::vector<PeerConnection*> dead;
    size_t peerCount = _peers.size();
    for (size_t i = 0; i < peerCount; i++ )
    {
        PeerConnection* pc = _peers[i];
        if (!pc->Update())
            dead.push_back(pc);
    }

    // Cleanup dead connections
	if (dead.size() > 0)
	{
		_peerLock->Lock();
		for (auto pc : dead)
		{
			_peers.erase(std::remove(_peers.begin(), _peers.end(), pc), _peers.end());
			delete pc;
		}
		_peerLock->Unlock();
	}
}

void Network::UpdatePendingConnections()
{
	if (_listener->HasPendingConnections())
	{
		std::vector<Socket*> connections;
		_listener->GetPendingConnections(connections);

		if (connections.size() > 0)
		{
			_peerLock->Lock();
			for (auto s : connections)
			{
				PeerConnection* pc = new PeerConnection(s);
				_peers.push_back(pc);
			}
			_peerLock->Unlock();
		}
	}
}

void Network::FindPeers()
{
    while (true)
    {
        // Try to connect to new peers
        if (_peers.size() < _maxConnections)
        {
            KnownPeer* kp = _kpm->GetPotentialConnection();
            if (kp)
            {
                // Try to connect to this peer
                Socket* s = new Socket();
                if (s->Connect(kp->Address.c_str(), _port))
                {
                    PeerConnection* pc = new PeerConnection(s);
					_peerLock->Lock();
					_peers.push_back(pc);
					_peerLock->Unlock();
                }
            }
        }
    }
}