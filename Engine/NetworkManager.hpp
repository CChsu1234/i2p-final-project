#ifndef __NetworkManager__
#define __NetworkManager__

#include <enet/enet.h>

#define MAX_BUFLEN 256

namespace Engine {
    class NetworkManager {
    protected:
        char Buff[MAX_BUFLEN];
        ENetHost *Host;
        ENetPeer *Peer;
        ENetEvent Event;
    public:
        NetworkManager() = default;
        virtual int Init(char *addr);
        virtual int Wait();
        virtual int Connect(char *addr);
        virtual int SendRecv(char *msg = nullptr, int size = 0);
        virtual char *read();
    };
}

#endif