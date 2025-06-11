#ifndef FINALSTARTSCENE_H
#define FINALSTARTSCENE_H
#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include <memory>
#include <allegro5/allegro_audio.h>
#include "UI/Component/RotatingCube.hpp"
#include "Scene/TestScene.hpp"
#include "Engine/IObject3D.hpp"
#include "Engine/Triangle3D.hpp"
#include "Engine/IScene.hpp"


class FinalStartScene final : public Engine::IScene {
public:
    explicit FinalStartScene() = default;
    Engine::MouseKeyboard *Controller;
    int cubeLifeTime[15] = {};
    Engine::RotatingCube *cube[15];
    float timeAccumulator = 0.0f;
    bool change[15] = {0};
    void OnKeyDown(int keyCode) override;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void SettingsOnClick(int stage);
    void ScoreBoardOnClick(int stage);
    void Update(float deltaTime) override;
};
#endif  
