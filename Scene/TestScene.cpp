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
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TestObject3D.hpp"
#include "UI/Component/TestClick3D.hpp"
#include "UI/Component/CrossHair.hpp"
#include "File/User.hpp"


void TestScene::Initialize() {
    Engine::TestClick3D *test;
    AddNewControlObject3D(test = new Engine::TestClick3D());
    Controller = new Engine::MouseKeyboard();
    AddNewControlObject(Controller);
    Engine::CrossHair *crosshair;
    AddNewObject(crosshair = new Engine::CrossHair());
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
    
}