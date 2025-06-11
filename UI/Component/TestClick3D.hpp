#ifndef TESTCLICK3D_HPP
#define TESTCLICK3D_HPP

#include "Engine/IObject3D.hpp"
#include "Engine/IControl.hpp"
#include "Engine/Triangle3D.hpp"

namespace Engine {
    class TestClick3D : public IObject3D, public IControl {
    public:
        Eigen::Vector3f Position;
        ALLEGRO_COLOR Color;
        TestClick3D(const Eigen::Vector3f&, float halfSize, ALLEGRO_COLOR);
        ~TestClick3D() = default;
        void updateDraw(const Eigen::Vector3f&);
        void OnMouseDown(int Button, int mx, int my) override;
    };
}

#endif
