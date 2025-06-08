#include <list>
#include <set>
#include <iostream>

#include "IObject3D.hpp"

namespace Engine {
    std::list<std::pair<bool, IObject3D *>>::iterator IObject3D::GetObject3DIterator() const {
        return object3DIterator;
    }
    void IObject3D::Project() {
        for (auto tris : Tris) {
            Tris_Projected.insert(tris);
        }
    }
    void IObject3D::Draw() const {
        std::cout << "Draw" << std::endl;
        for (auto it = Tris_Projected.begin(); it != Tris_Projected.end(); ++it) {
            it->Draw();
        }
    }
    void IObject3D::CleanUp() {
        Tris_Projected.clear();
    }
    void IObject3D::Update(float deltaTime) {}
}
