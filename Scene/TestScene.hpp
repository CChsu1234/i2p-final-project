#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/MouseKeyboard.hpp"

namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}   // namespace Engine

class TestScene final : public Engine::IScene {
private:
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;

protected:
    int lives;
    int money;
    int SpeedMult;

public:
    static bool DebugMode;
    static const float DangerTime;
    int MapId;
    float ticks;
    float deathCountDown;
    // Map tiles.
    Group *TileMapGroup;
    Group *GroundEffectGroup;
    Group *DebugIndicatorGroup;
    Group *BulletGroup;
    Group *TowerGroup;
    Group *EnemyGroup;
    Group *EffectGroup;
    Group *UIGroup;
    Engine::Label *UIMoney;
    Engine::Label *UILives;
    Engine::Image *imgTarget;
    Engine::Sprite *dangerIndicator;
    Engine::MouseKeyboard *Controller;
    std::list<std::pair<int, float>> enemyWaveData;
    explicit TestScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Hit();
    int GetMoney() const;
    void EarnMoney(int money);
    void ReadEnemyWave();
    void ConstructUI();
    void UIBtnClicked(int id);
    // void ModifyReadMapTiles();
};
#endif   // PLAYSCENE_HPP
