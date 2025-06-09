#ifndef TRIANGLE3D_HPP
#define TRIANGLE3D_HPP

#include <allegro5/allegro_color.h>
#include "Resource/Eigen/Dense"

#include "Engine/GameEngine.hpp"

namespace Engine {
    class Triangle3D {
    public:
        Eigen::Vector4f P[3]; // p1->p2->p3->p1 is counter clockwise
        ALLEGRO_COLOR Color;
        Triangle3D(Eigen::Vector4f A, Eigen::Vector4f B, Eigen::Vector4f C, unsigned char r, unsigned char g, unsigned char b);
        Triangle3D(Eigen::Vector4f A, Eigen::Vector4f B, Eigen::Vector4f C, ALLEGRO_COLOR color);
        ~Triangle3D() = default;
        void Draw() const;
        Triangle3D TriangleTransform() const;
        bool operator<(Triangle3D other) const;
    };
}
#endif