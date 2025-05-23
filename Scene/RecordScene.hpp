#ifndef RECORDSCENE_HPP
#define RECORDSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

class RecordScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;

public:
    explicit RecordScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
};
#endif
