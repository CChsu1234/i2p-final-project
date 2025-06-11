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
        bool showText;
        ImageButton *toggleshow;
        Label label;
    public:
        explicit TextEditor(std::string img, std::string imaIn, const std::string &font, int fontsize, float x, float y, float w = 0, float h = 0, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 0.5, bool show = true, const std::string &text = "", int flag = 0);
        void ClearText();
        void ToggleOnClick(int stage);
        void AddText(char text);
        void DeleteText(void);
        void OnMouseDown(int Button, int mx, int my) override;
        void OnKeyDown(int keycode) override;
        void OnKeyUp(int keycode) override;
        void Draw(void) const override;
        void ToggleEditting(void);
        std::string getTextLine(void);
    };
}

#endif // TEXTEDITOR_HPP
