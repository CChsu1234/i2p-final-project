#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/TestScene.hpp"
#include "Scene/SurvivalScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"
#include "UI/Animation/CubeBackGround.hpp"

void SettingsScene::Initialize() {
    AddNewControlObject(new Engine::MouseKeyboard(false));
    AddNewObject3D(new Engine::CubeBackGround());

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Engine::ImageButton *btn;
    AddNewObject(new Engine::Label("Select your Crosshair color.", "pirulen.ttf", 45, halfW, 70, 255, 255, 255, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("stage-select/blue.jpg", "stage-select/blue.jpg", halfW - 250, 350, 100, 100);
    btn->SetOnClickCallback(std::bind(&SettingsScene::BlueOnClick, this, 1));
    AddNewControlObject(btn);
    
    btn = new Engine::ImageButton("stage-select/red.jpg", "stage-select/red.jpg", halfW + 150, 350, 100, 100);
    btn->SetOnClickCallback(std::bind(&SettingsScene::RedOnClick, this, 2));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&SettingsScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
}
void SettingsScene::Terminate() {
   
    IScene::Terminate();
}
void SettingsScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("finalStart");
}

void SettingsScene::RedOnClick(int stage) {
    TestScene* play1 = dynamic_cast<TestScene *> (Engine::GameEngine::GetInstance().GetScene("test"));
    play1->r = 255, play1->g = 90, play1->b = 90;
    SurvivalScene* play2 = dynamic_cast<SurvivalScene *> (Engine::GameEngine::GetInstance().GetScene("survival"));
    play2->r = 255, play2->g = 90, play2->b = 90;
}

void SettingsScene::BlueOnClick(int stage) {
    TestScene* play1 = dynamic_cast<TestScene *> (Engine::GameEngine::GetInstance().GetScene("test"));
    play1->r = 0, play1->g = 255, play1->b = 255;
    SurvivalScene* play2 = dynamic_cast<SurvivalScene *> (Engine::GameEngine::GetInstance().GetScene("survival"));
    play2->r = 0, play2->g = 255, play2->b = 255;
}