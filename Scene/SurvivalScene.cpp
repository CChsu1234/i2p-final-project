#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <random>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "SurvivalScene.hpp"
#include "EndTwoScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TestObject3D.hpp"
#include "UI/Component/TestClick3D.hpp"
#include "UI/Component/CrossHair.hpp"
#include "File/User.hpp"

using namespace std;
static ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
static ALLEGRO_COLOR light_blue = al_map_rgb(173, 216, 230); // Light Blue: #ADD8E6
static ALLEGRO_COLOR light_pink = al_map_rgb(255, 182, 193); // Light Pink: #FFB6C1
static ALLEGRO_COLOR light_green = al_map_rgb(144, 238, 144); // Light Green: #90EE90
static Engine::Label *ShowTime;
static Engine::Label *ShowLife;
static float accumalateTime = 0.0f;
static float spawnTimer = 0.0f;

#define table Engine::GameEngine::GetInstance().GetUserTable()
#define currentUserid Engine::GameEngine::GetInstance().GetCurrentUser()


void SurvivalScene::Initialize() {

    lives=5;
    suvivalTime = 0;
    spawnNum = 1;
    spawnInterval = 3.0f;
    redFlashTimer = 0.0f;
    speed = 10.0f;

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Controller = new Engine::MouseKeyboard(true);
    AddNewControlObject(Controller);
    Engine::CrossHair *crosshair;
    AddNewObject(crosshair = new Engine::CrossHair(r, b, g));

    AddNewObject(ShowTime = new Engine::Label("Time: 60", "pirulen.ttf", 15 , halfW - 50, 10 , 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(ShowLife = new Engine::Label("Lives: 5", "pirulen.ttf", 15 , halfW- 50, 35 , 255, 255, 255, 255, 0.5, 0.5));

    double posX0 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posY0 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posX1 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posY1 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posX2 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posY2 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    
    targets.clear(); 
    targets.emplace_back(new Engine::TestClick3D(Eigen::Vector3f(posX0, posY0, -40), 1.0f, light_blue));
    targets.emplace_back(new Engine::TestClick3D(Eigen::Vector3f(posX1, posY1, -40), 1.0f, light_green));
    targets.emplace_back(new Engine::TestClick3D(Eigen::Vector3f(posX2, posY2, -40), 1.0f, light_pink));
    AddNewControlObject3D(targets[0]);
    AddNewControlObject3D(targets[1]);
    AddNewControlObject3D(targets[2]);
}
void SurvivalScene::Terminate() {
    Engine::GameEngine::GetInstance().SaveScore(suvivalTime, 2);
    IScene::Terminate();
}

void SurvivalScene::Draw() const {
    IScene::Draw();
    if (redFlashTimer > 0) {
        float alpha = redFlashTimer / redFlashDuration;
        ALLEGRO_COLOR redOverlay = al_map_rgba_f(1.0, 0.0, 0.0, 0.3f * alpha);
        al_draw_filled_rectangle(0, 0,
            Engine::GameEngine::GetInstance().GetScreenSize().x,
            Engine::GameEngine::GetInstance().GetScreenSize().y,
            redOverlay);
    }
}

void SurvivalScene::OnMouseDown(int button, int x, int y) {
    IScene::OnMouseDown(button, x, y);
    for (int i = 0; i < targets.size(); ++i) {
        if (targets[i]->Selected && targets[i]->visible) {
            targets[i]->Position = Eigen::Vector3f(0,0,-100000);
            targets[i]->updateDraw(targets[i]->Position);
            targets[i]->visible = false;
            break;
        }
    }
    
}
void SurvivalScene::Update(float deltaTime) {
    IScene::Update(deltaTime);

    if (redFlashTimer > 0)
        redFlashTimer -= deltaTime;

    if (lives <= 0) {
        EndGame();
        return;
    }

    accumalateTime += deltaTime;
    spawnTimer += deltaTime;

    if (accumalateTime >= 1.0f) {
        accumalateTime -= 1.0f;
        suvivalTime += 1;
        speed += suvivalTime*0.02;
        spawnInterval *= 0.95f; 
        if (spawnInterval < 0.5f) spawnInterval = 0.5f;
    }
    
    const int maxTargets = 30;
    if (spawnTimer >= spawnInterval && targets.size() < maxTargets) {
        spawnTimer = 0;
        SpawnTarget();
    }

    Eigen::Vector3f targetPos(0.0f, 0.0f, 20.0f);

    for (auto it = targets.begin(); it != targets.end();) {
        Engine::TestClick3D* tg = *it;

        if (!tg->visible) {
            it = targets.erase(it);  
            continue;
        }

        Eigen::Vector3f dir = (targetPos - tg->Position).normalized();
        tg->Position += dir * deltaTime * speed; 
        tg->updateDraw(tg->Position);

        if ((tg->Position - targetPos).norm() < 1.0f) {
            lives--;
            redFlashTimer = redFlashDuration; 
            ShowLife->Text = "Lives: " + std::to_string(lives);
            tg->visible = false;
            tg->Position = Eigen::Vector3f(0, 0, -100000);
            tg->updateDraw(tg->Position);
            it = targets.erase(it); 
        } else {
            ++it;
        }
    }

    ShowTime->Text = "Time: " + std::to_string(suvivalTime);
    ShowLife->Text = "Lives: " + std::to_string(lives);
}
void SurvivalScene::SpawnTarget() {
    float x = -20.0f + 40.0f * ((float)rand() / RAND_MAX);
    float y = -20.0f + 40.0f * ((float)rand() / RAND_MAX);
    float z = -40.0f;
    Eigen::Vector3f pos(x, y, z);  

    ALLEGRO_COLOR col[4] = {
        al_map_rgb(255, 255, 255),
        al_map_rgb(173, 216, 230),
        al_map_rgb(255, 182, 193),
        al_map_rgb(144, 238, 144)
    };

    ALLEGRO_COLOR decide = col[rand() % 4];
    Engine::TestClick3D* tg = new Engine::TestClick3D(pos, 1.0f, decide);  // 固定大小
    AddNewControlObject3D(tg); 
    targets.emplace_back(tg);
}

void SurvivalScene::EndGame() {
    EndTwoScene *endscene = dynamic_cast<EndTwoScene *>(Engine::GameEngine::GetInstance().GetScene("finalendtwo"));
    endscene->survivalTime = suvivalTime;
    Engine::GameEngine::GetInstance().ChangeScene("finalendtwo");
}

void SurvivalScene::Hit() {

}

void SurvivalScene::ConstructUI() {

}