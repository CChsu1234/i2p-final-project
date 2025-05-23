#ifndef TANKYENEMT_HPP
#define TANKYENEMT_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class TankyEnemy : public Enemy {
public:
    TankyEnemy(int x, int y);
    void Hit(float damage) override;
};
#endif   // TANKYENEMT_HPP
