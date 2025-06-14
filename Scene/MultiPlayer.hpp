#ifndef MULTIPLAYER_HPP
#define MULTIPLAYER_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "Engine/NetworkManager.hpp"
#include "Engine/Client.hpp"
#include "Engine/Server.hpp"
#include "UI/Component/TestClick3D.hpp"


namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}   // namespace Engine

class MultiPlayer final : public Engine::IScene {
private:
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
    Engine::NetworkManager *Host;
    int Mode;
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR light_blue = al_map_rgb(173, 216, 230); // Light Blue: #ADD8E6
    ALLEGRO_COLOR light_pink = al_map_rgb(255, 182, 193); // Light Pink: #FFB6C1
    ALLEGRO_COLOR light_green = al_map_rgb(144, 238, 144); // Light Green: #90EE90
    Engine::Label *ShowTimer;
    Engine::Label *ShowScore;
    Engine::Label *ShowHitRate;
    float accumalateTime = 0.0f;
    float StartCountDown = 6.0f;
    Engine::Label *CountDown;

public:
    int delta = 0;
    int targetCount = 5;
    int opponentTotalBall = 5;
    int hitCount = 0;
    int totalShots = 0;
    int score = 0;
    int timeLeft = 60;
    int myTotalBall = 5;
    
    Engine::MouseKeyboard *Controller;
    Engine::TestClick3D* target[10];

    std::vector<float> hitRateVariation;
    std::vector<int> scoreVariation;

    explicit MultiPlayer() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;

    void RespawnTarget(int i);
    void OnMouseDown(int button, int x, int y) override;
    void EndGame();

    void SetHost(Engine::NetworkManager *host);
    void SetMode(int Mode);
    
};
#endif   // PLAYSCENE_HPP
