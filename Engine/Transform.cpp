#include <cmath>
#include "Resource/Eigen/Dense"

#include "Engine/Transform.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/ModelView.hpp"
#define M_PI 3.14159265358979323846

namespace Engine {
    Eigen::Matrix4f GetTransformMatrix() {
        // TODO Complete Transform Matrix
        float aspect =  static_cast<float> (GameEngine::GetInstance().GetScreenSize().x) / static_cast<float> (GameEngine::GetInstance().GetScreenSize().y);
        SetProjectionMatrix(90.0f * M_PI / 180.0f, aspect, 1.0f, 500.0f);
        SetModelViewMatrix();
        return ProjectionMatrix * ModelViewMatrix;;
    }
    Eigen::Vector4f Transform(Eigen::Vector4f Vec) {
        Vec = Vec.transpose() * TransformMatrix;
        Vec[0] /= Vec[3];
        Vec[1] /= Vec[3];
        Vec[2] /= Vec[3];
        
        float screenWidth = GameEngine::GetInstance().GetScreenSize().x;
        float screenHeight = GameEngine::GetInstance().GetScreenSize().y;

        Vec[0] = (Vec[0] + 1) * 0.5f * screenWidth;
        Vec[1] = (1 - Vec[1]) * 0.5f * screenHeight;

        return Vec;
        // Vec = ModelView(Vec);
        // Vec = Projection(Vec);
        // x /= w, y /= w, z /= w
        // Viewport Transform // in IObject3D
    }
    void SetTransformMatrix() {
        TransformMatrix = GetTransformMatrix();
    }
}