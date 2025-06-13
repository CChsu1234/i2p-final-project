#include <allegro5/allegro_primitives.h>
#include <iostream>

#include "CrossHair.hpp"
#include "Engine/GameEngine.hpp"

namespace Engine {

    CrossHair::CrossHair() : 
        // default: 1422 crosshair
        IObject(),
        R(0), G(255), B(255),
        OutLine(false, 0.5f, 1),
        CenterDot(false, 1.0f, 1),
        InnerLine(true, 1.0f, 4, 2, 2),
        OuterLine(false, 0.35f, 2, 2, 10) {
    }
    CrossHair::CrossHair(unsigned char r, unsigned char g, unsigned char b) :
        IObject(),
        R(r), G(g), B(b),
        OutLine(false, 0.5f, 1),
        CenterDot(false, 1.0f, 1),
        InnerLine(true, 1.0f, 4, 2, 2),
        OuterLine(false, 0.35f, 2, 2, 10){}
    
    CrossHair::CrossHair(unsigned char r, unsigned char g, unsigned char b, bool ol, float olOpacity, int olThickness, bool cd, float cdOpacity, int cdThickness, bool in, float inOpacity, int inLength, int inThickness, int inOffset, bool out, float outOpacity, int outLength, int outThickness, int outOffset) :
        IObject(),
        R(r), G(g), B(b),
        OutLine(ol, olOpacity, olThickness),
        CenterDot(cd, cdOpacity, cdThickness), 
        InnerLine(in, inOpacity, inLength, inThickness, inOffset),
        OuterLine(out, outOpacity, outLength, outThickness, outOffset) {
    }
    void CrossHair::SetCrossHair(unsigned char r, unsigned char g, unsigned char b, bool ol, float olOpacity, int olThickness, bool cd, float cdOpacity, int cdThickness, bool in, float inOpacity, int inLength, int inThickness, int inOffset, bool out, float outOpacity, int outLength, int outThickness, int outOffset) {

    }
    void CrossHair::Draw() const {
        float midX = GameEngine::GetInstance().GetScreenSize().x * 0.5;
        float midY = GameEngine::GetInstance().GetScreenSize().y * 0.5;

        if (CenterDot.Enable) {
            if (OutLine.Enable) {
                al_draw_filled_rectangle(
                    midX + (CenterDot.Thickness * 0.5 + OutLine.Thickness),
                    midY + (CenterDot.Thickness * 0.5 + OutLine.Thickness),
                    midX - (CenterDot.Thickness * 0.5 + OutLine.Thickness),
                    midY - (CenterDot.Thickness * 0.5 + OutLine.Thickness),
                    al_map_rgba_f(0, 0, 0, 255 * OutLine.Opacity)
                );     
            }
            al_draw_filled_rectangle(
                midX + CenterDot.Thickness * 0.5,
                midY + CenterDot.Thickness * 0.5,
                midX - CenterDot.Thickness * 0.5,
                midY - CenterDot.Thickness * 0.5,
                al_map_rgba_f(R, G, B, 255 * CenterDot.Opacity)
            );
        }

        if (InnerLine.Enable) {
            float xOffset[4] = {1.0f, 0.0f, -1.0f, 0.0f};
            float yOffset[4] = {0.0f, -1.0f, 0.0f, 1.0f};
            float xThickness[4] = {0.0f, 1.0f, 0.0f, 1.0f};
            float yThickness[4] = {1.0f, 0.0f, 1.0f, 0.0f};
            float xLength[4] = {1.0f, 0.0f, -1.0f, 0.0f};
            float yLength[4] = {0.0f, -1.0f, 0.0f, 1.0f};
            for (int i = 0; i < 4; i++) {
                al_draw_filled_rectangle(
                    midX + (xOffset[i] * InnerLine.Offset) + xLength[i] * InnerLine.Length + xThickness[i] * InnerLine.Thickness * 0.5f,
                    midY + (yOffset[i] * InnerLine.Offset) + yLength[i] * InnerLine.Length + yThickness[i] * InnerLine.Thickness * 0.5f,
                    midX + (xOffset[i] * InnerLine.Offset) - xThickness[i] * InnerLine.Thickness * 0.5f,
                    midY + (yOffset[i] * InnerLine.Offset) - yThickness[i] * InnerLine.Thickness * 0.5f,
                    al_map_rgba(R, G, B, 255 * InnerLine.Opacity)
                );
            }
        }

        if (OuterLine.Enable) {
            float xOffset[4] = {1.0f, 0.0f, -1.0f, 0.0f};
            float yOffset[4] = {0.0f, -1.0f, 0.0f, 1.0f};
            float xThickness[4] = {0.0f, 1.0f, 0.0f, 1.0f};
            float yThickness[4] = {1.0f, 0.0f, 1.0f, 0.0f};
            float xLength[4] = {1.0f, 0.0f, -1.0f, 0.0f};
            float yLength[4] = {0.0f, -1.0f, 0.0f, 1.0f};
            for (int i = 0; i < 4; i++) {
                al_draw_filled_rectangle(
                    midX + (xOffset[i] * OuterLine.Offset) + xLength[i] * OuterLine.Length + xThickness[i] * OuterLine.Thickness * 0.5f,
                    midY + (yOffset[i] * OuterLine.Offset) + yLength[i] * OuterLine.Length + yThickness[i] * OuterLine.Thickness * 0.5f,
                    midX + (xOffset[i] * OuterLine.Offset) - xThickness[i] * OuterLine.Thickness * 0.5f,
                    midY + (yOffset[i] * OuterLine.Offset) - yThickness[i] * OuterLine.Thickness * 0.5f,
                    al_map_rgba(R, G, B, 255 * OuterLine.Opacity)
                );
            }
        }
    }
 }