#include <algorithm>
#include <allegro5/allegro.h>
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
#include "File/User.hpp"


void TestScene::Initialize() {
    Engine::TestObject3D *test;
    AddNewObject3D(test = new Engine::TestObject3D());
    Controller = new Engine::MouseKeyboard();
    AddNewControlObject(Controller);
}
void TestScene::Terminate() {
    IScene::Terminate();
}
void TestScene::Update(float deltaTime) {
    
}
void TestScene::Draw() const {
    IScene::Draw();
}
void TestScene::OnMouseDown(int button, int mx, int my) {
    
}
void TestScene::OnMouseMove(int mx, int my) {
    
}
void TestScene::OnMouseUp(int button, int mx, int my) {
    
}
void TestScene::OnKeyDown(int keyCode) {
    
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