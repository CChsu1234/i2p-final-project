#include "Resource/Eigen/Dense"
#include <iostream>
#include <cmath>
#include <fstream> 
#include <string>

#include "TargetBall.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"

#define M_PI 3.14159265358979323846

namespace Engine {
    TargetBall::TargetBall(Eigen::Vector3f center, int radius, ALLEGRO_COLOR color) {
        std::ifstream inputFile("Resource/ball.obj");
        std::list<Engine::Triangle3D> Tris;
        read3DFile(inputFile, center, radius ,color);
        inputFile.close();
    }

    void TargetBall::OnMouseDown(int Button, int mx, int my) {
        if (Selected) {
            std::cout << "Clicked" << std::endl;
        }
    }

    void TargetBall::read3DFile(std::ifstream& inputFile, Eigen::Vector3f center, int radius, ALLEGRO_COLOR color) {
        std::vector<Eigen::Vector4f> vertices;
        std::string line;

        // Step 1: Read all vertices from the file
        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;

            if (type == "v") {
                float x, y, z;
                ss >> x >> y >> z;
                vertices.emplace_back(x, y, z, 1.0f);
            }
        }

        // Step 2: Normalize (scale to radius) and translate to center
        // Compute bounding box center and size
        Eigen::Vector3f minV = vertices[0].head<3>(), maxV = vertices[0].head<3>();
        for (const auto& v : vertices) {
            minV = minV.cwiseMin(v.head<3>());
            maxV = maxV.cwiseMax(v.head<3>());
        }
        Eigen::Vector3f modelCenter = (minV + maxV) / 2.0f;
        float modelRadius = (maxV - minV).norm() / 2.0f;
        float scale = radius / modelRadius;

        for (auto& v : vertices) {
            v.head<3>() = (v.head<3>() - modelCenter) * scale + center;
        }

        // Step 3: Go back to beginning and read faces
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);

        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;

            if (type == "f") {
                int idx[3];
                for (int i = 0; i < 3; ++i) {
                    std::string token;
                    ss >> token;

                    // Parse index (handles v/vt/vn cases)
                    size_t slashPos = token.find('/');
                    if (slashPos != std::string::npos)
                        token = token.substr(0, slashPos);

                    idx[i] = std::stoi(token) - 1; // OBJ index is 1-based
                }

                // Add triangle
                Tris.emplace_back(vertices[idx[0]], vertices[idx[1]], vertices[idx[2]], color);
            }
        }
    }
}
