#include "Resource/Eigen/Dense"
#include <iostream>
#include <cmath>

#include "TestClick3D.hpp"
#include "Scene/TestScene.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"

#define M_PI 3.14159265358979323846

namespace Engine {
    TestClick3D::TestClick3D(const Eigen::Vector3f& center, float halfSize, ALLEGRO_COLOR allegroColor) :Position(center), Color(allegroColor) {
        updateDraw(center);
    }

    void TestClick3D::updateDraw(const Eigen::Vector3f& center) {
            Position = center;
            Tris.clear();  // Step 1: Clear previous triangles

            float halfSize = 2.0f; // Or store `halfSize` as a member variable if needed

            // Step 2: Define cube vertices at origin
            Eigen::Vector4f vertices[8] = {
                {-halfSize, -halfSize, -halfSize, 1.0f},
                { halfSize, -halfSize, -halfSize, 1.0f},
                { halfSize,  halfSize, -halfSize, 1.0f},
                {-halfSize,  halfSize, -halfSize, 1.0f},
                {-halfSize, -halfSize,  halfSize, 1.0f},
                { halfSize, -halfSize,  halfSize, 1.0f},
                { halfSize,  halfSize,  halfSize, 1.0f},
                {-halfSize,  halfSize,  halfSize, 1.0f}
            };

            // Step 3: Reapply rotation
            float angleX = M_PI / 6.0f;
            float angleY = M_PI / 4.0f;

            Eigen::Matrix4f rotX;
            rotX << 1, 0, 0, 0,
                    0, cos(angleX), -sin(angleX), 0,
                    0, sin(angleX),  cos(angleX), 0,
                    0, 0, 0, 1;

            Eigen::Matrix4f rotY;
            rotY << cos(angleY), 0, sin(angleY), 0,
                    0, 1, 0, 0,
                -sin(angleY), 0, cos(angleY), 0,
                    0, 0, 0, 1;

            Eigen::Matrix4f transform = rotY * rotX;

            // Step 4: Translate to new center
            Eigen::Matrix4f translate;
            translate << 1, 0, 0, center.x(),
                        0, 1, 0, center.y(),
                        0, 0, 1, center.z() - 20.0f, // still push back
                        0, 0, 0, 1;

            for (int i = 0; i < 8; ++i) {
                vertices[i] = translate * (transform * vertices[i]);
        }

        // Step 5: Re-add triangles
        auto addTriangle = [&vertices, this](int a, int b, int c, ALLEGRO_COLOR color) {
            Tris.emplace_back(vertices[a], vertices[b], vertices[c], color);
        };

        ALLEGRO_COLOR faceColor = Color; // re-use original color

        addTriangle(0, 1, 2, faceColor); addTriangle(2, 3, 0, faceColor); // Front
        addTriangle(5, 4, 7, faceColor); addTriangle(7, 6, 5, faceColor); // Back
        addTriangle(4, 0, 3, faceColor); addTriangle(3, 7, 4, faceColor); // Left
        addTriangle(1, 5, 6, faceColor); addTriangle(6, 2, 1, faceColor); // Right
        addTriangle(3, 2, 6, faceColor); addTriangle(6, 7, 3, faceColor); // Top
        addTriangle(4, 5, 1, faceColor); addTriangle(1, 0, 4, faceColor); // Bottom

        Selected = false;
    }


    void TestClick3D::OnMouseDown(int Button, int mx, int my) {
        /*
        TestScene *currentScene = dynamic_cast<TestScene *>(GameEngine::GetInstance().GetScene("test"));
        if (Selected) {
            // std::cout << "Clicked" << std::endl;
            currentScene->totalShots++;
            currentScene->hitCount++;
            currentScene->hit = 1;
        }
        else currentScene->hit = 2;
        */
    }
}
