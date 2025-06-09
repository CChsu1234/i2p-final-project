/*
#include <cmath>
#include "Projection.hpp"


namespace Engine {
    Eigen::Matrix4f GetProjectionMatrix(float theta, float aspectRatio, float Znear, float Zfar) {
        // TODO Complete the matrix
        const float DEG2RAD = 0.0174532925f; // acos(-1.0f) / 180;
        float tangent = tan(theta/2 * DEG2RAD);    // tangent of half fovY
        float top = Znear * tangent;              // half height of near plane
        float right = top * aspectRatio;          // half width of near plane
        Eigen::Matrix4f projectionMatrix;
        if (Zfar == Znear) {
            Zfar = 1; 
            Znear = 0.9f;
        }
        if (right == 0) right = 1;
        if (top == 0) top = 1;
        projectionMatrix << Znear/right, 0, 0, 0,
                            0, Znear / top, 0, 0,
                            0, 0, -(Zfar + Znear) / (Zfar - Znear), -1,
                            0, 0, -(2 * Znear * Zfar) / (Zfar - Znear), 0;
        return projectionMatrix;
    }
    Eigen::Vector4f Projection(Eigen::Vector4f Vec) {
        return Vec.transpose() * ProjectionMatrix;
    }
    void SetProjectionMatrix(float theta, float aspectRatio, float Zn, float Zf) {
        ProjectionMatrix = GetProjectionMatrix(theta, aspectRatio, Zn, Zf);
    }
}
*/
