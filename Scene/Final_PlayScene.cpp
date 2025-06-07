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
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"
#include "Final_PlayScene.hpp"

void Final_PlayScene::Initialize() {
    Engine::Label *test;
    AddNewObject(test = new Engine::Label("test", "pirulen.ttf", 24, 0, 0, 255, 255, 255, 255));
}
void Final_PlayScene::Terminate() {
    IScene::Terminate();
}
void Final_PlayScene::Update(float deltaTime) {
    
}
void Final_PlayScene::Draw() const {
    IScene::Draw();
}
void Final_PlayScene::OnMouseDown(int button, int mx, int my) {
    
}
void Final_PlayScene::OnMouseMove(int mx, int my) {
    
}
void Final_PlayScene::OnMouseUp(int button, int mx, int my) {
    
}
void Final_PlayScene::OnKeyDown(int keyCode) {
    
}
void Final_PlayScene::Hit() {

}
int Final_PlayScene::GetMoney() const {

}
void Final_PlayScene::EarnMoney(int money) {

}
void Final_PlayScene::ReadEnemyWave() {

}