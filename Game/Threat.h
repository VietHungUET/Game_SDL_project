#ifndef THREAT_H
#define THREAT_H

#include <iostream>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;
const int Number_Threat=15;
const int FLYING_ANIMATION_FRAMES =15;
SDL_Rect threatClips[ FLYING_ANIMATION_FRAMES];

struct Threat
{
    SDL_Texture*image;
    int x=1100;
    int y=900;
    int frame=0;
    void move_threat()
    {
        x-=10;
        if(x<-150)
        {
            int rand_y=rand()%700;
            x=1100+rand_y;
            y=500* (rand_y)/100;
            if(y<620 && y>550) {y=y-200;}
        }

    }
    SDL_Rect threatrect;

    void draw(SDL_Renderer* renderer)
    {
        SDL_Rect* clip=& threatClips[frame/15];
        ++frame;
        if( frame / 15 >= FLYING_ANIMATION_FRAMES )
        {
            frame = 0;
        }
        SDL_QueryTexture(image,NULL,NULL,& threatrect.w,& threatrect.h);
        threatrect.x=x;
        threatrect.y=y;
        threatrect.w=threatrect.w/9;
        threatrect.h=threatrect.h;
        SDL_RenderCopy(renderer,image,clip,&threatrect);

    }
    void reset()
    {
        int rand_y=rand()%300;
        x=1200+rand_y*2;
        y=600* (rand_y)/100;
    }
};
void setclip_threat()
{
    int threatClipsCount=80;
    threatClips[0].x=0;
    threatClips[0].y=0;
    threatClips[0].w=threatClipsCount;
    threatClips[0].h=80;
    for(int i=1; i<=14; i++)
    {
        threatClips[i].x =threatClips[i-1].x+threatClipsCount;
        threatClips[i].y = 0;
        threatClips[i].w =threatClipsCount;
        threatClips[i].h = 80;
        threatClipsCount=80;
    }
}

#endif
