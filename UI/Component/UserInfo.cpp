#include <iostream>

#include "UserInfo.hpp"

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/Collider.hpp"

#define table Engine::GameEngine::GetInstance().GetUserTable()
#define currentUserid Engine::GameEngine::GetInstance().GetCurrentUser()

namespace Engine {
    UserInfo::UserInfo() : Label("", "pirulen.ttf", 16, 25, 25, 255, 255, 255, 255, 0, 0, 0), IControl() {
        if (currentUserid != -1) {
            Text = 
                "User: " + table.at(currentUserid).Name + '\n';
        } else {
            Text = "login";
        }
    }
    void UserInfo::Update(float deltaTime) {
        if (currentUserid != -1) {
            Text = 
                "User: " + table.at(currentUserid).Name + '\n';
        } else {
            Text = "login";
        }
    }
    void UserInfo::OnMouseDown(int button, int mx, int my) {
        if ((button & 1)) {
            Point pnt(mx, my);
            Point rectPos(25, 25);
            Point rectSize(50, 150);
            if (Collider::IsPointInRect(pnt, rectPos, rectSize)) {
                if (currentUserid != -1) {
                    GameEngine::GetInstance().ChangeScene("login");
                } else {
                    GameEngine::GetInstance().ChangeScene("login");
                }
            }
        }
    }
}