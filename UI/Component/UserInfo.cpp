#include "UserInfo.hpp"

#include "Engine/GameEngine.hpp"

#define currentUser Engine::GameEngine::GetInstance().GetCurrentUser()

namespace Engine {
    UserInfo::UserInfo() : Label("", "pirulen.ttf", 16, 25, 25, 255, 255, 255, 255, 0, 0, 0) {
        if (currentUser) {
            Text = 
                "User: " + currentUser->Name + '\n';
        } else {
            Text = "login";
        }
    }
    void UserInfo::Update(float deltaTime) {
        if (currentUser) {
            Text = 
                "User: " + currentUser->Name + '\n';
        } else {
            Text = "login";
        }
    }
}