#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "Resource/Eigen/Dense"

namespace Engine {
    Eigen::Matrix4f GetProjectionMatrix(float theta, float aspectRatio);
    Eigen::Vector4f Projection(Eigen::Vector4f Vec, Eigen::Matrix4f ProjectionMatrix);
    void SetProjectionMatrix(float theta, float aspectRatio);
    static Eigen::Matrix4f ProjecitonMatrix;
}

#endif