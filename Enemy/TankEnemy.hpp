#ifndef TANKENEMY_HPP
#define TANKENEMY_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class TankEnemy : public Enemy {
private:
    float targetRotation;
    Sprite head;

public:
    TankEnemy(int x, int y);
    void Draw() const override;
    void Update(float deltaTime) override;
};
#endif   // TANKENEMY_HPP
