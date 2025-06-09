#include <cmath>
#include "ModelView.hpp"


namespace Engine {
    Eigen::Matrix4f ModelViewMatrix;
    Eigen::Matrix4f ProjectionMatrix;
    float yaw = 0.0f;
    float pitch = 0.0f;

    Eigen::Matrix4f GetModelIViewMatrix(void) {
        // TODO Complete the matrix
        // rotation 
        float cosYaw = std::cos(yaw);
        float sinYaw = std::sin(yaw);
        float cosPitch = std::cos(pitch);
        float sinPitch = std::sin(pitch);

        Eigen::Matrix4f yawMatrix;
        yawMatrix << cosYaw, 0, -sinYaw, 0,
                     0,      1, 0,       0,
                     sinYaw, 0, cosYaw,  0,
                     0,      0, 0,       1;

        Eigen::Matrix4f pitchMatrix;
        pitchMatrix << 1, 0,        0,         0,
                       0, cosPitch, sinPitch,  0,
                       0, -sinPitch, cosPitch, 0,
                       0, 0,        0,         1;

        return pitchMatrix * yawMatrix;
    }
    Eigen::Matrix4f GetProjectionMatrix(float fovY, float aspect, float nearZ, float farZ) {
        float f = 1.0f / std::tan(fovY / 2.0f);
        float rangeInv = 1.0f / (nearZ - farZ);

        Eigen::Matrix4f proj;
        proj << f / aspect, 0, 0,                              0,
                0,          f, 0,                              0,
                0,          0, (nearZ + farZ) * rangeInv,      2 * nearZ * farZ * rangeInv,
                0,          0, -1,                             0;

        return proj;
    }
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec) {
        return Vec.transpose() * ModelViewMatrix;
    }
    void SetModelViewMatrix(void) {
        ModelViewMatrix = GetModelIViewMatrix();
    }
    Eigen::Vector4f Projection(Eigen::Vector4f Vec) {
        return Vec.transpose() * ProjectionMatrix;
    }
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf) {
        ProjectionMatrix = GetProjectionMatrix(theta, aspectRatio, Zn, Zf);
    }
}