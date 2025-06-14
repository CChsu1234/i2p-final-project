#include "FinalStartScene.hpp"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

#define currentUserid Engine::GameEngine::GetInstance().GetCurrentUser()

// DONE HACKATHON-2 (1/3): You can imitate the 2 files: 'StartScene.hpp', 'StartScene.cpp' to implement your SettingsScene.
void FinalStartScene::Initialize() { 
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    Controller = new Engine::MouseKeyboard(false);
    AddNewControlObject(Controller);


    AddNewObject(new Engine::Label("Cube Sniper", "pirulen.ttf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 200, 400, 100);
    btn->SetOnClickCallback(std::bind(&FinalStartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Play", "pirulen.ttf", 48, halfW, halfH / 2 + 250, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 450, halfH * 3 / 2  + 10, 400, 100);
    btn->SetOnClickCallback(std::bind(&FinalStartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 38, halfW - 250 ,halfH * 3 / 2  + 10 +50, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 50,halfH * 3 / 2  + 10 , 400, 100);
    btn->SetOnClickCallback(std::bind(&FinalStartScene::ScoreBoardOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("1v1 battle", "pirulen.ttf", 38, halfW + 250, halfH * 3 / 2  + 10 +50, 0, 0, 0, 255, 0.5, 0.5));



    for (int i = 0; i<15;i++){
        unsigned char r = rand() % 256;
        unsigned char g = rand() % 256;
        unsigned char b = rand() % 256;
        ALLEGRO_COLOR decideColor = al_map_rgb(r, g, b);
        double posX = -100.0f + 200.0f *((double)rand() / RAND_MAX);
        double posY = -50.0f + 100.0f *((double)rand() / RAND_MAX);
        cubeLifeTime[i] = rand() % 5;
        AddNewControlObject3D(cube[i] = new Engine::RotatingCube(Eigen::Vector3f(posX, posY, -30), 3.0f, decideColor));
    }
}
void FinalStartScene::Terminate() {
    IScene::Terminate();
}

void FinalStartScene::PlayOnClick(int stage) {
    if (currentUserid != -1) {
        Engine::GameEngine::GetInstance().ChangeScene("finalSelect");
    } else {
        Engine::GameEngine::GetInstance().ChangeScene("login");
    }
}

void FinalStartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}

void FinalStartScene::ScoreBoardOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("wait");
}
void FinalStartScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_A){
        Engine::GameEngine::GetInstance().ChangeScene("finalSelect");
    }
    else if (keyCode == ALLEGRO_KEY_S) {
        Engine::GameEngine::GetInstance().ChangeScene("settings");
    }
    else if (keyCode == ALLEGRO_KEY_D){
        Engine::GameEngine::GetInstance().ChangeScene("wait");
    }
}
void FinalStartScene::Update(float deltaTime){
    IScene::Update(deltaTime);
    
    timeAccumulator += deltaTime;
    if (timeAccumulator >= 5.0f) {
        timeAccumulator -= 5.0f;
        for (int i = 0; i<15;i++) change[i] = false;
    }
        

    for (int i = 0; i < 15;i++){
        if (timeAccumulator>= cubeLifeTime[i] && change[i] == false){
            double posX = -100.0f + 200.0f *((double)rand() / RAND_MAX);
            double posY = -50.0f + 100.0f *((double)rand() / RAND_MAX);
            cube[i]->updateDraw(al_map_rgb(255, 255, 255), Eigen::Vector3f(posX, posY, -30));
            change[i] = true;
        }
    }
        
}
