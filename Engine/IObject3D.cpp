#include <list>
#include <set>

#include "IObject3D.hpp"
#include "Engine/Triangle3D.hpp"

namespace Engine {
    std::list<std::pair<bool, IObject3D *>>::iterator IObject3D::GetObject3DIterator() const {
        return object3DIterator;
    }
    void IObject3D::Transform() {
        for (auto tris : Tris) {
            Triangle3D Transformed = tris.Transform();
            // TODO Complete Viewport Transform
            if (true) {
                Tris_Transformed.insert(Transformed);
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
