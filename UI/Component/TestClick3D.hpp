#ifndef TESTCLICK3D_HPP
#define TESTCLICK3D_HPP

#include <allegro5/allegro_audio.h>
#include "Engine/IObject3D.hpp"
#include "Engine/IControl.hpp"
#include "Engine/Triangle3D.hpp"

namespace Engine {
    class TestClick3D : public IObject3D, public IControl {
    public:
        TestClick3D(const Eigen::Vector3f& center, float halfSize, ALLEGRO_COLOR allegroColor);
        ~TestClick3D() = default;
        virtual void updateDraw(const Eigen::Vector3f&);
        virtual void OnMouseDown(int Button, int mx, int my) override;
        Eigen::Vector3f Position;
        ALLEGRO_COLOR Color;
        float HalfSize;
    };
}

#endif
