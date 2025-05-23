#include "Turret/Shovel.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"

const int Shovel::Price = 0;
Shovel::Shovel(float x, float y)
    : Turret("play/tool-base.png", "play/shovel.png", x, y, 200, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
