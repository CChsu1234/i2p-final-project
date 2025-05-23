#include <cstdio>

#include "Settings.hpp"
#include "fstream"

Settings::Settings(void) {

    std::ifstream in;

    in.open("Resource/settings.txt");

    int temp_bgm;
    int temp_sfx;

    in >> temp_bgm >> temp_sfx;

    in.close();

    bgm_volume = temp_bgm * 0.01;
    if (bgm_volume > 1.0) {
        bgm_volume = 1.0;
    }
    if (bgm_volume < 0) {
        bgm_volume = 0;
    }
    sfx_volume = temp_sfx * 0.01;
    if (sfx_volume > 1.0) {
        sfx_volume = 1.0;
    }
    if (sfx_volume < 0) {
        sfx_volume = 0;
    }

    AudioHelper::BGMVolume = bgm_volume;
    AudioHelper::SFXVolume = sfx_volume;
}
void Settings::Save(void) {

    std::ofstream out;

    out.open("Resource/settings.txt");
    
    bgm_volume = AudioHelper::BGMVolume;
    sfx_volume = AudioHelper::SFXVolume;
    int temp_bgm = bgm_volume * 100;
    int temp_sfx = sfx_volume * 100;

    out << temp_bgm << '\n' << temp_sfx << '\n';

    out.close();
}
