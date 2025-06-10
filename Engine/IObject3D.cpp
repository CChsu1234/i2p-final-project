#include <list>
#include <set>
#include <iostream>

#include "IObject3D.hpp"
#include "Resource/Eigen/Dense"
#include "Engine/Triangle3D.hpp"
#include "Engine/ModelView.hpp"

namespace Engine {
    std::list<std::pair<bool, IObject3D *>>::iterator IObject3D::GetObject3DIterator() const {
        return object3DIterator;
    }
    void IObject3D::Transform() {
        // SetModelViewMatrix();
        Eigen::Matrix4f MVP = ProjectionMatrix * ModelViewMatrix;

        for (auto tris : Tris) {
            Triangle3D transformed = tris.TriangleTransform();

            Eigen::Vector3f test(0.0f, 0.0f, 1.0f);
            if (transformed.Normal.dot(test) > 0) {
                Tris_Transformed.insert(transformed);
            }
            // TODO Complete Viewport Transform
        }
    }
    void IObject3D::Draw() const {

        for (auto it = Tris_Transformed.begin(); it != Tris_Transformed.end(); ++it) {
            it->Draw();
        }
    }
    void IObject3D::CleanUp() {
        Tris_Transformed.clear();
    }
    void IObject3D::Update(float deltaTime) {}
}
