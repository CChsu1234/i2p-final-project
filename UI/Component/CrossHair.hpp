#ifndef CROSSHAIR_HPP
#define CROSSHAIR_HPP

#include <allegro5/allegro_color.h>
#include "Engine/IObject.hpp"

namespace Engine {
    struct Component {
        bool Enable;
        float Opacity;
        int Thickness;
        int Length;
        int Offset;
        Component(bool enable, float opacity, int length, int thickness, int offset) {
            Enable = enable;
            Opacity = opacity;
            Thickness = thickness;
            Length = length;
            Offset = offset;
        }
        Component(bool enable, float opacity, int thickness) {
            Enable = enable;
            Opacity = opacity;
            Thickness = thickness;
            Length = 0;
            Offset = 0;
        }
    };
    class CrossHair : public IObject {
    private:
        // Crosshair settings
        // Copy from valorant crosshair setting
        /*
        // Color
        std::string Color;
        // OutLine
        bool OutLine;
        float OutLineOpacity; // min = 0, max = 1
        int OutLineThickness; // min = 1, max = 6;
        // Center dot
        bool CenterDot;
        float CenterDotOpacity;
        int 
        // InnerLine
        bool InnerLine;
        float InnerLineOpacity;
        int InnerLineLength;
        float InnerLineThickness
        */
        unsigned char R, G, B;
        Component OutLine;
        Component CenterDot;
        Component InnerLine;
        Component OuterLine;
    public:
        CrossHair();
        CrossHair(unsigned char r, unsigned char g, unsigned char b, bool ol, float olOpacity, int olThickness, bool cd, float cdOpacity, int cdThickness, bool in, float inOpacity, int inLength, int inThickness, int inOffset, bool out, float outOpacity, int outLength, int outThickness, int outOffset);
        void SetCrossHair(unsigned char r, unsigned char g, unsigned char b, bool ol, float olOpacity, int olThickness, bool cd, float cdOpacity, int cdThickness, bool in, float inOpacity, int inLength, int inThickness, int inOffset, bool out, float outOpacity, int outLength, int outThickness, int outOffset);
        void Draw() const override;
    };
}

#endif