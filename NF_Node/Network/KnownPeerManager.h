#pragma once
#include <string>
#include <vector>

class KnownPeer
{
public:
    std::string Address;
    int Score;
    bool Connected;
};

class KnownPeerManager
{
public:
    KnownPeerManager();
    ~KnownPeerManager();


    void Clear();
    void Load();
    void Save();

private:
    std::vector<KnownPeer*> _knownPeers;
};

