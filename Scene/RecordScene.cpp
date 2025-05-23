#include <functional>
#include <iostream>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextEditor.hpp"
#include "RecordScene.hpp"
#include "File/User.hpp"
Engine::TextEditor *editor;

void RecordScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Label("type in your name!", "pirulen.ttf", 32, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&RecordScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Save", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    AddNewControlObject(editor = new Engine::TextEditor("win/dirt.png", "win/floor.png", "pirulen.ttf", 32, halfW - 400, halfH, 800, 100, 0, 0, 0, 255, 0, 0.5));
    /*
        explicit TextEditor(std::string img, std::string imaIn, const std::string &font, int fontsize, float x, float y, float w = 0, float h = 0, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 9, const std::string &text = "", int flag = 0);
    */
    bgmId = AudioHelper::PlayAudio("win.wav");
}
void RecordScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void RecordScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void RecordScene::BackOnClick(int stage) {
    UserTable table;
    table.GiveName(editor->getTextLine());
    table.Sort();
    table.Save();
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
