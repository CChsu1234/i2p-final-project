#ifndef MOUSEKEYBOARD_HPP
#define MOUSEKEYBOARD_HPP

#include "Resource/Eigen/Dense"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

namespace Engine {
    class MouseKeyboard : public IControl, public IObject {
    private:
        float v;
        Eigen::Vector4f Eye, Target;
        enum { UP, LEFT, DOWN, RIGHT };
        bool isKeyDown[4];
    public:
        MouseKeyboard();
        ~MouseKeyboard() = default;
        void OnMouseMove(int mx, int my) override;
        void OnKeyDown(int keyCode) override;
        void OnKeyUp(int keyCode) override;
        void Update(float deltaTime) override;
    };
}

#endif