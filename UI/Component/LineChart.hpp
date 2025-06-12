#ifndef LINECHART_HPP
#define LINECHART_HPP

#include <vector>
#include <allegro5/allegro_color.h>
#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/Label.hpp"

namespace Engine {
    class LineChart : public IObject {
    private:
        std::vector<float> XY;
        int total_x;
        float max_y;
        float min_y;
        Point Pos;
        Point Size;
        ALLEGRO_COLOR Color;
        Label *Name;
        Label *Unit_x;
        Label *Unit_y;
        Label *highest;
        Label *lowest;

    public:
        LineChart(std::string name, float x, float y, float h, float w, std::vector<float> xy, std::string unit_x, std::string unit_y, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255);
        ~LineChart() = default;
        void Draw() const override;
    };
}

#endif