#include <set>
#include <algorithm>
#include "Resource/Eigen/Dense"

#include "Object3D.hpp"
#include "Engine/IObject.hpp"
#include "Engine/Projection.hpp"

namespace Engine {
    const Eigen::Matrix4f ProjectionMatrix = GetProjectionMatrix();
    bool Triangle3D::operator() (Triangle3D A, Triangle3D B) const {
        float avg_a = A.a(2) + A.b(2) + A.c(3);
        float avg_b = B.a(2) + B.b(2) + B.c(3);
        return avg_a < avg_b;
    }

    Object3D::Object3D(void) {
        
    }

    void Object3D::Draw(void) const {
        for (auto it = Triangles.begin(); it != Triangles.end(); ++it) {
            // projecct a b c
        }
    }
}
