#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include "Engine/AudioHelper.hpp"

class Settings {
public:
    float bgm_volume;
    float sfx_volume;
    Settings(void);
    void Save(void);
};
#endif
