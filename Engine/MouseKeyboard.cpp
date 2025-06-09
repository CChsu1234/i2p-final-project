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
        Target << 0, 0, -1, 1;
        IObject::Visible = true;
        GameEngine::GetInstance().HideCursor();
        inControl = true;
    }
    void MouseKeyboard::RotateH(float theta) {
        Eigen::Matrix4f RotationMatrix {
            {cos(-theta), 0.0f, sin(-theta), 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {-sin(-theta), 0.0f, cos(-theta), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        Target = Eye + RotationMatrix * (Target - Eye);
    }
    void MouseKeyboard::RotateV(float theta) {

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
            float thetaH = dx / GameEngine::GetInstance().GetScreenSize().x; // horizontal
            float thetaV = dy / GameEngine::GetInstance().GetScreenSize().x; // vertical
            RotateH(thetaH);
            RotateV(thetaV);
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
        if (isKeyDown[UP]) {
            // TODO Move towards Target
        }
        if (isKeyDown[DOWN]) {
            // TODO Move towards Target
        }
        if (isKeyDown[LEFT]) {
            // TODO Move towards Target
        }
        if (isKeyDown[RIGHT]) {
            // TODO Move towards Target
        }
        // TODO SetModelViewMatrix
    }
    void MouseKeyboard::Draw() const {
        al_draw_line(
            GameEngine::GetInstance().GetScreenSize().x * 0.5, GameEngine::GetInstance().GetScreenSize().y * 0.5, GameEngine::GetInstance().GetScreenSize().x * (0.5 + Target(0) * 0.5), GameEngine::GetInstance().GetScreenSize().y * (0.5 + Target(1) * 0.5),
            al_map_rgb(255, 255, 255),
            1.0
        );
    }
}