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
#include "MultiPlayer.hpp"
#include "EndScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TestObject3D.hpp"
#include "UI/Component/TestClick3D.hpp"
#include "UI/Component/CrossHair.hpp"
#include "File/User.hpp"

#define table Engine::GameEngine::GetInstance().GetUserTable()
#define currentUserid Engine::GameEngine::GetInstance().GetCurrentUser()

void MultiPlayer::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Controller = new Engine::MouseKeyboard(true);
    AddNewControlObject(Controller);
    Engine::CrossHair *crosshair;
    AddNewObject(crosshair = new Engine::CrossHair());

    AddNewObject(ShowTimer = new Engine::Label("Time: 60", "pirulen.ttf", 15 , halfW - 50, 10 , 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(ShowScore = new Engine::Label("Score: 0", "pirulen.ttf", 15 , halfW- 100, 35 , 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(ShowHitRate = new Engine::Label("Hit Rate: -", "pirulen.ttf", 15 , halfW +30, 35 , 255, 255, 255, 255, 0.5, 0.5));

    AddNewObject(CountDown = new Engine::Label("", "pirulen.ttf", 48, halfW, halfH, 255, 255, 255, 255, 0.5f, 0.5f, ALLEGRO_ALIGN_CENTER));

    hitRateVariation.clear();
    scoreVariation.clear();

    for (int i = 0; i < 10; i++) {
        double posX = -20.0f + 40.0f *((double)rand() / RAND_MAX);
        double posY = -10.0f + 20.0f *((double)rand() / RAND_MAX);
        target[i] = new Engine::TestClick3D(Eigen::Vector3f(posX, posY, -30), 2.0f, light_blue);
    }
    
    hitCount = 0;
    totalShots = 0;
    score = 0;
    timeLeft = 60;
    myTotalBall = 5;
    opponentTotalBall = 5;
    StartCountDown = 6.0f;
    delta = 0;
}
void MultiPlayer::Terminate() {
    Engine::GameEngine::GetInstance().SaveScore(score, 1);
    IScene::Terminate();
}
void MultiPlayer::Update(float deltaTime) {
    if (StartCountDown >= 0.0f) {
        StartCountDown -= deltaTime;
        CountDown->Text = std::to_string((int)(StartCountDown / 1));
        Host->SendRecv((char*)std::to_string(myTotalBall).c_str(), sizeof(std::to_string(myTotalBall).length() + 1));
    } else {
        CountDown->Text = "";
        std::cout << myTotalBall << std::endl;

        if (myTotalBall + delta == 10 || myTotalBall + delta == 0) {
            EndGame();
        }

        for (int i = 0; i < myTotalBall + delta; i++) {
            target[i]->Transform();
        }
        int nowOpponentTotalBall = atoi(Host->read());
        if (nowOpponentTotalBall != opponentTotalBall) {
            delta += opponentTotalBall - nowOpponentTotalBall;
            opponentTotalBall = nowOpponentTotalBall; 
        }
        Host->SendRecv((char*)std::to_string(myTotalBall).c_str(), sizeof(std::to_string(myTotalBall).length() + 1));
        // std::cout<<"update"<<std::endl;
        IScene::Update(deltaTime);
        accumalateTime += deltaTime;
        if (accumalateTime >= 1.0f) {
            accumalateTime -= 1.0f;
            // timeLeft -= 1;
            scoreVariation.push_back(score);
            if (totalShots) hitRateVariation.push_back(100 * hitCount / totalShots);
            else hitRateVariation.push_back(0);
        }
        // if (timeLeft<=0) EndGame();
        ShowTimer->Text = "Time: " + std::to_string(timeLeft);
        ShowScore->Text = "Score: " + std::to_string(score);
        if (totalShots > 0) ShowHitRate->Text = "Hit Rate: " + std::to_string((int) 100 * hitCount / totalShots);
        else ShowHitRate->Text = "Hit Rate: -";
        
    }
}
void MultiPlayer::Draw() const {
    IObject3D::Draw();
    IScene::Draw();
}
void MultiPlayer::EndGame() {
    Engine::GameEngine::GetInstance().ChangeScene("finalStart");
}

 void MultiPlayer::OnMouseDown(int button, int x, int y) {
    IScene::OnMouseDown(button, x, y);
    bool foundHit = false;
    for (int i = 0; i < myTotalBall + delta; ++i) {
        if (target[i]->Selected) {
            score += 1;
            hitCount++;
            totalShots++;
            myTotalBall--;
            // 重新生成目標
            RespawnTarget(i);
            foundHit = true;
            break;
        }
    }
    if (!foundHit) {
        score -= 1;
        totalShots++;
    }
}
void MultiPlayer::RespawnTarget(int i) {
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
void MultiPlayer::SetHost(Engine::NetworkManager *host) {
    Host = host;
}
void MultiPlayer::SetMode(int mode) {
    Mode = mode;
}