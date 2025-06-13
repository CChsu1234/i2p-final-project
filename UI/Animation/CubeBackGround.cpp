#include "CubeBackGround.hpp"

namespace Engine {
    CubeBackGround::CubeBackGround() {
        for (int i = 0; i<15;i++){
            unsigned char r = rand() % 256;
            unsigned char g = rand() % 256;
            unsigned char b = rand() % 256;
            ALLEGRO_COLOR decideColor = al_map_rgba(r, g, b, 225);
            double posX = -100.0f + 200.0f *((double)rand() / RAND_MAX);
            double posY = -50.0f + 100.0f *((double)rand() / RAND_MAX);
            cubeLifeTime[i] = rand() % 5;
            cube[i] = new Engine::RotatingCube(Eigen::Vector3f(posX, posY, -30), 3.0f, decideColor);
        }
    }
    void CubeBackGround::Transform() {
        for (int i = 0; i < 15; i++) {
            cube[i]->Transform();
        }
    }
    void CubeBackGround::Draw() const {
        for (int i = 0; i < 15; i++) {
            cube[i]->Draw();
        }
    }
    void CubeBackGround::Update(float deltaTime) {
        
        timeAccumulator += deltaTime;
        if (timeAccumulator >= 5.0f) {
            timeAccumulator -= 5.0f;
            for (int i = 0; i<15;i++) change[i] = false;
        }
            

        for (int i = 0; i < 15;i++){
            if (timeAccumulator>= cubeLifeTime[i] && change[i] == false){
                double posX = -100.0f + 200.0f *((double)rand() / RAND_MAX);
                double posY = -50.0f + 100.0f *((double)rand() / RAND_MAX);
                unsigned char r = rand() % 256;
                unsigned char g = rand() % 256;
                unsigned char b = rand() % 256;
                ALLEGRO_COLOR decideColor = al_map_rgba(r, g, b, 225);
                cube[i]->updateDraw(decideColor, Eigen::Vector3f(posX, posY, -30));
                change[i] = true;
            }
        }
    }
}