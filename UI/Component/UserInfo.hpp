#ifndef USERINFO_HPP
#define USERINFO_HPP

#include "UI/Component/Label.hpp"
#include "Engine/IControl.hpp"
#include "Engine/GameEngine.hpp"

namespace Engine {
    class UserInfo : public Label, public IControl {
    public:
        UserInfo();
        void Update(float deltaTime) override;
        void OnMouseDown(int button, int mx, int my) override;
    };
}
#endif