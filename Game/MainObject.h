#ifndef MAINOBJECT_H
#define MAINOBJECT_H
#include "SDL_utils.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
SDL_Rect nhanvatrect;

struct NhanVat
{   SDL_Texture*nhanvat_normal;
    SDL_Texture*nhanvat_attack;
    int v_nhanvatx=0,v_nhanvaty=0,step=6;

    void handleEvent(SDL_Event& e)
    {
        if (e.type == SDL_KEYDOWN )
        {

            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                break;
            case SDLK_LEFT:
                v_nhanvatx = (v_nhanvatx -step);
                if (v_nhanvatx <- step)
                    v_nhanvatx = -step;
                break;
            case SDLK_RIGHT:
                v_nhanvatx = (v_nhanvatx + step);
                if (v_nhanvatx > step)
                    v_nhanvatx = step;
                break;
            case SDLK_DOWN:
                v_nhanvaty = (v_nhanvaty + step);
                if (v_nhanvaty > step)
                    v_nhanvaty = step;
                break;
            case SDLK_UP:
                v_nhanvaty = (v_nhanvaty - step);
                if (v_nhanvaty <- step)
                    v_nhanvaty = -step;
                break;
            default:
                break;
            }
        }
        else if (e.type == SDL_KEYUP )
        {

            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                v_nhanvatx = (v_nhanvatx +step);
                break;
            case SDLK_RIGHT:
                v_nhanvatx = (v_nhanvatx - step);
                break;
            case SDLK_DOWN:
                v_nhanvaty = (v_nhanvaty - step);
                break;
            case SDLK_UP:
                v_nhanvaty = (v_nhanvaty + step);
                break;
            default:
                break;
            }
        }
    }
    void move()
    {
        nhanvatrect.x += v_nhanvatx;
        nhanvatrect.y += v_nhanvaty;
        if( ( nhanvatrect.y < 10 ) || ( nhanvatrect.y + nhanvatrect.h  > 600 ) )
        {

            nhanvatrect.y-= v_nhanvaty;
        }
        if( ( nhanvatrect.x < 0 ) || ( nhanvatrect.x + nhanvatrect.w  > 1200 ) )
        {

            nhanvatrect.x-= v_nhanvatx;
        }
    }
   void render(SDL_Renderer* renderer)
   {
       SDL_RenderCopy(renderer,nhanvat_normal,NULL,&nhanvatrect);
   }
   void render_attack(SDL_Renderer* renderer)
   {
       SDL_RenderCopy(renderer,nhanvat_attack,NULL,&nhanvatrect);
   }
};

struct Health
{
    int x=60,y=0,w=50,h=50;
    SDL_Rect health_rect= {x,y,w,h};
    SDL_Texture*image;
    void draw(SDL_Renderer*renderer)
    {
        SDL_RenderCopy(renderer,image,NULL,&health_rect);
    }
    void rest()
    {
        health_rect.x=60;
        health_rect.y=0;
        health_rect.w=50;
        health_rect.h=50;
    }
};
#endif
