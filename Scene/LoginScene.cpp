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
#include "Scene/FinalScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextEditor.hpp"
#include "UI/Component/UserInfo.hpp"

#define table Engine::GameEngine::GetInstance().GetUserTable()
int currentUser = Engine::GameEngine::GetInstance().GetCurrentUser();

Engine::TextEditor *username;
Engine::TextEditor *userpwd;
Engine::Label *LoginLog;
Engine::Label *switchmode;
Engine::Label *action;
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
    
    AddNewControlObject(username = new Engine::TextEditor("win/blue.jpg", "win/hoveredblue.jpg", "pirulen.ttf", 32, halfW - 400, halfH - 200, 800, 100, 0, 0, 0, 255, 0, 0.5));
    AddNewControlObject(userpwd = new Engine::TextEditor("win/blue.jpg", "win/hoveredblue.jpg", "pirulen.ttf", 32, halfW - 400, halfH, 800, 100, 0, 0, 0, 255, 0, 0.5, false));
    AddNewObject(LoginLog = new Engine::Label("", "pirulen.ttf", 32, halfW, halfH + 150, 255, 255, 255, 225, 0.5, 0.5));


    AddNewObject(title = new Engine::Label("Login", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", w - 150 - 100, 35 - 25, 200, 50);
    btn->SetOnClickCallback(std::bind(&LoginScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 24, w - 150, 35, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", w - 400 - 100, 35 - 25, 200, 50);
    btn->SetOnClickCallback(std::bind(&LoginScene::ToggleSignupLogin, this, 1));
    AddNewControlObject(btn);
    AddNewObject(switchmode =  new Engine::Label("SIGNUP", "pirulen.ttf", 24, w - 400, 35, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 250 - 200, halfH * 5 / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::LoginSignupOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(action = new Engine::Label("LOGIN", "pirulen.ttf", 48, halfW - 250, halfH * 5 / 3, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 250 - 200, halfH * 5 / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::LogoutOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("LOGIN OUT", "pirulen.ttf", 48, halfW + 250, halfH * 5 / 3, 0, 0, 0, 255, 0.5, 0.5));

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
    Engine::GameEngine::GetInstance().ChangeScene("finalStart");
}
void LoginScene::ToggleSignupLogin(int stage) {
    Mode = (Mode + 1) % 2;
    if (Mode == LOGIN) {
        switchmode->Text = "SIGN UP";
        action->Text = "LOGIN";
        title->Text = "Login";
    } else if (Mode == SIGNUP) {
        switchmode->Text = "LOGIN";
        action->Text = "SIGN UP";
        title->Text = "Sign up";
    }
    username->ClearText();
    userpwd->ClearText();
}
void LoginScene::OnKeyDown(int keycode) {
    IScene::OnKeyDown(keycode);
    if (Mode == LOGIN) {
        if (keycode == ALLEGRO_KEY_ENTER) {
            int loginUserid = Login();
            if (loginUserid != -1) {
                username->ClearText();
                userpwd->ClearText();
                LoginLog->Text = "Login as " + table.at(loginUserid).Name;
                Engine::GameEngine::GetInstance().SetCurrentUser(loginUserid);
            } else {
                LoginLog->Text = "Login fail";
            }
            LoginLogCountDown = 3.0f;
        }
    } else if(Mode == SIGNUP) {
        if (keycode == ALLEGRO_KEY_ENTER) {
           int signupuserid = Signup();
            if (signupuserid == -1) {
                LoginLog->Text = "User already exist!";
            } else {
                LoginLog->Text = "Sign up success: " + table.at(signupuserid).Name + ", Pleaes Login Again";
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
int LoginScene::Login() {
    std::string name = username->getTextLine();
    std::string pwd = userpwd->getTextLine();

    User loginuser(name, pwd);

    for (int i = 0; i < table.size(); i++) {
        if (loginuser == table[i]) {
            Engine::GameEngine::GetInstance().SetCurrentUser(table[i].id);
            Engine::GameEngine::GetInstance().ChangeScene("finalStart");
            return table[i].id;
        }
    }
    return -1;
}
int LoginScene::Signup() {
    
    std::string name = username->getTextLine();
    std::string pwd = userpwd->getTextLine();

    User signupuser(name, pwd);

    for (int i = 0; i < table.size(); i++) {
        if (signupuser.sameName(table[i])) {
            return -1;
        }
    }
    signupuser.id = table.size();
    Engine::GameEngine::GetInstance().AddNewUser(signupuser);

    for (int i = 0; i < table.size(); i++) {
        if (signupuser == table[i]) {
            return table[i].id;
        }
    }

    return -1;
}
void LoginScene::LogoutOnClick(int stage) {
    Engine::GameEngine::GetInstance().SetCurrentUser(-1);
}
void LoginScene::LoginSignupOnClick(int stage) {
    if (Mode == LOGIN) {
        int loginUserid = Login();
        if (loginUserid != -1) {
            username->ClearText();
            userpwd->ClearText();
            LoginLog->Text = "Login as " + table.at(loginUserid).Name;
            Engine::GameEngine::GetInstance().SetCurrentUser(loginUserid);
        } else {
            LoginLog->Text = "Login fail";
        }
        LoginLogCountDown = 3.0f;
    } else if(Mode == SIGNUP) {
        int signupuserid = Signup();
        if (signupuserid == -1) {
            LoginLog->Text = "User already exist!";
        } else {
            LoginLog->Text = "Sign up success: " + table.at(signupuserid).Name + ", Pleaes Login Again";
            LoginLogCountDown = 3.0f;
            ToggleSignupLogin(1);
        }
        LoginLogCountDown = 3.0f;
    }
}