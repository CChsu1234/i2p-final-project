#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "Resource/Eigen/Dense"
// Write function that use OpenGl Projection Matrix to Project eye coordinate to NDC (normalize device coordinate)
namespace Engine {
    Eigen::Matrix4f GetProjectionMatrix(void);
    Eigen::Vector4f Project(Eigen::Vector4f v, Eigen::Matrix4f Projection_Matrix);
}

#endif