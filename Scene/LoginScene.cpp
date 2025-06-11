#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <cstdio>
#include <iostream>

#include "LoginScene.hpp"
#include "File/User.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/FinalScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextEditor.hpp"
#include "UI/Component/UserInfo.hpp"

#define table Engine::GameEngine::GetInstance().GetUserTable()
User *currentUser = Engine::GameEngine::GetInstance().GetCurrentUser();

Engine::TextEditor *username;
Engine::TextEditor *userpwd;
Engine::Label *LoginLog;
Engine::Label *signup_login;
Engine::Label *title;

void LoginScene::Initialize() {
    table.Update();
    LoginLogCountDown = 0.0f;
    Mode = LOGIN;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;
    AddNewControlObject(username = new Engine::TextEditor("win/dirt.png", "win/floor.png", "pirulen.ttf", 32, halfW - 400, halfH - 200, 800, 100, 0, 0, 0, 255, 0, 0.5));
     AddNewControlObject(userpwd = new Engine::TextEditor("win/dirt.png", "win/floor.png", "pirulen.ttf", 32, halfW - 400, halfH, 800, 100, 0, 0, 0, 255, 0, 0.5, false));
    AddNewObject(LoginLog = new Engine::Label("", "pirulen.ttf", 32, halfW, halfH + 150, 255, 255, 255, 225, 0.5, 0.5));


    AddNewObject(title = new Engine::Label("Login", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 - 300, halfH * 5 / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW - 300, halfH * 5 / 3, 0, 0, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 + 300, halfH * 5 / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::ToggleSignupLogin, this, 1));
    AddNewControlObject(btn);
    AddNewObject(signup_login =  new Engine::Label("SIGNUP", "pirulen.ttf", 48, halfW + 300, halfH * 5 / 3, 0, 0, 0, 255, 0.5, 0.5));
    AddNewControlObject(new Engine::UserInfo());

    bgmInstance = AudioHelper::PlaySample("scoreboard.ogg", true, AudioHelper::BGMVolume);
}
void LoginScene::Terminate() {
    table.Save();
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void LoginScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("finalscoreboard");
}
void LoginScene::ToggleSignupLogin(int stage) {
    Mode = (Mode + 1) % 2;
    if (Mode == LOGIN) {
        signup_login->Text = "SIGNUP";
        title->Text = "Login";
    } else if (Mode == SIGNUP) {
        signup_login->Text = "LOGIN";
        title->Text = "Sign up";
    }
    username->ClearText();
    userpwd->ClearText();
}
void LoginScene::OnKeyDown(int keycode) {
    IScene::OnKeyDown(keycode);
    if (Mode == LOGIN) {
        if (keycode == ALLEGRO_KEY_ENTER) {
            User *loginUser = Login();
            if (loginUser) {
                username->ClearText();
                userpwd->ClearText();
                LoginLog->Text = "Login as " + loginUser->Name;
                Engine::GameEngine::GetInstance().SetCurrentUser(loginUser);
            } else {
                LoginLog->Text = "Login fail";
            }
            LoginLogCountDown = 3.0f;
        }
    } else if(Mode == SIGNUP) {
        if (keycode == ALLEGRO_KEY_ENTER) {
            User *signupuser = Signup();
            if (!signupuser) {
                LoginLog->Text = "User already exist!";
            } else {
                LoginLog->Text = "Sign up success: " + signupuser->Name + ", Pleaes Login Again";
                LoginLogCountDown = 3.0f;
                ToggleSignupLogin(1);
            }
            LoginLogCountDown = 3.0f;
        }
    }
}
void LoginScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    if (LoginLogCountDown > 0.0f) {
        LoginLogCountDown -= deltaTime;
    } else {
        LoginLog->Text = "";
    }
}
User *LoginScene::Login() {
    std::string name = username->getTextLine();
    std::string pwd = userpwd->getTextLine();

    User loginuser(name, pwd);

    for (int i = 0; i < table.size(); i++) {
        if (loginuser == table[i]) {
            return &table[i];
        }
    }
    return nullptr;
}
User *LoginScene::Signup() {
    
    std::string name = username->getTextLine();
    std::string pwd = userpwd->getTextLine();

    User signupuser(name, pwd);

    for (int i = 0; i < table.size(); i++) {
        if (signupuser == table[i]) {
            return nullptr;
        }
    }
    Engine::GameEngine::GetInstance().AddNewUser(signupuser);

    for (int i = 0; i < table.size(); i++) {
        if (signupuser == table[i]) {
            return &table[i];
        }
    }
}