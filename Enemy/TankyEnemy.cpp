#include <allegro5/base.h>
#include <random>
#include <string>
#include <iostream>

#include "Engine/Point.hpp"
#include "TankyEnemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Turret/Turret.hpp"
#include "Bullet/Bullet.hpp"
#include "Scene/PlayScene.hpp"
#include "Enemy/SoldierEnemy.hpp"
#include "Enemy/TankEnemy.hpp"

TankyEnemy::TankyEnemy(int x, int y)
    : Enemy("play/enemy-4.png", x, y, 30, 20, 1000, 50) {
}
void TankyEnemy::Hit(float damage) {
    HitCountDown = 0.1;
    hp -= damage;
    if (hp <= 0) {
        OnExplode();
        // Remove all turret's reference to target.
        for (auto &it : lockedTurrets)
            it->Target = nullptr;
        for (auto &it : lockedBullets)
            it->Target = nullptr;
        int x = Position.x;
        int y = Position.y;
        getPlayScene()->EarnMoney(money);
        Enemy *spawn_enemy;
        for (int i = 0; i < 10; i++) {
            getPlayScene()->EnemyGroup->AddNewObject(spawn_enemy = new SoldierEnemy(x, y));
            // spawn_enemy->Update(i * 0.5);
            spawn_enemy->UpdatePath(getPlayScene()->mapDistance);
            // Compensate the time lost.
            spawn_enemy->Update((10 - i) * 0.5);
        }
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
