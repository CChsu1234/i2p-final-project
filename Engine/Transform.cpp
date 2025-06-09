#include "Resource/Eigen/Dense"

#include "Engine/Transform.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Projection.hpp"
#include "Engine/ModelView.hpp"

namespace Engine {
    Eigen::Matrix4f GetTrasformMatrix() {
        // TODO
        SetProjectionMatrix(90, GameEngine::GetInstance().GetScreenSize().x / GameEngine::GetInstance().GetScreenSize().y , 1.0f, 500.0f);
        SetModelViewMatrix();
        Eigen::Matrix4f transformMatrix;
        transformMatrix << 1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1;
        return transformMatrix;
    }
    Eigen::Vector4f Transform(Eigen::Vector4f Vec) {
        Vec = Vec.transpose() * TransformMatrix;
        // Vec = ModelView(Vec);
        // Vec = Projection(Vec);
        // x /= w, y /= w, z /= w
        // Viewport Transform // in IObject3D
        return Vec;
    }
    void SetTransformMatrix() {
        TransformMatrix = GetTrasformMatrix();
    }
}