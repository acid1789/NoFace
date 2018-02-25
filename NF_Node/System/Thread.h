#pragma once

typedef void(*ThreadFunc)(void* threadParam);

class Thread
{
public:
    Thread(ThreadFunc tf, void* threadParam = nullptr);
    ~Thread();

    void* _threadHandle;
    int _threadId;
    ThreadFunc _threadFunc;
    void* _threadParam;
};

