#ifndef ENDTWOSCENE_HPP
#define ENDTWOSCENE_HPP
#include "Engine/IScene.hpp"
#include "UI/Component/RotatingCube.hpp"
#include "Engine/MouseKeyboard.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>

class EndTwoScene final : public Engine::IScene {
private:
    ALLEGRO_BITMAP* background = nullptr;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::MouseKeyboard *Controller;
public:
    int survivalTime;
    Engine::RotatingCube* cube;
    explicit EndTwoScene() = default;
    void Initialize() override;
    void Terminate() override;
    void OnKeyDown(int keyCode) override;
    void BackOnClick(int stage);
};

#endif   // LOSESCENE_HPP
