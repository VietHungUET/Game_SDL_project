#include<iostream>
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "SDL_ttf_function.h"
#include "SDL_utils.h"
#include "SDL_mixer_function.h"
#include "Bullet.h"
#include "Threat.h"
#include "Collision.h"
#include "MainObject.h"
#include <fstream>
#include <ctime>
using namespace std;


int Number_health=5;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE="UNDEATH";
const int FPS=60;
const int DELAY_TIME=1000/FPS;

SDL_Rect play_rect= {1000,540,200,70};
SDL_Rect time_rect= {1100,20,50,30};
SDL_Rect scrore_rect= {1100,80,50,30};
SDL_Rect result_rect= {300,80,600,100};
SDL_Rect sound_rect_on= {20,510,80,70};
SDL_Rect sound_rect_off= {20,510,80,70};
SDL_Rect explosion;
SDL_Rect backgroundrect= {0,0,1200,600};
SDL_Rect backgroundrect1= {1195,0,1200,600};
SDL_Rect playagain_rect= {550,280,150,70};
SDL_Rect quit_rect= {550,380,150,70};
SDL_Rect help_button_rect= {1150,0,30,30};
SDL_Rect help_rect= {100,50,1000,450};
SDL_Rect high_score_rect= {550,200,150,50};

int main( int argc, char*argv[])
{
    srand((unsigned int )time(NULL));

    SDL_Window*window;
    SDL_Renderer* renderer;
    SDL_Event e;
    initSDL(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Texture*background=loadTexture("bggg.jpg",renderer);
    SDL_Texture*background_play=loadTexture("Reference-Image.png", renderer);
    SDL_Texture*menu=loadTexture("artistic-red-forest-23-1920x1200.jpg",renderer);
    SDL_Texture*exp_image=loadTexture("exp-removebg-preview.png",renderer);

    SDL_Texture*playbutton=loadTexture("playbutton.png",renderer);
    SDL_Texture*helpbutton=loadTexture("information-button-removebg-preview.png",renderer);
    SDL_Texture*help=loadTexture("help-removebg-preview.png",renderer);
    SDL_Texture*soundbutton_on=loadTexture("turn_onmusic.jpg",renderer);
    SDL_Texture*soundbutton_off=loadTexture("turn_offmusic.jpg",renderer);

    SDL_Texture*play_agian_button_up=loadTexture("quiit_on-removebg-preview.png",renderer);
    SDL_Texture*play_agian_button_down=loadTexture("quitit_off-removebg-preview.png",renderer);

    SDL_Texture*quit_button_up=loadTexture("5-removebg-preview (1).png",renderer);
    SDL_Texture*quit_button_down=loadTexture("52-removebg-preview.png",renderer);

    if (!LoadMusic())
        cout << "Failed to load music!" << endl;
    Mix_VolumeChunk(click_sound, 32);
    Mix_VolumeMusic(30);
    Mix_PlayMusic(background_music,-1);

    NhanVat nhanvat;
    nhanvat.nhanvat_normal=loadTexture("3-removebg-preview.png",renderer);
    nhanvat.nhanvat_attack=loadTexture("4-removebg-preview.png",renderer);
    SDL_QueryTexture(nhanvat.nhanvat_normal,NULL,NULL,& nhanvatrect.w, & nhanvatrect.h);
    nhanvatrect= {50,50,nhanvatrect.w,nhanvatrect.h};

    Bullet bullet;
    bullet.image=loadTexture("fire.png", renderer);


    Threat threat;
    threat.image=loadTexture("bat.jpg",renderer);
    setclip_threat();
    vector<Threat> threats;
    for(int i=0; i<Number_Threat ; i++)
    {
        threats.push_back(threat);
    }

    Health health;
    health.image=loadTexture("heart.png",renderer);
    vector<Health> healths;
    for(int i=0; i<Number_health; i++)
    {
        healths.push_back(health);
        health.health_rect.x+=50;
    }

    SDL_RenderCopy(renderer,background,NULL,NULL);
    SDL_RenderCopy(renderer,soundbutton_on,NULL,&sound_rect_on);
    SDL_RenderCopy(renderer,helpbutton,NULL,&help_button_rect);
    SDL_RenderCopy(renderer,playbutton,NULL,& play_rect);
    SDL_RenderPresent(renderer);
    bool turn_music=true;
    bool turn_help=false;
    bool quit= false;
    bool isRunning=true;
    Uint32 startime=0;
    stringstream timeText;

    Uint32 score=0;
    Uint32 high_score=0;
    stringstream Score;
    stringstream H_Score;
    int check_score=0;

    Uint32 frameStart;
    Uint32 frameTime;



    while(!quit)
    {

        if (SDL_PollEvent(&e) == 0)
            continue;
        if(e.type==SDL_QUIT)
        {
            isRunning=false;
            quit=true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN )
        {
            bool playBut = (e.button.x <=play_rect.x+play_rect.w) && (e.button.x >= play_rect.x) && (e.button.y <=play_rect.y+play_rect.h) && (e.button.y >= play_rect.y) ;
            if(playBut)
            {
                Mix_PlayChannel(-1,click_sound,0);
                SDL_Texture*playbutton=loadTexture("playbuttondown.png",renderer);
                SDL_RenderCopy(renderer,playbutton,NULL, &play_rect);
                SDL_RenderPresent(renderer);
                SDL_Delay(12);
                quit=true;
            }
            bool soundBut=(e.button.x <= 120) && (e.button.x >= 10) && (e.button.y <= 580) && (e.button.y >= 500);
            if(soundBut && turn_music==1)
            {
                Mix_PlayChannel(-1,click_sound,0);
                Mix_PauseMusic();
                Mix_Pause(-1);
                SDL_RenderCopy(renderer,soundbutton_off,NULL,&sound_rect_off);
                SDL_RenderPresent(renderer);
                turn_music=0;
            }
            else if(soundBut && turn_music==0)
            {
                Mix_PlayChannel(-1,click_sound,0);
                Mix_ResumeMusic();//tiếp tục nhạc
                Mix_Resume(-1);// tiếp tục sound effect
                SDL_RenderCopy(renderer,soundbutton_on,NULL,&sound_rect_on);
                SDL_RenderPresent(renderer);
                turn_music=1;

            }
            bool helpBut=(e.button.x<=help_button_rect.x+help_button_rect.w)&&(e.button.x>=help_button_rect.x)&&(e.button.y<=help_button_rect.y+help_button_rect.h)&&(e.button.y>=help_button_rect.y);
            if(helpBut&& turn_help==0)
            {
                Mix_PlayChannel(-1,click_sound,0);
                SDL_RenderCopy(renderer,help,NULL,&help_rect);
                SDL_RenderPresent(renderer);
                turn_help=1;
            }
            else if(helpBut&& turn_help==1)
            {
                Mix_PlayChannel(-1,click_sound,0);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,background,NULL,NULL);
                SDL_RenderCopy(renderer,helpbutton,NULL,&help_button_rect);
                SDL_RenderCopy(renderer,playbutton,NULL,& play_rect);
                if(turn_music==1)
                {
                    SDL_RenderCopy(renderer,soundbutton_on,NULL,&sound_rect_on);
                }
                else if(turn_music==0)
                {
                    SDL_RenderCopy(renderer,soundbutton_off,NULL,&sound_rect_off);
                }
                SDL_RenderPresent(renderer);
                turn_help=0;
            }
        }

    }


    Mix_HaltMusic();
    SDL_RenderCopy(renderer,background_play,NULL,&backgroundrect);


    while(isRunning)
    {
        if(turn_music==1)
        {
            Mix_PlayMusic(play_music,-1);
        }
        startime=SDL_GetTicks();
        score=0;
        unsigned int pos=4;
        quit=false;
        while(!quit)
        {
            frameStart=SDL_GetTicks();
            frameTime=SDL_GetTicks()-frameStart;
            if(frameTime<DELAY_TIME)
            {
                SDL_Delay(DELAY_TIME-frameTime);
            }
            SDL_RenderClear(renderer);
            backgroundrect.x-=2;
            backgroundrect1.x-=2;
            SDL_RenderCopy(renderer,background_play,NULL,&backgroundrect);
            SDL_RenderCopy(renderer,background_play,NULL,&backgroundrect1);
            if(backgroundrect.x <= -SCREEN_WIDTH)
            {
                backgroundrect.x=0;
                backgroundrect1.x=SCREEN_WIDTH;
            }

            timeText.str("");
            timeText<<"Time:"<<(SDL_GetTicks() -startime)/1000;
            LoadFont(timeText.str().c_str(),renderer,time_rect);
            Score.str("");
            Score<<"Score:"<<score;
            LoadFont(Score.str().c_str(),renderer,scrore_rect);
            if(check_score>=1)
            {
                threats.push_back(threat);
                check_score=0;
            }
            for( int i=0; i<int(healths.size()); i++)
            {
                healths[i].draw(renderer);
            }
            nhanvat.render(renderer);

            for( int i=0; i< int(threats.size()); i++)
            {

                threats[i].draw(renderer);
                threats[i].move_threat();
                bool is_col= CheckCollision(threats[i],nhanvatrect);
                if(is_col)
                {
                    check_score++;
                    Mix_PlayChannel(-1,nhanvat_sound,0);
                    if(healths.size()>=1)
                    {
                        healths.erase(healths.begin()+pos);
                        pos--;
                    }
                    if(healths.empty())
                        quit=true;

                    for(int i=0; i<int(healths.size()); i++)
                    {
                        healths[i].draw(renderer);
                    }
                    threats.erase(threats.begin()+i);
                }
            }
            SDL_RenderPresent(renderer);

            while ( SDL_PollEvent(&e) != 0)
            {
                nhanvat.handleEvent(e);
                if(e.type==SDL_MOUSEBUTTONDOWN )
                {
                    Mix_PlayChannel(-1,bullet_sound,0);
                    bullet.reset(nhanvatrect);
                    nhanvat.render_attack(renderer);
                    for(int i=0; i<int(healths.size()); i++)
                    {
                        healths[i].draw(renderer);

                    }
                    while(bullet.is_move(0,SCREEN_WIDTH,50))
                    {
                        if(frameTime<DELAY_TIME)
                        {
                            SDL_Delay(DELAY_TIME-frameTime);
                        }

                        SDL_RenderClear(renderer);
                        backgroundrect.x-=2;
                        backgroundrect1.x-=2;
                        if(backgroundrect.x <= -SCREEN_WIDTH)
                        {
                            backgroundrect.x=0;
                            backgroundrect1.x=SCREEN_WIDTH;
                        }
                        SDL_RenderCopy(renderer,background_play,NULL,&backgroundrect);
                        SDL_RenderCopy(renderer,background_play,NULL,&backgroundrect1);
                        LoadFont(timeText.str().c_str(),renderer,time_rect);
                        LoadFont(Score.str().c_str(),renderer,scrore_rect);
                        nhanvat.render_attack(renderer);
                        for(int i=0; i<int(healths.size()); i++)
                        {
                            healths[i].draw(renderer);

                        }

                        for(int i=0; i< int(threats.size()); i++)
                        {

                            threats[i].draw(renderer);
                            threats[i].move_threat();
                            bullet.draw(renderer);
                            bullet.mover();
                            bool is_col= CheckCollision(threats[i],nhanvatrect);
                            if(is_col)
                            {
                                check_score++;
                                Mix_PlayChannel(-1,nhanvat_sound,0);
                                if(healths.size()>=1)
                                {
                                    healths.erase(healths.begin()+pos);
                                    pos--;
                                }
                                if(healths.empty())
                                    quit=true;

                                for(int i=0; i<int(healths.size()); i++)
                                {
                                    healths[i].draw(renderer);
                                }
                                threats.erase(threats.begin()+i);
                            }
                            bool is_col2= CheckCollision2(threats[i],bullet);
                            if(is_col2)
                            {
                                int x_pos=threats[i].threatrect.x;
                                int y_pos=threats[i].threatrect.y;
                                Mix_PlayChannel(-1,exp_sound,0);
                                explosion= {x_pos-50,y_pos,200,100};
                                score++;
                                check_score++;
                                bullet_dispear=1;
                                SDL_RenderCopy(renderer,exp_image,NULL,&explosion);
                                threats.erase(threats.begin()+i);
                            }
                        }
                        SDL_RenderPresent(renderer);
                        if(bullet_dispear==1)
                        {
                            bullet_dispear=0;
                            break;
                        }
                    }
                }
            }
            nhanvat.move();
        }
        Mix_HaltMusic();
        SDL_RenderCopy(renderer,menu,NULL,NULL);
        SDL_RenderCopy(renderer,play_agian_button_up,NULL,&playagain_rect);
        SDL_RenderCopy(renderer,quit_button_up,NULL,&quit_rect);
        Score.str("");
        Score<<"Your score:"<<score;
        LoadFont(Score.str().c_str(),renderer,result_rect);

        ifstream input("BestScore.txt");
        if(! input.is_open())
        {
            cout<<"Unable to read";
        }
        input>> high_score;
        ofstream output("BestScore.txt");
        if(output.is_open())
        {
            if(score> high_score)
            {
                output<<score;

            }
            else
            {
                output<<high_score;
            }
            output.close();
        }
        H_Score.str("");
        H_Score<<"High score:"<<high_score;
        LoadFont(H_Score.str().c_str(),renderer,high_score_rect);
        SDL_RenderPresent(renderer);
        Mix_PlayMusic(result_music,-1);
        quit=false;
        while(!quit)
        {

            if (SDL_PollEvent(&e) == 0)
                continue;
            if(e.type== SDL_QUIT)
            {
                isRunning=false;
                quit=true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN )
            {
                bool play_againBut = (e.button.x >= playagain_rect.x) && (e.button.x <= playagain_rect.x+playagain_rect.w) && (e.button.y >= playagain_rect.y) && (e.button.y <= playagain_rect.y+playagain_rect.h);
                if(play_againBut)
                {
                    Mix_PlayChannel(-1,click_sound,0);
                    SDL_RenderCopy(renderer,play_agian_button_down,NULL,&playagain_rect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(10);
                    nhanvatrect.x=50;
                    nhanvatrect.y=50;
                    health.rest();
                    threats.clear();

                    for(int i=0; i<Number_health; i++)
                    {
                        healths.push_back(health);
                        health.health_rect.x+=50;
                    }
                    for(int i=0; i<Number_Threat; i++)
                    {
                        threats.push_back(threat);
                    }
                    break;
                }

                bool quitBut = (e.button.x <= quit_rect.x+quit_rect.w) && (e.button.x >= quit_rect.x) && (e.button.y <= quit_rect.y+quit_rect.h) && (e.button.y >= quit_rect.y);
                if(quitBut)
                {
                    Mix_PlayChannel(-1,click_sound,0);
                    SDL_RenderCopy(renderer,quit_button_down,NULL,&quit_rect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(10);
                    isRunning=false;
                    quit=true;
                }
            }
        }
    }

    quitSDL(window,renderer);
    return 0;


}
