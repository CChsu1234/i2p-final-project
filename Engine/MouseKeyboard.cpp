#include <allegro5/allegro.h>

#include "MouseKeyboard.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Engine/ModelView.hpp"

namespace Engine {
    MouseKeyboard::MouseKeyboard() : IControl(), IObject() {
        v = 1.0f;
        Eye << 0, 0, 0, 1;
        Target << 0, 0, -1, 1;
        IObject::Visible = false;
    }
    void MouseKeyboard::OnMouseMove(int mx, int my) {
        // TODO Move Target
    }
    void MouseKeyboard::OnKeyDown(int keyCode) {
        if (keyCode == ALLEGRO_KEY_W) {
            isKeyDown[UP] = true;
        } else if (keyCode == ALLEGRO_KEY_A) {
            isKeyDown[LEFT] = true;
        } else if (keyCode == ALLEGRO_KEY_S) {
            isKeyDown[DOWN] = true;
        } else if (keyCode == ALLEGRO_KEY_D) {
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