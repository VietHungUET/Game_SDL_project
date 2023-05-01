#ifndef SDL_TTF_FUNCTION_H
#define SDL_TTF_FUNCTION_H
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

void LoadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect);
void CloseFont();
#endif // !SDL_TTF_FUNCTION_H
