#ifndef MODELVIEW_HPP
#define MODELVIEW_HPP

#include "Resource/Eigen/Dense"

namespace Engine {
    Eigen::Matrix4f GetModelIviewMatrix(void);
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec);
    void SetModelViewMatrix(void);
    static Eigen::Matrix4f ModelViewMatrix;
}

#endif