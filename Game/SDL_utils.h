#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <bits/stdc++.h>
#include <SDL.h>
#include<SDL_image.h>



void logSDLError(std::ostream& os,
	const std::string& msg, bool fatal = false);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer,
	int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();
SDL_Texture*loadTexture(std::string path,SDL_Renderer * renderer);

#endif
