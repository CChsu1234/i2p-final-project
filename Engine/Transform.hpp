#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Resource/Eigen/Dense"
#include "Engine/Projection.hpp"
#include "Engine/ModelView.hpp"

namespace Engine {
    Eigen::Matrix4f GetTrasformMatrix();
    Eigen::Vector4f Transform(Eigen::Vector4f Vec);
    void SetTransformMatrix();
    static Eigen::Matrix4f TransformMatrix;
}

#endif