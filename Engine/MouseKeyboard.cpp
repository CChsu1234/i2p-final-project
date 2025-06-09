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
#include "Engine/GameEngine.hpp"

namespace Engine {
    MouseKeyboard::MouseKeyboard() : IControl(), IObject() {
        v = 1.0f;
        Eye << 0, 0, 0, 1;
        Dir << 1, 0, 0, 1;
        thetaH = 90;
        thetaV = 0;
        IObject::Visible = true;
        GameEngine::GetInstance().HideCursor();
        inControl = true;
    }
    void MouseKeyboard::RotateH() {
        Eigen::Matrix4f RotationMatrix {
            {cos(-thetaH), 0.0f, sin(-thetaH), 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {-sin(-thetaH), 0.0f, cos(-thetaH), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        Dir = RotationMatrix * Dir;
    }
    void MouseKeyboard::RotateV() {
        Eigen::Matrix4f RotationMatrix {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, cos(-thetaV), -sin(-thetaV), 0.0f},
            {0.0f, sin(-thetaV), cos(-thetaV), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        Dir = RotationMatrix * Dir;
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
            thetaH += dx / GameEngine::GetInstance().GetScreenSize().x; // horizontal
            thetaV += dy / GameEngine::GetInstance().GetScreenSize().x; // vertical
            if (thetaV > 180.0f) {
                thetaV = 180.0f;
            } else if (thetaV < -180.0f) {
                thetaV = -180.0f;
            }
            if (thetaH > 360.0f) {
                thetaH -= 360.0f;
            } else if (thetaH < 0.0f) {
                thetaH += 360.0f;
            }
            Dir << 0, 0, 1, 1;
            RotateV();
            RotateH();
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
        float x = cos(thetaV);
        float z = sin(thetaV);
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
        // TODO SetModelViewMatrix
    }
    void MouseKeyboard::Draw() const {
        al_draw_line(
            GameEngine::GetInstance().GetScreenSize().x * 0.25, GameEngine::GetInstance().GetScreenSize().y * 0.25, GameEngine::GetInstance().GetScreenSize().x * (0.25 + Eye(0) * 0.05 * 0.25), GameEngine::GetInstance().GetScreenSize().y * (0.25 + Eye(2) * 0.05 * 0.25),
            al_map_rgb(255, 255, 255),
            1.0
        );
        al_draw_line(
            GameEngine::GetInstance().GetScreenSize().x * 0.75, GameEngine::GetInstance().GetScreenSize().y * 0.75, GameEngine::GetInstance().GetScreenSize().x * (0.75 + Dir(0) * 0.25), GameEngine::GetInstance().GetScreenSize().y * (0.75 + Dir(1) * 0.25),
            al_map_rgb(255, 255, 255),
            1.0
        );
    }
}