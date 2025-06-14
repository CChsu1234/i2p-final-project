#include <iostream>

#include "Server.hpp"

namespace Engine {
    int Server::Init(char *addr) {
        ENetAddress address;
        
        address.host = ENET_HOST_ANY;
        enet_address_set_host (& address, addr);
        /* Bind the server to port 1234. */
        address.port = 1234;
        
        Host = enet_host_create(&address, 32, 1, 0, 0);
        if (Host == NULL) {
            std::cout << "An error occurred while trying to create an ENet server host." << std::endl;
            exit (EXIT_FAILURE);
        } else {
            std::cout << "create host success!" << std::endl;
        }

        ENetSocket socket;

        socket = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
        enet_socket_get_address(socket, &address);

        char ip[100];

        enet_address_get_host_ip(&address, ip, 100);

        std::cout << "IP: " << ip << std::endl;

        return 0;
    }
    int Server::Wait() {
        ENetEvent event;
        while (enet_host_service(Host, &event, 60000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf ("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer->address.port);
                
                Peer = event.peer;
        
                /* Store any relevant client information here. */
                event.peer->data = (char *)"Client information";
                return 0;
            default:
                return 1;
            }
        }
        return 1;
    }
}