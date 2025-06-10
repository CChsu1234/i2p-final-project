#include <cmath>
#include "ModelView.hpp"
#define M_PI 3.14159265358979323846


namespace Engine {
    Eigen::Matrix4f ModelViewMatrix;
    Eigen::Matrix4f ProjectionMatrix;
    // float yaw = 0.0f;
    // float pitch = 0.0f;

    Eigen::Matrix4f GetModelIViewMatrix(float yaw, float pitch, Eigen::Vector4f Pos) {
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

        Eigen::Matrix4f Translate;
        Translate << 1.0f, 0.0f, 0.0f, -Pos(0),
                     0.0f, 1.0f, 0.0f, -Pos(1),
                     0.0f, 0.0f, 1.0f, -Pos(2),
                     0.0f, 0.0f, 0.0f, 1.0f;

        return (pitchMatrix * yawMatrix) * Translate;
    }
    Eigen::Matrix4f GetProjectionMatrix(float fovX, float aspectRatio, float front, float back) {
        Znear = front;
        Zfar = back;

        const float DEG2RAD = acos(-1.0f) / 180;

        float tangent = tan(fovX/2 * DEG2RAD);    // tangent of half fovX
        float right = front * tangent;            // half width of near plane
        float top = right / aspectRatio;  

        Eigen::Matrix4f proj;
        proj << front / right, 0.0f, 0.0f, 0.0f,
                0.0f, front / top, 0.0f, 0.0f,
                0.0f, 0.0f, -(back + front) / (back - front), -(2 * back * front) / (back - front),
                0.0f, 0.0f, -1.0f, 0.0f;
            
        return proj;
    }
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec) {
        return ModelViewMatrix * Vec;
    }
    void SetModelViewMatrix(float yaw, float pitch, Eigen::Vector4f Pos) {
        ModelViewMatrix = GetModelIViewMatrix(yaw, pitch, Pos);
    }
    Eigen::Vector4f Projection(Eigen::Vector4f Vec) {
        return Vec.transpose() * ProjectionMatrix;
    }
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf) {
        ProjectionMatrix = GetProjectionMatrix(theta, aspectRatio, Zn, Zf);
    }
}