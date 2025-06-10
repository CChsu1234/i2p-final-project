#include "Resource/Eigen/Dense"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

#include "Engine/ModelView.hpp"
#include "Engine/Triangle3D.hpp"
#include "Engine/ModelView.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/LightShadow.hpp"

namespace Engine {
    Triangle3D::Triangle3D(Eigen::Vector4f A, Eigen::Vector4f B, Eigen::Vector4f C, unsigned char r, unsigned char g, unsigned char b) : Color(al_map_rgb(r, g, b)) {
        P[0] = A;
        P[1] = B;
        P[2] = C;
        
        Eigen::Vector3f e1(P[2](0) - P[0](0), P[2](1) - P[0](1), P[2](2) - P[0](2));
        Eigen::Vector3f e2(P[1](0) - P[0](0), P[1](1) - P[0](1), P[1](2) - P[0](2));

        Normal = e1.cross(e2);
    }
    Triangle3D::Triangle3D(Eigen::Vector4f A, Eigen::Vector4f B, Eigen::Vector4f C, ALLEGRO_COLOR color) : Color(color) {
        P[0] = A;
        P[1] = B;
        P[2] = C;
        
        Eigen::Vector3f e1(P[2](0) - P[0](0), P[2](1) - P[0](1), P[2](2) - P[0](2));
        Eigen::Vector3f e2(P[1](0) - P[0](0), P[1](1) - P[0](1), P[1](2) - P[0](2));

        Normal = e1.cross(e2).normalized();
    }
    /*
    void Triangle3D::Draw() const {
        al_draw_filled_triangle(P[0](0), P[0](1), P[1](0), P[1](1), P[2](0), P[2](1), Color);
        al_draw_triangle(P[0](0), P[0](1), P[1](0), P[1](1), P[2](0), P[2](1), al_map_rgb(0, 0, 0) , 1.0f);
    }
    */
    void Triangle3D::Draw() const {
        LightShadow* Light = GameEngine::GetInstance().light;
        float r, g, b;
        al_unmap_rgb_f(Color, &r, &g, &b);
        Eigen::Vector3f baseColor(r, g, b);

        Eigen::Vector3f normal = Normal.normalized();
        Eigen::Vector3f center = ((P[0] + P[1] + P[2]) / 3.0f).head<3>();

        Eigen::Vector3f shadedColor = Light->computeLighting(center, normal, baseColor);
        shadedColor = shadedColor.cwiseMin(1.0f).cwiseMax(0.0f); // Clamp

        ALLEGRO_COLOR drawColor = al_map_rgb_f(shadedColor.x(), shadedColor.y(), shadedColor.z());

        al_draw_filled_triangle(
            P[0].x(), P[0].y(),
            P[1].x(), P[1].y(),
            P[2].x(), P[2].y(),
            drawColor
        );

        al_draw_triangle(
            P[0].x(), P[0].y(),
            P[1].x(), P[1].y(),
            P[2].x(), P[2].y(),
            al_map_rgb(0, 0, 0), 1.0f
        );

        // Shadow
        Eigen::Vector4f sP[3];
        for (int i = 0; i < 3; ++i) {
            Eigen::Vector3f shadow = Light->projectShadow(P[i].head<3>());
            sP[i] = Eigen::Vector4f(shadow.x(), shadow.y(), shadow.z(), 1.0f);
        }

        ALLEGRO_COLOR shadowColor = al_map_rgba_f(0.1f, 0.1f, 0.1f, 0.5f);
        al_draw_filled_triangle(
            sP[0].x(), sP[0].y(),
            sP[1].x(), sP[1].y(),
            sP[2].x(), sP[2].y(),
            shadowColor
        );
    }



    Triangle3D Triangle3D::TriangleTransform() const {
        Eigen::Vector4f A = Engine::Transform(P[0]);
        Eigen::Vector4f B = Engine::Transform(P[1]);
        Eigen::Vector4f C = Engine::Transform(P[2]);

        return Triangle3D(A, B, C, Color);
    }
    bool Triangle3D::operator<(Triangle3D other) const {
        return (
            (P[0](2) + P[1](2) + P[2](2)) > other.P[0](2) + other.P[1](2) + other.P[2](2)
        );
    }
}