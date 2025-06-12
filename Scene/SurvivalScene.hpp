#ifndef SURVIVALSCENE_HPP
#define SURVIVALSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "UI/Component/TestClick3D.hpp"
#include "UI/Component/CrossHair.hpp"

namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}   // namespace Engine

class SurvivalScene final : public Engine::IScene {

public:
    int lives=5;
    int suvivalTime = 0;
    float spawnNum = 1;
    float spawnInterval = 5.0f;
    Engine::MouseKeyboard *Controller;

    std::vector<Engine::TestClick3D*> targets;
    
    explicit SurvivalScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Hit();
    
    void SpawnTarget();
    void OnMouseDown(int button, int x, int y) override;
    void EndGame();
    void ConstructUI();
};
#endif