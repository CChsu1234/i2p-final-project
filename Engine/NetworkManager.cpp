#include <enet/enet.h>
#include <iostream>
#include "NetworkManager.hpp"

namespace Engine {
    int NetworkManager::Init(char *addr) { return 0; }
    int NetworkManager::Wait() { return 0; }
    int NetworkManager::Connect(char *addr) { return 0; }
    int NetworkManager::SendRecv(char *msg, int size) {
        ENetPacket * packet;
        if (msg == nullptr) {
            packet = enet_packet_create ("Nothing", strlen("Nothing") + 1, ENET_PACKET_FLAG_RELIABLE);
        } else {
            packet = enet_packet_create (msg, size, ENET_PACKET_FLAG_RELIABLE);
        }
        enet_peer_send(Peer, 0, packet);
        enet_host_flush(Host);
        enet_host_service(Host, &Event, 0);
        switch (Event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            return -1;
        case ENET_EVENT_TYPE_RECEIVE:
            for (int i = 0; i < Event.packet->dataLength && i < MAX_BUFLEN; i++) {
                Buff[i] = Event.packet->data[i];
            }
            return 0;
        case ENET_EVENT_TYPE_DISCONNECT:
            return 1;
        case ENET_EVENT_TYPE_NONE:
        default:
            return -1;
        }
        return 0;
    }
    char *NetworkManager::read() {
        return Buff;
    }
}