#include "Thread.h"
#include "Windows.h"

DWORD WINAPI WinThreadProc(void* ThreadClassPtr)
{
    Thread* t = (Thread*)ThreadClassPtr;
    t->_threadFunc(t->_threadParam);
    return 0;
}

Thread::Thread(ThreadFunc threadFunc, void* threadParam)
{
    _threadHandle = CreateThread(NULL, 0, WinThreadProc, this, CREATE_SUSPENDED, (DWORD*)&_threadId);
    ResumeThread(_threadHandle);
}


Thread::~Thread()
{
}
