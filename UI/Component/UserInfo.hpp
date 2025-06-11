#ifndef USERINFO_HPP
#define USERINFO_HPP

#include "UI/Component/Label.hpp"
#include "Engine/GameEngine.hpp"

namespace Engine {
    class UserInfo : public Label {
    public:
        UserInfo();
        void Update(float deltaTime) override;
    };
}
#endif