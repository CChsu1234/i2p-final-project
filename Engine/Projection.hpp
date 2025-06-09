/*
#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "Resource/Eigen/Dense"

namespace Engine {
    // return Projection Matrix base on input parameter
    Eigen::Matrix4f GetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf);
    // Project eye coordinate to NDC (normalize device coordinate)
    Eigen::Vector4f Projection(Eigen::Vector4f Vec);
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf);
    // Set Projection Matrix
    static Eigen::Matrix4f ProjectionMatrix;
}

#endif
*/