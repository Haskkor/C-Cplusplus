#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "SP.h"

int main ( int argc, char** argv )
{
    int continuer = 1,boolSouris = 0,boolShoot = 1,cptShoot = 0,cptHit = 0,timNow = 0,timBfr = 0,cptTim = 30,gameOver = 0,mainloop = 1;
    char tabTime[20] = "",tabScore[20] = "";
    Uint32 timSouris = 0, dif = 0;

    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Jeu de tir",NULL);
    SDL_WM_SetIcon(IMG_Load("joy_ico.png"),NULL);

    TTF_Font *police = NULL, *fontScoTim = NULL;
    police = TTF_OpenFont("ka.ttf", 180);
    fontScoTim = TTF_OpenFont("ka.ttf",15);
    SDL_Color couleurBlanche = {255,255,255};
    SDL_Event event;
    SDL_Rect posViseur,posCible,posScore,posTime;
    SDL_Surface *ecran = NULL, *viseur = NULL, *cible = NULL, *fond = NULL, *time = NULL, *score = NULL;
    ecran = SDL_SetVideoMode(800,800,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    viseur = IMG_Load("12606.png");
    fond = IMG_Load("paysage.jpg");

    FMOD_SYSTEM *system;
    FMOD_SOUND *tir = NULL;
    FMOD_SOUND *fondS = NULL;
    FMOD_SOUND *hit = NULL;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateSound(system, "gun-shot.wav", FMOD_CREATESAMPLE, 0, &tir);
    FMOD_System_CreateSound(system, "nature30s.wav", FMOD_CREATESAMPLE, 0, &fondS);
    FMOD_System_CreateSound(system, "brokenbottle.wav", FMOD_CREATESAMPLE, 0, &hit);

    while (mainloop == 1)
    {
        continuer = 1;
        menuJeu(ecran,system,&continuer,&mainloop);

        if(continuer == 1)
        {
            compteDepart(ecran,system);
            FMOD_System_PlaySound(system, 3,fondS,0,NULL);
        }

        cptShoot = 0;
        cptHit = 0;
        cptTim = 30;

        while(continuer == 1)
        {
            SDL_ShowCursor(SDL_DISABLE);
            SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
            if (boolShoot == 1)
            {
                switch (rand() % 4)
                {
                    case 0 :
                        cible = IMG_Load("mod_target32.png");
                        break;
                    case 1 :
                        cible = IMG_Load("mod_target48.png");
                        break;
                    case 2 :
                        cible = IMG_Load("mod_target128.png");
                        break;
                    case 3 :
                        cible = IMG_Load("mod_target256.png");
                        break;
                }
                posCible.x = (rand() % 800 - cible->w);
                posCible.y = (rand() % 800 - cible->h);
                boolShoot = 0;
            }
            SDL_PollEvent(&event);
            switch (event.type)
            {
                case SDL_QUIT :
                    continuer = 0;
                    break;
                case SDL_MOUSEMOTION :
                    posViseur.x = event.motion.x - viseur->w / 2;
                    posViseur.y = event.motion.y - viseur->h / 2;
                case SDL_MOUSEBUTTONDOWN :
                    boolSouris = 1;
                    break;
                case SDL_MOUSEBUTTONUP :
                    if (boolSouris == 1)
                    {
                        dif = SDL_GetTicks();
                        if (dif - timSouris > 120)
                        {
                            FMOD_System_PlaySound(system, 1,tir,0,NULL);
                            timSouris = SDL_GetTicks();
                        }
                        boolSouris = 0;
                        if (posViseur.x >= posCible.x && posViseur.x < posCible.x + cible->w && posViseur.y >= posCible.y && posViseur.y < posCible.y + cible->h)
                        {
                            cptHit++;
                            FMOD_System_PlaySound(system, 1,tir,0,NULL);
                            FMOD_System_PlaySound(system, 2,hit,0,NULL);
                            sprintf(tabScore, "Cibles Touchees %d",cptHit);
                            SDL_FreeSurface(score);
                            score = TTF_RenderText_Blended(fontScoTim,tabScore,couleurBlanche);
                            boolShoot = 1;
                        }
                        cptShoot++;
                    }
                    break;
            }
            if (cptTim == 30)
            {
                sprintf(tabTime, "Temps Restant %d",cptTim);
                SDL_FreeSurface(time);
                time = TTF_RenderText_Blended(fontScoTim,tabTime,couleurBlanche);
            }
            if (cptHit == 0)
            {
                sprintf(tabScore, "Cibles Touchees %d",cptHit);
                SDL_FreeSurface(score);
                score = TTF_RenderText_Blended(fontScoTim,tabScore,couleurBlanche);
            }
            if (timNow - timBfr >= 1000)
            {
                cptTim--;
                sprintf(tabTime, "Temps Restant %d",cptTim);
                SDL_FreeSurface(time);
                time = TTF_RenderText_Blended(fontScoTim,tabTime,couleurBlanche);
                timBfr = timNow;
            }
            if (cptTim == 0)
            {
                continuer = 0;
                gameOver = 1;

            }
            posTime.x = 600 - time->w / 2;
            posTime.y = 5;
            posScore.x = 200 - score->w / 2;
            posScore.y = 5;

            SDL_BlitSurface(fond,0,ecran,0);
            SDL_BlitSurface(time,0,ecran,&posTime);
            SDL_BlitSurface(score,0,ecran,&posScore);
            SDL_BlitSurface(cible,0,ecran,&posCible);
            SDL_BlitSurface(viseur,0,ecran,&posViseur);
            SDL_Flip(ecran);
            timNow = SDL_GetTicks();
        }

        if (gameOver == 1)
        {
            montrerResultats(ecran,cptHit,cptShoot,system);
            gameOver = 0;
        }
    }


    FMOD_Sound_Release(tir);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_FreeSurface(viseur);
    SDL_FreeSurface(cible);
    SDL_Quit();

    return EXIT_SUCCESS;
}



