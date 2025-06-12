#ifndef CUBEBACKGROUND_HPP
#define CUBEBACKGROUND_HPP

#include "Engine/IObject3D.hpp"
#include "UI/Component/RotatingCube.hpp"

namespace Engine {
    class CubeBackGround : public IObject3D {
    private:
        int cubeLifeTime[15] = {};
        Engine::RotatingCube *cube[15];
        float timeAccumulator = 0.0f;
        bool change[15] = {0};
    public:
        CubeBackGround();
        ~CubeBackGround() = default;
        void Transform() override;
        void Draw() const override;
        void Update(float deltaTime) override;
    };
}

#endif