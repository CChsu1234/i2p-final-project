#ifndef TEXTEDITOR_HPP
#define TEXTEDITOR_HPP
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include <string>

namespace Engine {
    class TextEditor : public ImageButton {
    private:
        std::string TextLine;
        bool ShiftPressed;
        bool Editting;
        Label label;
    public:
        explicit TextEditor(std::string img, std::string imaIn, const std::string &font, int fontsize, float x, float y, float w = 0, float h = 0, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 0.5, const std::string &text = "", int flag = 0);
        void AddText(char text);
        void DeleteText(void);
        void OnKeyDown(int keycode) override;
        void OnKeyUp(int keycode) override;
        void Draw(void) const override;
        void ToggleEditting(void);
        std::string getTextLine(void);
    };
}

/*
        explicit ImageButton(std::string img, std::string imgIn, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
        explicit Label(const std::string &text, const std::string &font, int fontSize, float x, float y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 0, int flag = 0);
*/
#endif // TEXTEDITOR_HPP
