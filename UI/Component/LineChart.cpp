#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>

#include "LineChart.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
    LineChart::LineChart(std::string name, float x, float y, float w, float h, std::vector<float> xy, std::string unit_x, std::string unit_y, unsigned char r, unsigned char g, unsigned char b) : IObject(), Pos(x, y), Size(w, h), Color(al_map_rgb(r, g, b)) {
        total_x = 0;
        max_y = -1000000.0f;
        min_y = 1000000.0f;
        for (auto i : xy) {
            XY.emplace_back(i);
            total_x++;
            if (i  < min_y) {
                min_y = i;
            }
            if (i > max_y) {
                max_y = i;
            }
        }
        float highestY = Pos.y + Size.y * 0.1;
        std::stringstream high;
        high << max_y;
        float lowestY = Pos.y + Size.y * 0.9;
        std::stringstream low;
        low << min_y;
        
        highest = new Label(high.str(), "pirulen.ttf", 12, x - 5.0f, highestY, r, g, b, 255, 1.0f, 0.0f, ALLEGRO_ALIGN_RIGHT);
        lowest = new Label(low.str(), "pirulen.ttf", 12, x - 5.0f, lowestY, r, g, b, 255, 1.0f, 0.0f, ALLEGRO_ALIGN_RIGHT);
        Name = new Label(name, "pirulen.ttf", 20, x + w / 2, y - 15, r, g, b, 255, 0.5f, 0.5f, 0);
        Unit_x = new Label(unit_x, "pirulen.ttf", 12, x - 15, y + 15, r, g, b, 255, 0.5f, 0.5f, 0);
        Unit_y = new Label(unit_y, "pirulen.ttf", 12, x + w + 15, y + h, r, g, b, 255, 0.0f, 0.5f, 0);
    }
    void LineChart::Draw() const {
        Name->Draw();
        Unit_x->Draw();
        Unit_y->Draw();
        al_draw_line(Pos.x, Pos.y, Pos.x, Pos.y + Size.y, Color, 3.0f);
        al_draw_line(Pos.x, Pos.y + Size.y, Pos.x + Size.x, Pos.y + Size.y, Color, 3.0f);
        if (total_x != 0) {
            float highestY = Pos.y + Size.y * 0.1f;
            float lowestY = Pos.y + Size.y * 0.9f;
            float offset = Size.x * 0.8f / (total_x - 1);
            float diff = Size.y * 0.8f;
            float prevX = Pos.x;
            float prevY = Pos.y;
            float nowX = prevX + Size.x * 0.1f;
            float nowY = Pos.y + Size.y * 0.9 - (XY[0] - min_y) / (max_y - min_y) * diff;
            for (int i = 1; i < total_x ; i++) {
                if (nowY < highestY) {
                    highestY = nowY;
                }
                prevX = nowX;
                prevY = nowY;
                nowX += offset;
                nowY = Pos.y + Size.y * 0.9 - (XY[i] - min_y) / (max_y - min_y) * diff;
                al_draw_line(
                    prevX,
                    prevY,
                    nowX,
                    nowY,
                    Color,
                    2.0f
                );
            }
            al_draw_line(
                Pos.x - 5.0f,
                highestY,
                Pos.x + 5.0f,
                highestY,
                Color,
                3.0f
            );
            highest->Draw();
            al_draw_line(
                Pos.x - 5.0f,
                lowestY,
                Pos.x + 5.0f,
                lowestY,
                Color,
                3.0f
            );
            lowest->Draw();
        }
    }
}