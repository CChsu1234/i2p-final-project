#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <cstdio>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/FinalScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/UserInfo.hpp"

#define table Engine::GameEngine::GetInstance().GetUserTable()

void FinalScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    table.Update();
    total_line = table.size();

    AddNewObject(new Engine::Label("Score Board", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    AddNewObject(new Engine::Label("Name", "pirulen.ttf", 16, halfW * 1 / 4 - 100, halfH + 50 * (-1 - PAGE_LINE / 2), 255, 255, 255, 255, 0, 0.5, 0));
    AddNewObject(new Engine::Label("Score", "pirulen.ttf", 16, halfW * 1 / 2 - 100, halfH + 50 * (-1 - PAGE_LINE / 2), 255, 255, 255, 255, 0, 0.5, 0));

    for (int i = 0; i < PAGE_LINE; i++) {
        AddNewObject(scoreboard[i][0] = new Engine::Label((i < total_line) ? std::to_string(i + 1) + ". " + table[i].Name : "" , "pirulen.ttf", 16, halfW * 1 / 4 - 100, halfH +  50 * (i - PAGE_LINE / 2), 255, 255, 255, 255, 0, 0.5, 0));
        AddNewObject(scoreboard[i][1] = new Engine::Label((i < total_line) ? std::to_string(table[i].Score) : "" , "pirulen.ttf", 16, halfW * 1 / 2 - 100, halfH +  50 * (i - PAGE_LINE / 2), 255, 255, 255, 255, 0, 0.5, 0));
    }
    current_head_line = 0;

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 5 / 3 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&FinalScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 5 / 3, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 1 / 2 - 300, halfH * 3 / 2 - 50, 100, 25);
    btn->SetOnClickCallback(std::bind(&FinalScoreBoardScene::DownOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PAGE DOWN", "pirulen.ttf", 12, halfW * 1 / 2 - 250, halfH * 3 / 2 - 37.5, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW  * 1 / 2 - 150, halfH * 3 / 2 - 50, 100, 25);
    btn->SetOnClickCallback(std::bind(&FinalScoreBoardScene::UpOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PAGE UP", "pirulen.ttf", 12, halfW * 1 / 2 - 100, halfH * 3 / 2 - 37.5, 0, 0, 0, 255, 0.5, 0.5));
    AddNewControlObject(new Engine::UserInfo());
    bgmInstance = AudioHelper::PlaySample("scoreboard.ogg", true, AudioHelper::BGMVolume);
}
void FinalScoreBoardScene::Terminate() {
    table.Save();
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void FinalScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("login");
}
void FinalScoreBoardScene::MovePage(int line) {
    if (total_line < PAGE_LINE) {
        return;
    }
    if ( ((line < 0) && current_head_line == 0 ) || ((line > 0) && current_head_line == total_line - 1) ) {
        return;
    }

    if (current_head_line + line >= total_line) {
        current_head_line = total_line - 1;
    } else if (current_head_line + line < 0) {
        current_head_line = 0;
    } else {
        current_head_line += line;
    }

    for (int i = current_head_line; i < current_head_line + PAGE_LINE; i++) {
        scoreboard[i - current_head_line][0]->Text = (i < total_line) ? std::to_string(i + 1) + ". "+ table[i].Name : "" ;
        scoreboard[i - current_head_line][1]->Text = (i < total_line) ? std::to_string(table[i].Score) : "" ;
    }
}
void FinalScoreBoardScene::UpOnClick(int line) {
    MovePage(-line);
}
void FinalScoreBoardScene::DownOnClick(int line) {
    MovePage(line);
}
