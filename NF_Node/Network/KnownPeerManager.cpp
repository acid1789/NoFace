#include "KnownPeerManager.h"
#include "../CPPUtils.h"

#include <sstream>

KnownPeerManager::KnownPeerManager()
{
    Load();
}


KnownPeerManager::~KnownPeerManager()
{
    Save();
    Clear();
}

void KnownPeerManager::Clear()
{
    for (auto peer : _knownPeers)
        delete peer;
    _knownPeers.clear();
}

void KnownPeerManager::Load()
{
    Clear();
    vector<string> lines = File_ReadAllLines("kpm.config");

    for (auto line : lines)
    {
        vector<string> pieces = String_Split(line, ",");
        KnownPeer* p = new KnownPeer();
        p->Address = pieces[0];
        p->Score = pieces.size() > 1 ? atoi(pieces[1].c_str) : 0;
        _knownPeers.push_back(p);
    }
}

void KnownPeerManager::Save()
{
    vector<string> lines;
    for (auto kp : _knownPeers)
    {
        std::ostringstream stringStream;
        stringStream << kp->Address << "," << kp->Score;
        lines.push_back(stringStream.str());
    }

    File_WriteAllLines("kpm.config", lines);
}