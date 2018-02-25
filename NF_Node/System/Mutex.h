#pragma once
class Mutex
{
public:
    Mutex();
    ~Mutex();

    bool Lock(unsigned int timeoutMS = 0xFFFFFFFF);
    void Unlock();

private:
    void* _theMutex;
};

