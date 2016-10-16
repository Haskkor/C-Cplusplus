#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "Commun.h"
#include "Editeur.h"

void editer()
{
    SDL_Surface *ecran = NULL,*mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *mario = NULL, *editeurAcc = NULL;
    ecran = SDL_SetVideoMode(W_PLAT,H_PLAT,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Event event;
    int attente = 1,choix = '1',platJeu[12][12], i = 0, j = 0;
    SDL_Rect posImg,position;
    FILE *fichier = NULL;
    SDL_ShowCursor(SDL_DISABLE);

    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    caisseOK = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    mario = IMG_Load("mario_bas.gif");
    editeurAcc = IMG_Load("Accueil éditeur.jpg");

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

    while(attente)
    {
        SDL_BlitSurface(editeurAcc,NULL,ecran,NULL);
        SDL_Flip(ecran);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN :
                        attente = 0;
                        break;
                }
                break;
        }
    }

    for(i=0;i<12;i++)
    {
        j = 0;
        for(j=0;j<12;j++)
        {
            platJeu[i][j] = '0';
        }
    }

    attente = 1;
    while(attente == 1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                        return;
                        break;
                    case SDLK_F5 :
                        fichier = fopen("niveaux.txt","a");
                        i = 0;
                        j = 0;
                        for(i=0;i<12;i++)
                        {
                            j = 0;
                            for(j=0;j<12;j++)
                            {
                                fprintf(fichier,"%c",platJeu[i][j]);
                            }
                        }
                        fprintf(fichier,"\n");
                        fclose(fichier);
                        break;
                    case SDLK_KP1 :
                        choix = '1';
                        break;
                    case SDLK_KP2 :
                        choix = '2';
                        break;
                    case SDLK_KP3 :
                        choix = '3';
                        break;
                    case SDLK_KP4 :
                        choix = '4';
                        break;
                    case SDLK_KP5 :
                        choix = '5';
                        break;
                }
                break;
            case SDL_MOUSEMOTION :
                posImg.x = event.motion.x;
                posImg.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONUP :
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    platJeu[(event.button.y+15)/34][(event.button.x+15)/34] = choix;
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    platJeu[(event.button.y+15)/34][(event.button.x+15)/34] = '0';
                }
                break;
        }

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

        i = 0;
        j = 0;
        switch(choix)
        {
            case '1' :
                SDL_BlitSurface(mur,NULL,ecran,&posImg);
                break;
            case '2' :
                SDL_BlitSurface(caisse,NULL,ecran,&posImg);
                break;
            case '3' :
                SDL_BlitSurface(objectif,NULL,ecran,&posImg);
                break;
            case '4' :
                SDL_BlitSurface(mario,NULL,ecran,&posImg);
                break;
            case '5' :
                SDL_BlitSurface(caisseOK,NULL,ecran,&posImg);
                break;
        }

        for (i=0;i<12;i++)
        {
            j = 0;
            for (j=0;j<12;j++)
            {
                position.x = j * 34;
                position.y = i * 34;
                switch (platJeu[i][j])
                {
                    case '1' :
                        SDL_BlitSurface(mur,NULL,ecran,&position);
                        break;
                    case '2' :
                        SDL_BlitSurface(caisse,NULL,ecran,&position);
                        break;
                    case '3' :
                        SDL_BlitSurface(objectif,NULL,ecran,&position);
                        break;
                    case '4' :
                        SDL_BlitSurface(mario,NULL,ecran,&position);
                        break;
                    case '5' :
                        SDL_BlitSurface(caisseOK,NULL,ecran,&position);
                        break;
                }
            }
        }
        SDL_Flip(ecran);
    }
}
