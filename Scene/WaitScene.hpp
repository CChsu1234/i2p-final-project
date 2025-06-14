#ifndef WAITSCENE_HPP
#define WAITSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "Engine/NetworkManager.hpp"
#include "Engine/Server.hpp"
#include "Engine/Client.hpp"
#include "File/User.hpp"
#include "UI/Component/TextEditor.hpp"
#include "UI/Component/Label.hpp"
#include "File/User.hpp"

class WaitScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    int Mode;
    Engine::NetworkManager *Host;

    Engine::TextEditor *ip;
    Engine::Label *switchmode;
    Engine::Label *action;
    Engine::Label *title;

    bool lock = false;

public:
    explicit WaitScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void LockOnClick(int stage);
    void ToggleMode(int stage);
    void OnKeyDown(int keycode) override;
    void Update(float deltaTime) override;
};

#endif