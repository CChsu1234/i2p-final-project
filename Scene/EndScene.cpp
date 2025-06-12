#include <functional>
#include <string>
#include <allegro5/allegro_audio.h>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "EndScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/RotatingCube.hpp"

Engine::RotatingCube* cube;

void EndScene::Initialize() {

    Controller = new Engine::MouseKeyboard(false);
    AddNewControlObject(Controller);
    
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    std::string scoreText = "Your Score: " + std::to_string(score);
    std::string rateText = "Your Hit Rate: " + std::to_string(rate) + "%";
    AddNewObject(new Engine::Label("Cube Sniper", "pirulen.ttf",50, halfW, halfH / 4 + 20, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(scoreText , "pirulen.ttf", 30, halfW, halfH / 4 + 80, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(rateText , "pirulen.ttf", 30, halfW, halfH / 4 + 120, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&EndScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Start Again", "pirulen.ttf", 40, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject3D(cube = new Engine::RotatingCube(Eigen::Vector3f(0, 0, -40), 5.0f, al_map_rgb(255, 255, 255)));
    //bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);
}
void EndScene::Terminate() {
    //AudioHelper::StopSample(bgmInstance);
    //bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void EndScene::BackOnClick(int stage) {
    // Change to select scene.
    auto& engine = Engine::GameEngine::GetInstance();
    Engine::GameEngine::GetInstance().ChangeScene("finalStart");
}

void EndScene::OnKeyDown(int keyCode){
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_A){
        Engine::GameEngine::GetInstance().ChangeScene("finalStart");
    }
}