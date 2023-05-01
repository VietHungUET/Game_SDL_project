#ifndef BULLET_H
#define BULLET_H
#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

static int bullet_dispear=0;
struct Bullet
{
    int x;
    int y;
    SDL_Texture* image;
    void reset(const SDL_Rect& nhavatrect)
    {
        x=nhavatrect.x+nhavatrect.w;
        y=nhavatrect.y+nhavatrect.h*0.2;
    }
    void mover()
    {
        x+=3.5;
    }

    SDL_Rect bulletrect;
    void draw(SDL_Renderer* renderer)
    {
        SDL_QueryTexture(image,NULL,NULL,& bulletrect.w, & bulletrect.h);
        bulletrect.x= x;
        bulletrect.y= y;
        bulletrect.w =bulletrect.w/7;
        bulletrect.h=bulletrect.h/5;
        SDL_RenderCopy(renderer,image,NULL,&bulletrect);

    }

    bool is_move(int minx, int maxx,int _x)
    {
        return(minx <=x && x+_x<=maxx);
    }
};

#endif



