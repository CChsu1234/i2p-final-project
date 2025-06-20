#ifndef LOGINSCENE_HPP
#define LOGINSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "File/User.hpp"
#include "UI/Component/TextEditor.hpp"
#include "UI/Component/Label.hpp"
#include "File/User.hpp"

class LoginScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    float LoginLogCountDown;
    enum MODE { LOGIN, SIGNUP };
    int Mode;

public:
    explicit LoginScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void ToggleSignupLogin(int stage);
    void LoginSignupOnClick(int stage);
    void LogoutOnClick(int stage);
    void OnKeyDown(int keycode) override;
    void Update(float deltaTime) override;
    int Login();
    int Signup();
};

#endif