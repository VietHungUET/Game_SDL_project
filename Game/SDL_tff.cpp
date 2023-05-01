#include<SDL.h>
#include<SDL_ttf.h>
#include"SDL_ttf_function.h"
using namespace std;
TTF_Font* Font = NULL;
SDL_Surface* textSurface = NULL;
SDL_Texture* StrTexture = NULL;

void LoadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect)
{
    if (TTF_Init() == -1)
    {
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
    }
    else
    {
        Font = TTF_OpenFont("Southern.ttf",20);
        SDL_Color textColor = {255,255,255,255};
        textSurface = TTF_RenderText_Solid(Font, Text, textColor);
        StrTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_RenderCopy(renderer, StrTexture, NULL, &Text_rect);
        //SDL_RenderPresent(renderer);
        SDL_FreeSurface(textSurface);
    }

}
void CloseFont()
{
    TTF_CloseFont(Font);
    Font = NULL;
    SDL_DestroyTexture(StrTexture);
    StrTexture = NULL;
    TTF_Quit();
}
