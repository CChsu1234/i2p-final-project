#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "Resource/Eigen/Dense"

namespace Engine {
    Eigen::Matrix4f GetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf);
    Eigen::Vector4f Projection(Eigen::Vector4f Vec);
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf);
    static Eigen::Matrix4f ProjectionMatrix;
}

#endif