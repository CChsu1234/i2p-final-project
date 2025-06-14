#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "NetworkManager.hpp"

namespace Engine {
    class Client : public NetworkManager {
    public:
        Client() = default;
        int Init(char *addr) override;
        int Connect(char *addr) override;
    };
}
#endif