#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <cmath>
#include "Resource/Eigen/Dense"

#include "MouseKeyboard.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Engine/ModelView.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameEngine.hpp"

#define M_PI 3.14159265358979323846

namespace Engine {
    MouseKeyboard::MouseKeyboard() : IControl(), IObject() {
        v = 0.05f;
        Eye << 0.0f, 0.0f, 0.0f, 1.0f;
        thetaH = 0.0f;
        thetaV = 0.0f;
        IObject::Visible = true;
        GameEngine::GetInstance().HideCursor();
        inControl = true;
        for (int i = 0; i < 4; i++) {
            isKeyDown[i] = false;
        }
    }
    void MouseKeyboard::OnMouseDown(int Button, int mx, int my) {
        inControl = true;
        GameEngine::GetInstance().HideCursor();
    }
    void MouseKeyboard::OnMouseMove(int mx, int my) {
        if (inControl) {
            float dx = mx - GameEngine::GetInstance().GetScreenSize().x / 2;
            float dy = my - GameEngine::GetInstance().GetScreenSize().y / 2;
            GameEngine::GetInstance().ResetMousePos();
            thetaH -= dx / (GameEngine::GetInstance().GetScreenSize().x) * 0.5 * 90.0f; // horizontal
            thetaV -= dy / (GameEngine::GetInstance().GetScreenSize().x) * 0.5 * 90.0f; // vertical
            if (thetaV > 90.0f) {
                thetaV = 90.0f;
            } else if (thetaV < -90.0f) {
                thetaV = -90.0f;
            }
            if (thetaH > 360.0f) {
                thetaH -= 360.0f;
            } else if (thetaH < 0.0f) {
                thetaH += 360.0f;
            }
        }
        // TODO Move Target
    }
    void MouseKeyboard::OnKeyDown(int keyCode) {
        if (keyCode == ALLEGRO_KEY_ESCAPE) {
            inControl = false;
            GameEngine::GetInstance().ShowCursor();
        }
        if (keyCode == ALLEGRO_KEY_W) {
            isKeyDown[UP] = true;
        }
        if (keyCode == ALLEGRO_KEY_A) {
            isKeyDown[LEFT] = true;
        }
        if (keyCode == ALLEGRO_KEY_S) {
            isKeyDown[DOWN] = true;
        }
        if (keyCode == ALLEGRO_KEY_D) {
            isKeyDown[RIGHT] = true;
        }
    }
    void MouseKeyboard::OnKeyUp(int keyCode) {
        if (keyCode == ALLEGRO_KEY_W) {
            isKeyDown[UP] = false;
        } else if (keyCode == ALLEGRO_KEY_A) {
            isKeyDown[LEFT] = false;
        } else if (keyCode == ALLEGRO_KEY_S) {
            isKeyDown[DOWN] = false;
        } else if (keyCode == ALLEGRO_KEY_D) {
            isKeyDown[RIGHT] = false;
        }
    }
    void MouseKeyboard::Update(float deltaTime) {
        float x = cos((thetaH) * M_PI / 180.0f) * v;
        float z = sin((thetaH) * M_PI / 180.0f) * v;
        if (isKeyDown[UP]) {
            Eye(0) += x;
            Eye(2) += z;
        }
        if (isKeyDown[DOWN]) {
            Eye(0) -= x;
            Eye(2) -= z;
        }
        if (isKeyDown[LEFT]) {
            Eye(0) += z;
            Eye(2) -= x;
        }
        if (isKeyDown[RIGHT]) {
            Eye(0) -= z;
            Eye(2) += x;
        }
        // std::cout << thetaH << std::endl;
        SetModelViewMatrix(thetaH, thetaV, Eye);
        // TODO SetModelViewMatrix

    }
}