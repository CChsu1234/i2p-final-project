#include "UI/Component/TextEditor.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include <allegro5/allegro.h>
#include <iostream>
#include <string>

namespace Engine {
    TextEditor::TextEditor(std::string img, std::string imgIn, const std::string &font, int fontSize, float x, float y, float w, float h, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float anchorX, float anchorY, const std::string &text, int flag)
        : label(text, font, fontSize, x + 10, y + h / 2 - ((float) fontSize / 2.0), r, g, b, a, anchorX, anchorY, 0),
        ImageButton(img, imgIn, x, y, w, h) {
            TextLine = text;
            ShiftPressed = false;
            Editting = false;
            OnClickCallback = std::bind(&TextEditor::ToggleEditting, this);
        }
/*
        explicit ImageButton(std::string img, std::string imgIn, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
        explicit Label(const std::string &text, const std::string &font, int fontSize, float x, float y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 0, int flag = 0);
*/
    void TextEditor::AddText(char text) {
        TextLine.push_back(text);
    }
    void TextEditor::DeleteText(void) {
        TextLine.pop_back();
    }
    void TextEditor::ToggleEditting(void) { Editting = !Editting; }
    void TextEditor::OnKeyDown(int keycode) {
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
        label.Text = TextLine;
    }
    void TextEditor::OnKeyUp(int keycode) {
        if (keycode == ALLEGRO_KEY_LSHIFT || keycode == ALLEGRO_KEY_RSHIFT) {
            ShiftPressed = false;
        }
        label.Text = TextLine;
    }
    void TextEditor::Draw(void) const {
        ImageButton::Draw();
        label.Draw();
    }
    std::string TextEditor::getTextLine(void) {
        return TextLine;
    }
}

