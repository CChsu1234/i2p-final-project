#include <cmath>
#include "ModelView.hpp"
#define M_PI 3.14159265358979323846


namespace Engine {
    Eigen::Matrix4f ModelViewMatrix;
    Eigen::Matrix4f ProjectionMatrix;
    // float yaw = 0.0f;
    // float pitch = 0.0f;

    Eigen::Matrix4f GetModelIViewMatrix(float yaw, float pitch) {
        // TODO Complete the matrix
        // rotation 
        yaw = yaw * M_PI / 180.0f;
        pitch = pitch * M_PI / 180.0f;
        float cosYaw = std::cos(yaw);
        float sinYaw = std::sin(yaw);
        float cosPitch = std::cos(pitch);
        float sinPitch = std::sin(pitch);

        Eigen::Matrix4f yawMatrix;
        yawMatrix << cosYaw, 0.0f, -sinYaw, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     sinYaw, 0.0f, cosYaw, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f;

        Eigen::Matrix4f pitchMatrix;
        pitchMatrix << 1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, cosPitch, sinPitch,  0.0f,
                       0.0f, -sinPitch, cosPitch, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f;

        return yawMatrix * pitchMatrix;
    }
    Eigen::Matrix4f GetProjectionMatrix(float fovY, float aspect, float nearZ, float farZ) {
        float f = 1.0f / tan(fovY / 2.0f);
        float rangeInv = 1.0f / (nearZ - farZ);
        float right = nearZ * f;
        float top = right / aspect;

        Eigen::Matrix4f proj;
        /*
        proj << f / aspect, 0.0f, 0.0f, 0.0f,
                0.0f, f, 0.0f, 0.0f,
                0.0f, 0.0f, (nearZ + farZ) * rangeInv, 2 * nearZ * farZ * rangeInv,
                0.0f, 0.0f, -1.0f, 0.0f;
        */
        proj << nearZ / right, 0.0f, 0.0f, 0.0f,
                0.0f, nearZ / f, 0.0f, 0.0f,
                0.0f, 0.0f, -(farZ + nearZ) / (farZ - nearZ), -(2 * farZ  * nearZ) / (farZ - nearZ),
                0.0f, 0.0f, -1.0f, 0.0f;

        return proj;
    }
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec) {
        return Vec.transpose() * ModelViewMatrix;
    }
    void SetModelViewMatrix(float yaw, float pitch) {
        ModelViewMatrix = GetModelIViewMatrix(yaw, pitch);
    }
    Eigen::Vector4f Projection(Eigen::Vector4f Vec) {
        return Vec.transpose() * ProjectionMatrix;
    }
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf) {
        ProjectionMatrix = GetProjectionMatrix(theta, aspectRatio, Zn, Zf);
    }
}