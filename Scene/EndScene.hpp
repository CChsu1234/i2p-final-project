#ifndef ENDSCENE_HPP
#define ENDSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>

class EndScene final : public Engine::IScene {
private:
    ALLEGRO_BITMAP* background = nullptr;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::MouseKeyboard *Controller;
public:
    int score;
    float rate;
    std::vector<float> hitRateVariation;
    std::vector<int> scoreVariation;
    explicit EndScene() = default;
    void Initialize() override;
    void Terminate() override;
    void OnKeyDown(int keyCode) override;
    void BackOnClick(int stage);
    void ScoreBoardOnClick(int stage);
};

#endif   // LOSESCENE_HPP
