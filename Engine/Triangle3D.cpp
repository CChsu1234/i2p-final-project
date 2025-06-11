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

        if (Origin_in_Triangle()) {
            drawColor = al_map_rgb(0, 255, 0);
        }

        al_draw_filled_triangle(
            P[0].x(), P[0].y(),
            P[1].x(), P[1].y(),
            P[2].x(), P[2].y(),
            drawColor
        );

        /*
        al_draw_triangle(
            P[0].x(), P[0].y(),
            P[1].x(), P[1].y(),
            P[2].x(), P[2].y(),
            al_map_rgb(0, 0, 0), 1.0f
        );
        */

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
    Eigen::Vector4f Cross(Eigen::Vector4f u, Eigen::Vector4f v) {
        Eigen::Vector4f retVec;
        retVec <<
            u(0) * v(1) - u(1) * v(0),
            u(1) * v(0) - u(0) * v(1),
            0.0f,
            0.0f;
        return retVec;
    }
    // https://blackpawn.com/texts/pointinpoly/
    bool SameSide(Eigen::Vector4f p1, Eigen::Vector4f p2, Eigen::Vector4f a, Eigen::Vector4f b) {
        Eigen::Vector4f cp1 = Cross(b - a, p1 - a);
        Eigen::Vector4f cp2 = Cross(b - a, p2 - a);
        
        return (cp1.dot(cp2) >= 0);
    }
    // https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
    float Area(float x1, float y1, float x2, float y2, float x3, float y3) {
        return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f);
    }
    bool Triangle3D::Origin_in_Triangle() const {
        float midX = GameEngine::GetInstance().GetScreenSize().x * 0.5;
        float midY = GameEngine::GetInstance().GetScreenSize().y * 0.5;
        /*
        float Atotal = Area(P[0](0), P[0](1), P[1](0), P[1](1), P[2](0), P[2](1));
        float A1 = Area(midX, midY, P[1](0), P[1](1), P[2](0), P[2](1));
        float A2 = Area(P[0](0), P[0](1), midX, midY, P[2](0), P[2](1));
        float A3 = Area(P[0](0), P[0](1), P[1](0), P[1](1), midX, midY);
        return (Atotal == A1 + A2 + A3);
        */
        Eigen::Vector4f Origin(midX, midY, 0.0f, 0.0f);
        return (SameSide(Origin, P[0], P[1], P[2]) && SameSide(Origin,  P[1], P[0], P[2]) && SameSide(Origin, P[2], P[0],  P[1]));
    }
    bool Triangle3D::operator<(Triangle3D other) const {
        return (
            (P[0](2) + P[1](2) + P[2](2)) > other.P[0](2) + other.P[1](2) + other.P[2](2)
        );
    }
}