#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "SoldierEnemy.hpp"

// DONE HACKATHON-3 (1/3): You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
SoldierEnemy::SoldierEnemy(int x, int y)
    : Enemy("play/enemy-1.png", x, y, 20, 20, 100, 50) {
}
