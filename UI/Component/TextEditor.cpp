#include "UI/Component/TextEditor.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include <allegro5/allegro.h>
#include <iostream>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"

namespace Engine {
    TextEditor::TextEditor(std::string img, std::string imgIn, const std::string &font, int fontSize, float x, float y, float w, float h, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float anchorX, float anchorY, bool show, const std::string &text, int flag)
        : label(text, font, fontSize, x + 10, y + h / 2 - ((float) fontSize / 2.0), r, g, b, a, anchorX, anchorY, 0),
        ImageButton(img, imgIn, x, y, w, h) {
            TextLine = text;
            ShiftPressed = false;
            Editting = false;
            showText = show;
            OnClickCallback = std::bind(&TextEditor::ToggleEditting, this);
            if (show) {
                toggleshow = nullptr;
            } else {
                toggleshow = new ImageButton("win/veryvisible.png", "win/veryvisible.png", x + w + 10 + h * 0.2, y + h * 0.2, h * 0.6, h * 0.6);
                toggleshow->SetOnClickCallback(std::bind(&TextEditor::ToggleOnClick, this, 1));
                IScene *currentScene = GameEngine::GetInstance().GetActiveScene();
                currentScene->AddNewControlObject(toggleshow); 
            }
        }
    void TextEditor::ClearText() {
        TextLine = "";
        label.Text = "";
    }
    void TextEditor::AddText(char text) {
        TextLine.push_back(text);
    }
    void TextEditor::DeleteText(void) {
        TextLine.pop_back();
    }
    void TextEditor::ToggleEditting(void) { Editting = !Editting; }
    void TextEditor::OnKeyDown(int keycode) {
        if (!Editting) {
            return;
        }
        if (keycode == ALLEGRO_KEY_ENTER) {
            Editting = false;
        }
        if (keycode == ALLEGRO_KEY_LSHIFT || keycode == ALLEGRO_KEY_RSHIFT) {
            ShiftPressed = true;
        } else if (keycode >= ALLEGRO_KEY_A && keycode <= ALLEGRO_KEY_Z) {
            if (ShiftPressed) {
                AddText(keycode - ALLEGRO_KEY_A + 'A');
            } else {
                AddText(keycode - ALLEGRO_KEY_A + 'a');
            }
        } else if (keycode >= ALLEGRO_KEY_0 && keycode <= ALLEGRO_KEY_9) {
            if (ShiftPressed) {
                switch(keycode - ALLEGRO_KEY_0) {
                case 0:
                    AddText(')');
                    break;
                case 1:
                    AddText('!');
                    break;
                case 2:
                    AddText('@');
                    break;
                case 3:
                    AddText('#');
                    break;
                case 4:
                    AddText('$');
                    break;
                case 5:
                    AddText('%');
                    break;
                case 6:
                    AddText('^');
                    break;
                case 7:
                    AddText('&');
                    break;
                case 8:
                    AddText('*');
                    break;
                case 9:
                    AddText('(');
                    break;
                default:
                    break;
                }
            } else {
                AddText(keycode - ALLEGRO_KEY_0 + '0');
            }
        } else if (keycode == ALLEGRO_KEY_MINUS) {
            if (ShiftPressed) {
                AddText('_');
            } else {
                AddText('-');
            }
        } else if (keycode == ALLEGRO_KEY_EQUALS) {
            if (ShiftPressed) {
                AddText('+');
            } else {
                AddText('=');
            }
        } else if (keycode == ALLEGRO_KEY_BACKSPACE) {
            if (TextLine.length() > 0) {
                DeleteText();
            }
        }
        if (showText) {
            label.Text = TextLine;
        } else {
            label.Text = "";
            for (int i = 0; i < TextLine.length(); i++) {
                label.Text += "*";
            }
        }
    }
    void TextEditor::OnKeyUp(int keycode) {
        if (keycode == ALLEGRO_KEY_LSHIFT || keycode == ALLEGRO_KEY_RSHIFT) {
            ShiftPressed = false;
        }
        if (showText) {
            label.Text = TextLine;
        } else {
            label.Text = "";
            for (int i = 0; i < TextLine.length(); i++) {
                label.Text += "*";
            }
        }
    }
    void TextEditor::Draw(void) const {
        ImageButton::Draw();
        label.Draw();
    }
    std::string TextEditor::getTextLine(void) {
        return TextLine;
    }
    void TextEditor::OnMouseDown(int button, int mx, int my) {
        if ((button & 1)) {
            Editting = mouseIn;
        }
    }
    void TextEditor::ToggleOnClick(int stage) {
        showText = !showText;
        if (showText) {
            label.Text = TextLine;
        } else {
            label.Text = "";
            for (int i = 0; i < TextLine.length(); i++) {
                label.Text += "*";
            }
        }
    }
}

