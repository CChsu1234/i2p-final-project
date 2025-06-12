#ifndef FINALSTAGESELECTSCENE_HPP
#define FINALSTAGESELECTSCENE_HPP
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

class FinalSelectScene final : public Engine::IScene {
private:
    //std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::MouseKeyboard *Controller;
    int cubeLifeTime[15] = {};
    Engine::RotatingCube *cube[15];
    float timeAccumulator = 0.0f;
    bool change[15] = {0};
    void Update(float deltaTime) override;
public:
    explicit FinalSelectScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Play1OnClick(int stage);
    void Play2OnClick(int stage);
    void ScoreboardOnClick();
    void BackOnClick(int stage);
    void OnKeyDown(int keyCode) override;
};

#endif   // STAGESELECTSCENE_HPP
