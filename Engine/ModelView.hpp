#ifndef MODELVIEW_HPP
#define MODELVIEW_HPP

#include "Resource/Eigen/Dense"

namespace Engine {
    
    Eigen::Matrix4f GetModelIViewMatrix(float yaw, float pitch);
    Eigen::Matrix4f GetProjectionMatrix(float fovY, float aspect, float nearZ, float farZ);
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec);
    Eigen::Vector4f Projection(Eigen::Vector4f Vec);
    void SetModelViewMatrix(float yaw, float pitch);
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf);

    extern Eigen::Matrix4f ModelViewMatrix;
    extern Eigen::Matrix4f ProjectionMatrix;
}

#endif