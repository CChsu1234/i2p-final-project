#ifndef MODELVIEW_HPP
#define MODELVIEW_HPP

#include "Resource/Eigen/Dense"

namespace Engine {
    // return Model View Matrix
    Eigen::Matrix4f GetModelIviewMatrix(void);
    // Model-viewing the world coordinate to eye coordinate
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec);
    // Set Model View Matrix
    void SetModelViewMatrix(void);
    static Eigen::Matrix4f ModelViewMatrix;
}

#endif