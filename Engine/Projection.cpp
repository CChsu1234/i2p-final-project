#include "Projection.hpp"

namespace Engine {
    Eigen::Matrix4f GetProjectionMatrix(float theta, float aspectRatio) {
        Eigen::Matrix4f Temp;
        Temp << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1;
        return Temp;
    }
    Eigen::Vector4f Projection(Eigen::Vector4f Vec, Eigen::Matrix4f projectionMatrix) {
        return Vec.transpose() * ProjecitonMatrix;
    }
    void SetProjectionMatrix(float theta, float aspectRatio) {
        ProjecitonMatrix = GetProjectionMatrix(theta, aspectRatio);
    }
}