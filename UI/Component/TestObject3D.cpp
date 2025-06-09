#include "Resource/Eigen/Dense"
#include <iostream>

#include "TestObject3D.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"
#define M_PI 3.14159265358979323846
namespace Engine {
    TestObject3D::TestObject3D() {
        float halfSize = 0.5f;

        // Step 1: Define cube vertices centered at origin
        Eigen::Vector4f vertices[8] = {
            {-halfSize, -halfSize, -halfSize, 1.0f}, // 0
            { halfSize, -halfSize, -halfSize, 1.0f}, // 1
            { halfSize,  halfSize, -halfSize, 1.0f}, // 2
            {-halfSize,  halfSize, -halfSize, 1.0f}, // 3
            {-halfSize, -halfSize,  halfSize, 1.0f}, // 4
            { halfSize, -halfSize,  halfSize, 1.0f}, // 5
            { halfSize,  halfSize,  halfSize, 1.0f}, // 6
            {-halfSize,  halfSize,  halfSize, 1.0f}  // 7
        };

        // Step 2: Rotate all vertices around X and Y for better 3D view
        float angleX = M_PI / 6.0f; // 30 degrees
        float angleY = M_PI / 4.0f; // 45 degrees

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

        for (int i = 0; i < 8; ++i) {
            vertices[i] = transform * vertices[i];
            // Move the cube forward in Z so camera can see it
            vertices[i][2] -= 3.0f;
        }

        // Step 3: Define 12 triangles (2 per face × 6 faces)
        auto addTriangle = [&vertices, this](int a, int b, int c, ALLEGRO_COLOR color) {
            Tris.emplace_back(vertices[a], vertices[b], vertices[c], color);
        };

        ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

        // Front face
        addTriangle(0, 1, 2, color);
        addTriangle(2, 3, 0, color);

        // Back face
        addTriangle(5, 4, 7, color);
        addTriangle(7, 6, 5, color);

        // Left face
        addTriangle(4, 0, 3, color);
        addTriangle(3, 7, 4, color);

        // Right face
        addTriangle(1, 5, 6, color);
        addTriangle(6, 2, 1, color);

        // Top face
        addTriangle(3, 2, 6, color);
        addTriangle(6, 7, 3, color);

        // Bottom face
        addTriangle(4, 5, 1, color);
        addTriangle(1, 0, 4, color);
    }

    void TestObject3D::Transform() {
        IObject3D::Transform();
    }
}
