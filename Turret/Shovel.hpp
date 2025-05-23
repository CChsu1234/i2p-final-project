#ifndef SHOVEL_HPP
#define SHOVEL_HPP
#include "Turret/Turret.hpp"

class Shovel : public Turret {
public:
    static const int Price;
    Shovel(float x, float y);
    virtual void CreateBullet() {}
};
#endif
