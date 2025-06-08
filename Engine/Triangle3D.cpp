#include "Resource/Eigen/Dense"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Triangle3D.hpp"
#include "Engine/Projection.hpp"

namespace Engine {
    Triangle3D::Triangle3D(Eigen::Vector4f A, Eigen::Vector4f B, Eigen::Vector4f C, unsigned char r, unsigned char g, unsigned char b) : Color(al_map_rgb(r, g, b)) {
        P[0] = A;
        P[1] = B;
        P[2] = C;
    }
    Triangle3D::Triangle3D(Eigen::Vector4f A, Eigen::Vector4f B, Eigen::Vector4f C, ALLEGRO_COLOR color) : Color(color) {
        P[0] = A;
        P[1] = B;
        P[2] = C;
    }
    void Triangle3D::Draw() const {
        al_draw_triangle(P[0](0), P[0](1), P[1](0), P[1](1), P[2](0), P[2](1), Color, 1.0);
    }
    Triangle3D Triangle3D::Project() {
        Eigen::Vector4f Temp[3];
        for (int i = 0; i < 3; i++) {
            Temp[i] = Projection(P[i], ProjecitonMatrix);
        }
        return Triangle3D(Temp[0], Temp[1], Temp[2], Color);
    }
    bool Triangle3D::operator<(Triangle3D other) const {
        return (
            (P[0](2) + P[1](2) + P[2](2)) < other.P[0](2) + other.P[1](2) + other.P[2](2)
        );
    }
}