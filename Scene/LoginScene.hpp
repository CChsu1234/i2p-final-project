#ifndef LOGINSCENE_HPP
#define LOGINSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include "File/User.hpp"

class FinalScoreBoardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

public:
    explicit FinalScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void MovePage(int line);
    void UpOnClick(int line);
    void DownOnClick(int line);
};

#endif