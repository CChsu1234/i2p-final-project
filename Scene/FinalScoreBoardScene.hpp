#ifndef FinalScoreBoardScene_HPP
#define FinalScoreBoardScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include "File/User.hpp"

#define PAGE_LINE 6


class FinalScoreBoardScene final : public Engine::IScene {
private:
    int current_head_line;
    int total_line;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::Label *scoreboard[PAGE_LINE][3];

public:
    explicit FinalScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void MovePage(int line);
    void UpOnClick(int line);
    void DownOnClick(int line);
};

#endif   // FinalScoreBoardScene_HPP

