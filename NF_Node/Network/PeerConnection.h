#pragma once

class Socket;
class PeerConnection
{
public:
    PeerConnection(Socket* connection);
    ~PeerConnection();

    bool Update();

private:
    Socket* _socket;
};

