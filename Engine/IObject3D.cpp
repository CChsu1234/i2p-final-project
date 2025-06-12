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
        Selected = false;
        Touched = false;
        Eigen::Matrix4f MVP = ProjectionMatrix * ModelViewMatrix;

        for (auto tris : Tris) {
            // TODO Complete Viewport Transform
            Triangle3D transformed = tris.TriangleTransform();

            if (transformed.Origin_in_Triangle()) {
                Selected = true;
                Touched = true;
            }

            Eigen::Vector3f test(0.0f, 0.0f, 1.0f);
            bool should_Draw = true;
            if (transformed.Normal.dot(test) < 0) {
                should_Draw = false;
            } else {
                for (int i = 0; i < 3; i++) {
                    if (transformed.P[i](2) < Zfar || transformed.P[i](2) > Znear) {
                        should_Draw = false;
                    }
                }
            }
            if (should_Draw) {
                Tris_Transformed.insert(transformed);
            }
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
