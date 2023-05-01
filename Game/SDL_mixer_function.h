#ifndef SDL_MIXER_FUNCTION_H
#define SDL_MIXER_FUNCTION_H
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

extern Mix_Music* background_music;
extern Mix_Music* play_music;
extern Mix_Music* result_music;
extern Mix_Chunk* selected_sound;
extern Mix_Chunk* click_sound;
extern Mix_Chunk* bullet_sound;
extern Mix_Chunk* exp_sound;
extern Mix_Chunk* nhanvat_sound;
bool LoadMusic();
void CloseMusic();

#endif

