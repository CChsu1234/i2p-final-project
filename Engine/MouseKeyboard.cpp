#include <allegro5/allegro.h>
#include <iostream>

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
        IObject::Visible = false;
        GameEngine::GetInstance().HideCursor();
        inControl = true;
    }
    void MouseKeyboard::OnMouseDown(int Button, int mx, int my) {
        inControl = true;
        GameEngine::GetInstance().HideCursor();
    }
    void MouseKeyboard::OnMouseMove(int mx, int my) {
        if (inControl) {
            float dx = mx;
            float dy = my;
            GameEngine::GetInstance().ResetMousePos();
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
}