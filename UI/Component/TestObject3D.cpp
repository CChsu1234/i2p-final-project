#include "Resource/Eigen/Dense"
#include <iostream>

#include "TestObject3D.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"

namespace Engine {
    TestObject3D::TestObject3D() {
        Eigen::Vector4f A(10, 10, 0, 0);
        Eigen::Vector4f B(20, 20, 0, 0);
        Eigen::Vector4f C(10, 30, 0, 0);
        Triangle3D New(A, B, C, 255, 255, 255);
        Tris.push_back(New);
    }
    void TestObject3D::Transform() {
        IObject3D::Transform();
    }
}