#ifndef IOBJECT3D_HPP
#define IOBJECT3D_HPP
#include <list>
#include <set>
#include <utility>
#include <fstream> 
#include <iostream>
#include <string>

#include "Engine/Triangle3D.hpp"

namespace Engine {
    class IObject3D {
        friend class Group;

    protected:
        std::list<std::pair<bool, IObject3D *>>::iterator object3DIterator{};
        explicit IObject3D() = default;
        //bool Selected;
        bool Touched;

    public:
        bool Selected;
        std::list<Triangle3D> Tris;
        inline static std::set<Triangle3D> Tris_Transformed{};
        bool Visible = true;
        virtual ~IObject3D() = default;
        IObject3D(const IObject3D &other) = default;
        IObject3D &operator=(IObject3D const &) = default;
        std::list<std::pair<bool, IObject3D *>>::iterator GetObject3DIterator() const;
        virtual void Transform();
        virtual void Draw() const;
        virtual void CleanUp();
        virtual void Update(float deltaTime);
        //virtual void read3DFile(std::ifstream& inputFile, Eigen::Vector3f center, int radius, ALLEGRO_COLOR color) {};
    };
}
#endif   // IOBJECT_HPP
