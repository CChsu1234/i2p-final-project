#ifndef TESTOBJECT3D_HPP
#define TESTOBJECT3D_HPP

#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"

namespace Engine {
    class TestObject3D : public IObject3D {
    public:
        TestObject3D();
        ~TestObject3D() = default;
        void Transform() override;
    };
}

#endif
