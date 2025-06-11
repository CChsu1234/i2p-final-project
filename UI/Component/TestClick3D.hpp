#ifndef TESTCLICK3D_HPP
#define TESTCLICK3D_HPP

#include "Engine/IObject3D.hpp"
#include "Engine/IControl.hpp"
#include "Engine/Triangle3D.hpp"

namespace Engine {
    class TestClick3D : public IObject3D, public IControl {
    public:
        TestClick3D();
        ~TestClick3D() = default;
        void OnMouseDown(int Button, int mx, int my) override;
    };
}

#endif
