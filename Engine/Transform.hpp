#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Resource/Eigen/Dense"
#include "Engine/Projection.hpp"
#include "Engine/ModelView.hpp"

namespace Engine {
    // return transform matrix in order to complete Modeling viewing project with one matrix
    Eigen::Matrix4f GetTrasformMatrix();
    // Transform world coordinate to NDC (normalize device coordinate)
    Eigen::Vector4f Transform(Eigen::Vector4f Vec);
    void SetTransformMatrix();
    static Eigen::Matrix4f TransformMatrix;
}

#endif