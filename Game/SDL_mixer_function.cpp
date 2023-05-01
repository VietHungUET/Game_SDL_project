#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_mixer_function.h"

using namespace std;

Mix_Music* background_music = NULL;
Mix_Music* play_music=NULL;
Mix_Music* result_music=NULL;
Mix_Chunk* selected_sound = NULL;
Mix_Chunk* click_sound = NULL;
Mix_Chunk* bullet_sound = NULL;
Mix_Chunk* exp_sound=NULL;
Mix_Chunk* nhanvat_sound=NULL;
bool LoadMusic()
{
	bool success = true;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cerr << "Error:" << Mix_GetError() << endl;
		success = false;
	}
	background_music = Mix_LoadMUS("mysterious-celesta-114064.mp3");
	if (background_music == NULL)
	{
		cerr << "Failed to load background music! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
    click_sound = Mix_LoadWAV("audio_clickSound.wav");
	if (click_sound == NULL)
	{
		cerr << "Failed to load click sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
    play_music=Mix_LoadMUS("happy-comedy-halloween-party-dance-for-kids-children-118581.mp3");
    if(play_music==NULL)
    {
        cerr << "Failed to load play music sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
    }
    result_music=Mix_LoadMUS("horrible-22149.mp3");
    if(result_music==NULL)
    {
        cerr << "Failed to load result music sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
    }
	exp_sound = Mix_LoadWAV("Explosion+1.wav");
	if (exp_sound == NULL)
	{
		cerr << "Failed to load exp sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	bullet_sound = Mix_LoadWAV("throwknife2.wav");
	if (bullet_sound == NULL)
	{
		cerr << "Failed to load bullet sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	nhanvat_sound= Mix_LoadWAV("ough-47202.wav");
	if (nhanvat_sound == NULL)
	{
		cerr << "Failed to load nhanvat sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	return success;
}
void CloseMusic()
{
	Mix_FreeChunk(bullet_sound);
	Mix_FreeChunk(click_sound);
	Mix_FreeChunk(selected_sound);
	Mix_FreeChunk(exp_sound);

	exp_sound = NULL;
	click_sound = NULL;
	selected_sound = NULL;
	bullet_sound=NULL;
	Mix_FreeMusic(background_music);
	Mix_FreeMusic(play_music);
	Mix_FreeMusic(result_music);
	background_music = NULL;
	play_music=NULL;
	result_music=NULL;
	Mix_Quit();
}
