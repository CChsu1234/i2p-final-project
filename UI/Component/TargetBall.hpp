#ifndef TARGETBALL_HPP
#define TARGETBALL_HPP
#include <iostream>
#include <fstream> 
#include <string>
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"


namespace Engine {
    class TargetBall : public IObject3D, public IControl {
    public:
        TargetBall(Eigen::Vector3f, int radius, ALLEGRO_COLOR color);
        ~TargetBall() = default;
        void OnMouseDown(int Button, int mx, int my) override;
        void read3DFile(std::ifstream& inputFile, Eigen::Vector3f center, int radius, ALLEGRO_COLOR color) ;
    };
}

#endif
