#include "Resource/Eigen/Dense"
#include <iostream>
#include <cmath>

#include "TestClick3D.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"

#define M_PI 3.14159265358979323846

namespace Engine {
    TestClick3D::TestClick3D() {
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
            vertices[i][2] -= 20.0f;
        }

        // Step 3: Define distinct colors for lighting test
        ALLEGRO_COLOR frontColor = al_map_rgb(255, 255, 255);// Red
        ALLEGRO_COLOR backColor = al_map_rgb(255, 255, 255); // Green
        ALLEGRO_COLOR leftColor = al_map_rgb(255, 255, 255);     // Blue
        ALLEGRO_COLOR rightColor = al_map_rgb(255, 255, 255);  // Yellow
        ALLEGRO_COLOR topColor = al_map_rgb(255, 255, 255);    // Cyan
        ALLEGRO_COLOR bottomColor = al_map_rgb(255, 255, 255); // Magenta

        // Step 4: Define triangles using the transformed vertices
        auto addTriangle = [&vertices, this](int a, int b, int c, ALLEGRO_COLOR color) {
            Tris.emplace_back(vertices[a], vertices[b], vertices[c], color);
        };

        // Front face
        addTriangle(0, 1, 2, frontColor);
        addTriangle(2, 3, 0, frontColor);

        // Back face
        addTriangle(5, 4, 7, backColor);
        addTriangle(7, 6, 5, backColor);

        // Left face
        addTriangle(4, 0, 3, leftColor);
        addTriangle(3, 7, 4, leftColor);

        // Right face
        addTriangle(1, 5, 6, rightColor);
        addTriangle(6, 2, 1, rightColor);

        // Top face
        addTriangle(3, 2, 6, topColor);
        addTriangle(6, 7, 3, topColor);

        // Bottom face
        addTriangle(4, 5, 1, bottomColor);
        addTriangle(1, 0, 4, bottomColor);
    }

    void TestClick3D::OnMouseDown(int Button, int mx, int my) {
        if (Selected) {
            // std::cout << "Clicked" << std::endl;
        }
    }
}