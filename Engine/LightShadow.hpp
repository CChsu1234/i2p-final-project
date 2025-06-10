#ifndef LIGHTSHADOW_HPP
#define LIGHTSHADOW_HPP

#include <allegro5/allegro_color.h>
#include "Resource/Eigen/Dense"
#include "Engine/GameEngine.hpp"

namespace Engine {
    class LightShadow{
    public:
        LightShadow();
        void setLightPosition(const Eigen::Vector3f& pos);
        void setLightColor(const Eigen::Vector3f& color);
        void setAmbientLight(const Eigen::Vector3f& ambient);
        void setRoomBounds(const Eigen::Vector3f& minBound, const Eigen::Vector3f& maxBound);
        Eigen::Vector3f computeLighting(const Eigen::Vector3f& point, const Eigen::Vector3f& normal, const Eigen::Vector3f& baseColor) const;
        Eigen::Vector3f projectShadow(const Eigen::Vector3f& vertex) const;
        
        Eigen::Vector3f lightPos;
        Eigen::Vector3f lightColor;
        Eigen::Vector3f ambientLight;
        Eigen::Vector3f roomMin;
        Eigen::Vector3f roomMax;
    };
}
#endif