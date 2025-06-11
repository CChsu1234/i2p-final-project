#ifndef ROTATINGCUBE_HPP
#define ROTATINGCUBE_HPP
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"
#include "Engine/IControl.hpp"
#include <Eigen/Dense>
#include <vector>

namespace Engine {
    class RotatingCube: public IObject3D, public IControl {
    public:
        RotatingCube(const Eigen::Vector3f& center, float halfSize, ALLEGRO_COLOR color);
        void Update(float deltaTime) override;
        void updateDraw(ALLEGRO_COLOR,const Eigen::Vector3f& center); 
        float timeAccumulator1 = 0.0f;
        
    private:
        float angleY;
        Eigen::Vector3f Center;
        float HalfSize;
        ALLEGRO_COLOR Color;
    };
}

#endif