#include "LightShadow.hpp"
#include <algorithm>

namespace Engine {
    LightShadow::LightShadow()
    : lightPos(0.0f, 10.0f, 0.0f),
      lightColor(1.0f, 1.0f, 0.8f),
      ambientLight(0.2f, 0.2f, 0.2f),
      roomMin(-1.0f, -1.0f, -1.0f),
      roomMax(1.0f, 1.0f, 1.0f){}

    void LightShadow::setLightPosition(const Eigen::Vector3f& pos) {
        lightPos = pos;
    }
    void LightShadow::setLightColor(const Eigen::Vector3f& color) {
        lightColor = color;
    }
    void LightShadow::setAmbientLight(const Eigen::Vector3f& ambient) {
        ambientLight = ambient;
    }
    void LightShadow::setRoomBounds(const Eigen::Vector3f& minBound, const Eigen::Vector3f& maxBound) {
        roomMin = minBound;
        roomMax = maxBound;
    }

    Eigen::Vector3f LightShadow::computeLighting(
    const Eigen::Vector3f& point,
    const Eigen::Vector3f& normal,
    const Eigen::Vector3f& baseColor
    ) const {
        Eigen::Vector3f lightDir = (lightPos - point).normalized();
        float diff = std::max(normal.dot(lightDir), 0.0f);

        Eigen::Vector3f diffuse = diff * lightColor;
        Eigen::Vector3f ambient = ambientLight;
        Eigen::Vector3f finalColor = baseColor.cwiseProduct(diffuse + ambient);

        return finalColor.cwiseMin(1.0f); // Clamp to 1.0
    }
    Eigen::Vector3f LightShadow::projectShadow(const Eigen::Vector3f& vertex) const {
        Eigen::Vector3f dir = (vertex - lightPos).normalized();
        float closestT = std::numeric_limits<float>::infinity();
        Eigen::Vector3f bestHit = vertex;

        for (int axis = 0; axis < 3; ++axis) {
            if (dir[axis] == 0.0f) continue;

            for (float bound : { roomMin[axis], roomMax[axis] }) {
                float t = (bound - lightPos[axis]) / dir[axis];
                if (t <= 0) continue;  // intersection behind light

                Eigen::Vector3f intersect = lightPos + t * dir;

                // Check if intersect is within room bounds on other two axes
                bool inside = true;
                for (int other = 0; other < 3; ++other) {
                    if (other == axis) continue;
                    if (intersect[other] < roomMin[other] - 1e-3f || intersect[other] > roomMax[other] + 1e-3f) {
                        inside = false;
                        break;
                    }
                }

                if (inside && t < closestT) {
                    closestT = t;
                    bestHit = intersect;
                }
            }
        }

        return bestHit;
    }
}
