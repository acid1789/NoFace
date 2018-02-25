#pragma once
class Socket
{
    Socket(int existingHandle);
public:
    Socket();
    ~Socket();

    int Bind(int port);
    int Listen(int backlog);
    Socket* Accept();

	bool Connect(const char* address, int port);
    
    void Close();


protected:
    int _socketHandle;
};

