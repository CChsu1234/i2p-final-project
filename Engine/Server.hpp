#ifndef SERVER_HPP
#define SERVER_HPP
#include "NetworkManager.hpp"

namespace Engine {
    class Server : public NetworkManager {
    public:
        Server() = default;
        int Init(char *addr) override;
        int Wait() override;
    };
}
#endif