#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "UI/Component/TestClick3D.hpp"


namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}   // namespace Engine

class TestScene final : public Engine::IScene {
private:
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;

public:
    int hitCount = 0;
    int totalShots = 0;
    int score = 0;
    int timeLeft = 60;
    unsigned char r = 0, b = 255, g = 255; 
    
    Engine::MouseKeyboard *Controller;
    Engine::TestClick3D* target[3];

    std::vector<float> hitRateVariation;
    std::vector<int> scoreVariation;

    explicit TestScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;

    void RespawnTarget(int i);
    void OnMouseDown(int button, int x, int y) override;
    void EndGame();
    
};
#endif   // PLAYSCENE_HPP
