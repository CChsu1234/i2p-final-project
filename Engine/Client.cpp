#include <iostream>

#include "Client.hpp"

namespace Engine {
    int Client::Init(char *addr) {
        ENetHost * client;

        Host = enet_host_create (NULL, 1, 1, 0, 0);

        if (Host == NULL) {
            fprintf (stderr, 
                    "An error occurred while trying to create an ENet client host.\n");
            exit (EXIT_FAILURE);
        }

            return 0;
    }
    int Client::Connect(char *addr) {
        ENetAddress address;
        ENetEvent event;
        
        /* Connect to some.server.net:1234. */
        enet_address_set_host (&address, addr);
        address.port = 1234;
        
        /* Initiate the connection, allocating the two channels 0 and 1. */
        Peer = enet_host_connect (Host, &address, 1, 0);    
        
        if (Peer == NULL) {
            fprintf (stderr, 
                        "No available peers for initiating an ENet connection.\n");
            exit (EXIT_FAILURE);
        }
        
        /* Wait up to 5 seconds for the connection attempt to succeed. */
        if (enet_host_service (Host, & event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
            std::cout <<  ("Connection to some.server.net:1234 succeeded.") << std::endl;
            return 0;
        } else {
            /* Either the 5 seconds are up or a disconnect event was */
            /* received. Reset the peer in the event the 5 seconds   */
            /* had run out without any significant event.            */
            enet_peer_reset (Peer);
        
            puts ("Connection to some.server.net:1234 failed.");

            return 1;
        }
        return 1;
    }
}