#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "PlaneEnemy.hpp"

PlaneEnemy::PlaneEnemy(int x, int y)
    : Enemy("play/enemy-2.png", x, y, 20, 20, 100, 50) {
}
