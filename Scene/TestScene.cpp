#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/MouseKeyboard.hpp"
#include "TestScene.hpp"
#include "EndScene.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TestObject3D.hpp"
#include "UI/Component/TestClick3D.hpp"
#include "UI/Component/CrossHair.hpp"
#include "File/User.hpp"


void TestScene::Initialize() {
<<<<<<< HEAD
    Engine::TestClick3D *test;
    AddNewControlObject3D(test = new Engine::TestClick3D());
    Controller = new Engine::MouseKeyboard();
    AddNewControlObject(Controller);
    Engine::CrossHair *crosshair;
    AddNewObject(crosshair = new Engine::CrossHair());
=======
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
>>>>>>> fc1b24d (Scene BackGround)
}
void TestScene::Terminate() {
    IScene::Terminate();
}
void TestScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
}
void TestScene::Draw() const {
    IScene::Draw();
}
void TestScene::Hit() {

}
int TestScene::GetMoney() const {
    return 0;
}
void TestScene::EarnMoney(int money) {

}
void TestScene::ReadEnemyWave() {

}
void TestScene::ConstructUI() {

}
void TestScene::UIBtnClicked(int id) {
    
<<<<<<< HEAD
}
=======
}

void TestScene::EndGame() {
    auto& engine = Engine::GameEngine::GetInstance();
    auto endscene = dynamic_cast<EndScene*>(engine.GetScene("FinalEnd"));
    if (endscene) {
        endscene->score = score;
        endscene->rate = (int) 100 * hitCount / totalShots;
    }
    engine.ChangeScene("win");
    Engine::GameEngine::GetInstance().ChangeScene("FinalEnd");
}

int TestScene::GetMoney() const { return 0; }
void TestScene::EarnMoney(int money) {}
void TestScene::ReadEnemyWave() {}
void TestScene::ConstructUI() {}
void TestScene::UIBtnClicked(int id) {}
>>>>>>> fc1b24d (Scene BackGround)
