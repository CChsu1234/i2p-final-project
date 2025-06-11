#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <random>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "TestScene.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TestObject3D.hpp"
#include "UI/Component/TestClick3D.hpp"
#include "UI/Component/CrossHair.hpp"
#include "UI/Component/TargetBall.hpp"
#include "File/User.hpp"

ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
ALLEGRO_COLOR light_blue = al_map_rgb(173, 216, 230); // Light Blue: #ADD8E6
ALLEGRO_COLOR light_pink = al_map_rgb(255, 182, 193); // Light Pink: #FFB6C1
ALLEGRO_COLOR light_green = al_map_rgb(144, 238, 144); // Light Green: #90EE90

Engine::Label *ShowTimer;
Engine::Label *ShowScore;
Engine::Label *ShowHitRate;

float timeAccumulator = 0.0f;
bool hasEnded = false;


void TestScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Controller = new Engine::MouseKeyboard();
    AddNewControlObject(Controller);
    Engine::CrossHair *crosshair;
    AddNewObject(crosshair = new Engine::CrossHair());

    AddNewObject(ShowTimer = new Engine::Label("Time: 60", "pirulen.ttf", 15 , halfW - 50, 10 , 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(ShowScore = new Engine::Label("Score: 0", "pirulen.ttf", 15 , halfW- 100, 35 , 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(ShowHitRate = new Engine::Label("Hit Rate: -", "pirulen.ttf", 15 , halfW +30, 35 , 255, 255, 255, 255, 0.5, 0.5));

    double posX0 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posY0 = -10.0f + 20.0f *((double)rand() / RAND_MAX);
    double posX1 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posY1 = -10.0f + 20.0f *((double)rand() / RAND_MAX);
    double posX2 = -20.0f + 40.0f *((double)rand() / RAND_MAX);
    double posY2 = -10.0f + 20.0f *((double)rand() / RAND_MAX);
   
    AddNewControlObject3D(target[0] = new Engine::TestClick3D(Eigen::Vector3f(posX0, posY0, -30), 2.0f, light_blue));
    AddNewControlObject3D(target[1] = new Engine::TestClick3D(Eigen::Vector3f(posX1, posY1, -30), 2.0f, light_green));
    AddNewControlObject3D(target[2] = new Engine::TestClick3D(Eigen::Vector3f(posX2, posY2, -30), 2.0f, light_pink));


    hitCount = 0;
    totalShots = 0;
    score = 0;
    timeLeft = 60;
}


void TestScene::Terminate() {
    IScene::Terminate();
}

void TestScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    timeAccumulator += deltaTime;
    if (timeAccumulator >= 1.0f) {
        timeLeft--;
        timeAccumulator -= 1.0f;
    }
    if (timeLeft <= 0 && !hasEnded) {
        hasEnded = true;
        EndGame();
    }
    ShowTimer->Text = "Time: " + std::to_string(timeLeft) ;
    ShowScore->Text = "Score: " + std::to_string(score);
    if (totalShots) ShowHitRate ->Text = "Hit Rate: " + std::to_string((int) 100 * hitCount / totalShots);
}

void TestScene::OnMouseDown(int button, int mx, int my) {
    bool foundHit = false;
    for (int i = 0; i < 3; ++i) {
        if (target[i]->Selected) {
            score += 1;
            hitCount++;
            totalShots++;
            
            RespawnTarget(i);
            foundHit = true;
            break;
        }
    }
    if (!foundHit) {
        score -= 1;
        totalShots++;
    }
    IScene::OnMouseDown(button, mx, my);
}
void TestScene::RespawnTarget(int i) {
    double posX0, posY0;
    bool valid = false;
    int attempts = 0;

    while (!valid && attempts < 100) {
        posX0 = -20.0f + 40.0f * ((double)rand() / RAND_MAX);
        posY0 = -10.0f + 20.0f * ((double)rand() / RAND_MAX);
        Eigen::Vector2f newPos(posX0, posY0);
        valid = true;
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            Eigen::Vector3f otherPos = target[j]->Position;
            Eigen::Vector2f other2D(otherPos.x(), otherPos.y());
            if ((newPos - other2D).norm() < 4.0f) {
                valid = false;
                break;
            }
        }
        attempts++;
    }

    target[i]->updateDraw(Eigen::Vector3f(posX0, posY0, -30));
}

void TestScene::Draw() const {
    IScene::Draw();
    //labels for hit, hit rate and time 
}

void TestScene::Hit() {
    totalShots++;
    hitCount++;
}

void TestScene::Miss() {
    totalShots++;
}

void TestScene::SpawnTarget() {
    
}

void TestScene::EndGame() {
    
    // Engine::GameEngine::GetInstance().ChangeScene("ScoreScene");
}

int TestScene::GetMoney() const { return 0; }
void TestScene::EarnMoney(int money) {}
void TestScene::ReadEnemyWave() {}
void TestScene::ConstructUI() {}
void TestScene::UIBtnClicked(int id) {}