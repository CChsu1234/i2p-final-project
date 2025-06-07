#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

#include <set>
#include <allegro5/color.h>
#include "Engine/IObject.hpp"
#include "Resource/Eigen/Dense"

namespace Engine {
    struct Triangle3D {
        Eigen::Vector3f a, b, c;
        ALLEGRO_COLOR Coler;
        Triangle3D(Eigen::Vector3f A, Eigen::Vector3f B, Eigen::Vector3f C);
        void Update(float deltaTime);
        void Draw(void) const ;
        bool operator() (Triangle3D a, Triangle3D b) const;
    };

    class Object3D : public IObject {
    private:
        std::set<Triangle3D> Triangles;
    public:
        Object3D(void);
        void Draw(void) const override;
    };
}

#endif