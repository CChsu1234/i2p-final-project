#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <cstdio>
#include <iostream>

#include "WaitScene.hpp"
#include "File/User.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/FinalScoreBoardScene.hpp"
#include "Scene/MultiPlayer.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextEditor.hpp"
#include "UI/Component/UserInfo.hpp"

#define table Engine::GameEngine::GetInstance().GetUserTable()
#define currentUser Engine::GameEngine::GetInstance().GetCurrentUser()

void WaitScene::Initialize() {
    Mode = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;
    AddNewControlObject(ip = new Engine::TextEditor("win/dirt.png", "win/floor.png", "pirulen.ttf", 32, halfW - 400, halfH - 200, 800, 100, 0, 0, 0, 255, 0, 0.5));

    Host = nullptr;

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 5 / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WaitScene::LockOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(action = new Engine::Label("LOCK", "pirulen.ttf", 48, halfW, halfH * 5 / 3, 0, 0, 0, 255, 0.5, 0.5));


    AddNewObject(title = new Engine::Label("Start", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", w - 400 - 100, 35 - 25, 200, 50);
    btn->SetOnClickCallback(std::bind(&WaitScene::ToggleMode, this, 1));
    AddNewControlObject(btn);
    AddNewObject(switchmode =  new Engine::Label("Join", "pirulen.ttf", 24, w - 400, 35, 0, 0, 0, 255, 0.5, 0.5));

    AddNewControlObject(new Engine::UserInfo());

    bgmInstance = AudioHelper::PlaySample("scoreboard.ogg", true, AudioHelper::BGMVolume);
}
void WaitScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();

    
    IScene::Terminate();
}
void WaitScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("finalStart");
}
void WaitScene::LockOnClick(int stage) {
    if (Mode == 0) {
        Host = new Engine::Server();
        Host->Init((char*)(ip->getTextLine().c_str()));
    } else if (Mode == 1) {
        Host = new Engine::Client();
        Host->Init((char*)(ip->getTextLine().c_str()));
    }
    lock = true;
}
void WaitScene::ToggleMode(int stage) {
    Mode = (Mode + 1) % 2;
    std::string temp = title->Text;
    title->Text = switchmode->Text;
    switchmode->Text = temp;
}
void WaitScene::OnKeyDown(int keycode) {
    IScene::OnKeyDown(keycode);
    
}
void WaitScene::Update(float deltaTime) {
    if (lock && Mode == 0) {
        Host->Wait();
    } else if (lock && Mode == 1) {
        Host->Connect((char*)(ip->getTextLine().c_str()));
        Host->SendRecv((char*)"Go", strlen((char*)"Go") + 1);
        if (Host != nullptr) {
            MultiPlayer *scene = dynamic_cast<MultiPlayer *>(Engine::GameEngine::GetInstance().GetScene("multiplayer"));
            scene->SetHost(Host);
            scene->SetMode(Mode);
        }
        Engine::GameEngine::GetInstance().ChangeScene("multiplayer");
    }
    IScene::Update(deltaTime);
    if (Host != nullptr) {
        int result = Host->SendRecv((char*)"ComeOn", strlen((char*)"ComeOn") + 1);
        if (result == 1) {
            Engine::GameEngine::GetInstance().ChangeScene("finalStart");
        }
        if (!strcmp(Host->read(), (char*)"Go")) {
            if (Host != nullptr) {
                MultiPlayer *scene = dynamic_cast<MultiPlayer *>(Engine::GameEngine::GetInstance().GetScene("multiplayer"));
                scene->SetHost(Host);
                scene->SetMode(Mode);
            }
            Engine::GameEngine::GetInstance().ChangeScene("multiplayer");
        }
    }
}