#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include "RotatingCube.hpp"
#include "TestClick3D.hpp"
#include "Scene/TestScene.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"
#define M_PI 3.14159265358979323846

float timeAccumulator1 = 0.0f;

namespace Engine {
    RotatingCube::RotatingCube(const Eigen::Vector3f& center, float halfSize, ALLEGRO_COLOR color)
        : Center(center), HalfSize(halfSize), Color(color), angleY(0.0f) {
        updateDraw(color, center);
    }

    void RotatingCube::Update(float deltaTime) {
        angleY += deltaTime; 
        timeAccumulator1 += deltaTime;
        if (timeAccumulator1 >= 1.0f) {
            timeAccumulator1 -= 1.0f;
            unsigned char r = rand() % 256;
            unsigned char g = rand() % 256;
            unsigned char b = rand() % 256;

            // Create an ALLEGRO_COLOR object
            ALLEGRO_COLOR decideColor = al_map_rgb(r, g, b);
            Color = decideColor;
        }

        updateDraw(Color, Center);
    }

    void RotatingCube::updateDraw(ALLEGRO_COLOR decideColor, const Eigen::Vector3f& center) {
        Center = center;
        Tris.clear();

        Eigen::Vector4f vertices[8] = {
            {-HalfSize, -HalfSize, -HalfSize, 1.0f},
            { HalfSize, -HalfSize, -HalfSize, 1.0f},
            { HalfSize,  HalfSize, -HalfSize, 1.0f},
            {-HalfSize,  HalfSize, -HalfSize, 1.0f},
            {-HalfSize, -HalfSize,  HalfSize, 1.0f},
            { HalfSize, -HalfSize,  HalfSize, 1.0f},
            { HalfSize,  HalfSize,  HalfSize, 1.0f},
            {-HalfSize,  HalfSize,  HalfSize, 1.0f}
        };

        float angleX = M_PI / 6.0f;

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

        Eigen::Matrix4f translate;
        translate << 1, 0, 0, Center.x(),
                     0, 1, 0, Center.y(),
                     0, 0, 1, Center.z() - 20.0f,
                     0, 0, 0, 1;

        for (int i = 0; i < 8; ++i)
            vertices[i] = translate * (transform * vertices[i]);

        auto addTriangle = [&vertices, this](int a, int b, int c, ALLEGRO_COLOR color) {
            Tris.emplace_back(vertices[a], vertices[b], vertices[c], color);
        };
        
        addTriangle(0, 1, 2, decideColor); addTriangle(2, 3, 0, decideColor);
        addTriangle(5, 4, 7, decideColor); addTriangle(7, 6, 5, decideColor);
        addTriangle(4, 0, 3, decideColor); addTriangle(3, 7, 4, decideColor);
        addTriangle(1, 5, 6, decideColor); addTriangle(6, 2, 1, decideColor);
        addTriangle(3, 2, 6, decideColor); addTriangle(6, 7, 3, decideColor);
        addTriangle(4, 5, 1, decideColor); addTriangle(1, 0, 4, decideColor);
    }
}
