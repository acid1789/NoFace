// NF_Node.cpp : Defines the entry point for the console application.
//
#include "Network/Network.h"


int main()
{
    Network* theNetwork = Network::Init(9946, 500);



    while (true)
    {
        theNetwork->Update();

        
    }

    return 0;
}

