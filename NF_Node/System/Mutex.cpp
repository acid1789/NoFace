#include "Mutex.h"

#include <Windows.h>

Mutex::Mutex()
{
    _theMutex = CreateMutex(nullptr, FALSE, nullptr);
}

Mutex::~Mutex()
{
    CloseHandle(_theMutex);
}

bool Mutex::Lock(unsigned int timeoutMS)
{
    DWORD wait = WaitForSingleObject(_theMutex, timeoutMS);
    return wait == WAIT_OBJECT_0;
}

void Mutex::Unlock()
{
    ReleaseMutex(_theMutex);
}
