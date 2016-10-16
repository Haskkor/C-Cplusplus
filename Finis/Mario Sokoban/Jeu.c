#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "Commun.h"
#include "Jeu.h"

void jouer(SDL_Surface *ecran)
{
    int platJeu[12][12], reload = 0,tabPerso[4],i = 0,j = 0,parcours = 0,nbrObj = 0,xMario = 0,yMario = 0,nbrLvl = 0,lvlEnCours = 1,choixLvl = 0,attente = 1;
    FILE *fichier = NULL;
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *mario = NULL, *finNiveau = NULL;
    SDL_Rect position,posJoueur;
    SDL_Event event;
    SDL_EnableKeyRepeat(100, 100);

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    caisseOK = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    mario = IMG_Load("mario_bas.gif");
    finNiveau = IMG_Load("fin niveau.jpg");

    fichier = fopen("niveaux.txt","r");

    while (parcours != EOF)
    {
        parcours = fgetc(fichier);
        if (parcours == '\n')
            {
                nbrLvl++;
            }
    }

    while (lvlEnCours < nbrLvl)
    {
        choixLvl = lvlEnCours;
        rewind(fichier);
        while (choixLvl > 0)
        {
            parcours = fgetc(fichier);
            if (parcours == '\n')
                {
                        choixLvl--;
                }
        }
        parcours = 0;
        i = 0;
        j = 0;
        while (parcours != '\n')
        {
            parcours = fgetc(fichier);
            platJeu[i][j] = parcours;
            if (platJeu[i][j] == '3')
            {
                nbrObj++;
            }
            j++;
            if (j==12)
            {
                j = 0 ;
                i++;
            }
        }

        bliterPlateau(platJeu,position,&xMario,&yMario,ecran,mur,caisse,objectif,mario,caisseOK);
        posJoueur.x = xMario;
        posJoueur.y = yMario;

        SDL_Flip(ecran);

        while (nbrObj>0)
        {
            reload = 0;
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT :
                    SDL_Quit();
                    break;
                case SDL_KEYDOWN :
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP :
                            mario = IMG_Load("mario_haut.gif");
                            if(posJoueur.y - 34 < 0)
                            {
                                break;
                            }
                            if(platJeu[posJoueur.y/34-1][posJoueur.x/34] == '1')
                            {
                                break;
                            }
                            if(((platJeu[posJoueur.y/34-1][posJoueur.x/34] == '2') || (platJeu[posJoueur.y/34-1][posJoueur.x/34] == '5')) && ((platJeu[posJoueur.y/34-2][posJoueur.x/34] == '1') || (platJeu[posJoueur.y/34-2][posJoueur.x/34] == '2') || (platJeu[posJoueur.y/34-2][posJoueur.x/34] == '5') || (posJoueur.y - 68 < 0)))
                            {
                                break;
                            }
                            if ((platJeu[posJoueur.y/34-1][posJoueur.x/34] == '2') && (platJeu[posJoueur.y/34-2][posJoueur.x/34] == '3'))
                            {
                                platJeu[posJoueur.y/34-2][posJoueur.x/34] = '5';
                                platJeu[posJoueur.y/34-1][posJoueur.x/34] = '0';
                                nbrObj--;
                            }
                            if ((platJeu[posJoueur.y/34-1][posJoueur.x/34] == '5') && (platJeu[posJoueur.y/34-2][posJoueur.x/34] == '3'))
                            {
                                platJeu[posJoueur.y/34-2][posJoueur.x/34] = '5';
                                platJeu[posJoueur.y/34-1][posJoueur.x/34] = '3';
                            }
                            if ((platJeu[posJoueur.y/34-1][posJoueur.x/34] == '2') && (platJeu[posJoueur.y/34-2][posJoueur.x/34] == '0'))
                            {
                                platJeu[posJoueur.y/34-2][posJoueur.x/34] = '2';
                                platJeu[posJoueur.y/34-1][posJoueur.x/34] = '0';
                            }
                            if ((platJeu[posJoueur.y/34-1][posJoueur.x/34] == '5') && (platJeu[posJoueur.y/34-2][posJoueur.x/34] == '0'))
                            {
                                platJeu[posJoueur.y/34-2][posJoueur.x/34] = '2';
                                platJeu[posJoueur.y/34-1][posJoueur.x/34] = '3';
                                nbrObj++;
                            }
                            posJoueur.y = posJoueur.y - 34;
                            break;
                        case SDLK_DOWN :
                            mario = IMG_Load("mario_bas.gif");
                            if(posJoueur.y + 34 < 0)
                            {
                                break;
                            }
                            if(platJeu[posJoueur.y/34+1][posJoueur.x/34] == '1')
                            {
                                break;
                            }
                            if(((platJeu[posJoueur.y/34+1][posJoueur.x/34] == '2') || (platJeu[posJoueur.y/34+1][posJoueur.x/34] == '5')) && ((platJeu[posJoueur.y/34+2][posJoueur.x/34] == '1') || (platJeu[posJoueur.y/34+2][posJoueur.x/34] == '2') || (platJeu[posJoueur.y/34+2][posJoueur.x/34] == '5') || (posJoueur.y + 68 < 0)))
                            {
                                break;
                            }
                            if ((platJeu[posJoueur.y/34+1][posJoueur.x/34] == '2') && (platJeu[posJoueur.y/34+2][posJoueur.x/34] == '3'))
                            {
                                platJeu[posJoueur.y/34+2][posJoueur.x/34] = '5';
                                platJeu[posJoueur.y/34+1][posJoueur.x/34] = '0';
                                nbrObj--;
                            }
                            if ((platJeu[posJoueur.y/34+1][posJoueur.x/34] == '5') && (platJeu[posJoueur.y/34+2][posJoueur.x/34] == '3'))
                            {
                                platJeu[posJoueur.y/34+2][posJoueur.x/34] = '5';
                                platJeu[posJoueur.y/34+1][posJoueur.x/34] = '3';
                            }
                            if ((platJeu[posJoueur.y/34+1][posJoueur.x/34] == '2') && (platJeu[posJoueur.y/34+2][posJoueur.x/34] == '0'))
                            {
                                platJeu[posJoueur.y/34+2][posJoueur.x/34] = '2';
                                platJeu[posJoueur.y/34+1][posJoueur.x/34] = '0';
                            }
                            if ((platJeu[posJoueur.y/34+1][posJoueur.x/34] == '5') && (platJeu[posJoueur.y/34+2][posJoueur.x/34] == '0'))
                            {
                                platJeu[posJoueur.y/34+2][posJoueur.x/34] = '2';
                                platJeu[posJoueur.y/34+1][posJoueur.x/34] = '3';
                                nbrObj++;
                            }
                            posJoueur.y = posJoueur.y + 34;
                            break;
                        case SDLK_LEFT :
                            mario = IMG_Load("mario_gauche.gif");
                            if(posJoueur.x - 34 < 0)
                            {
                                break;
                            }
                            if(platJeu[posJoueur.y/34][posJoueur.x/34-1] == '1')
                            {
                                break;
                            }
                            if(((platJeu[posJoueur.y/34][posJoueur.x/34-1] == '2') || (platJeu[posJoueur.y/34][posJoueur.x/34-1] == '5')) && ((platJeu[posJoueur.y/34][posJoueur.x/34-2] == '1') || (platJeu[posJoueur.y/34][posJoueur.x/34-2] == '2') || (platJeu[posJoueur.y/34][posJoueur.x/34-2] == '5') || (posJoueur.x - 68 < 0)))
                            {
                                break;
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34-1] == '2') && (platJeu[posJoueur.y/34][posJoueur.x/34-2] == '3'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34-2] = '5';
                                platJeu[posJoueur.y/34][posJoueur.x/34-1] = '0';
                                nbrObj--;
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34-1] == '5') && (platJeu[posJoueur.y/34][posJoueur.x/34-2] == '3'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34-2] = '5';
                                platJeu[posJoueur.y/34][posJoueur.x/34-1] = '3';
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34-1] == '2') && (platJeu[posJoueur.y/34][posJoueur.x/34-2] == '0'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34-2] = '2';
                                platJeu[posJoueur.y/34][posJoueur.x/34-1] = '0';
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34-1] == '5') && (platJeu[posJoueur.y/34][posJoueur.x/34-2] == '0'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34-2] = '2';
                                platJeu[posJoueur.y/34][posJoueur.x/34-1] = '3';
                                nbrObj++;
                            }
                            posJoueur.x = posJoueur.x - 34;
                            break;
                        case SDLK_RIGHT :
                            mario = IMG_Load("mario_droite.gif");
                            if(posJoueur.x + 34 < 0)
                            {
                                break;
                            }
                            if(platJeu[posJoueur.y/34][posJoueur.x/34+1] == '1')
                            {
                                break;
                            }
                            if(((platJeu[posJoueur.y/34][posJoueur.x/34+1] == '2') || (platJeu[posJoueur.y/34][posJoueur.x/34+1] == '5')) && ((platJeu[posJoueur.y/34][posJoueur.x/34+2] == '1') || (platJeu[posJoueur.y/34][posJoueur.x/34+2] == '2') || (platJeu[posJoueur.y/34][posJoueur.x/34+2] == '5') || (posJoueur.x + 68 < 0)))
                            {
                                break;
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34+1] == '2') && (platJeu[posJoueur.y/34][posJoueur.x/34+2] == '3'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34+2] = '5';
                                platJeu[posJoueur.y/34][posJoueur.x/34+1] = '0';
                                nbrObj--;
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34+1] == '5') && (platJeu[posJoueur.y/34][posJoueur.x/34+2] == '3'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34+2] = '5';
                                platJeu[posJoueur.y/34][posJoueur.x/34+1] = '3';
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34+1] == '2') && (platJeu[posJoueur.y/34][posJoueur.x/34+2] == '0'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34+2] = '2';
                                platJeu[posJoueur.y/34][posJoueur.x/34+1] = '0';
                            }
                            if ((platJeu[posJoueur.y/34][posJoueur.x/34+1] == '5') && (platJeu[posJoueur.y/34][posJoueur.x/34+2] == '0'))
                            {
                                platJeu[posJoueur.y/34][posJoueur.x/34+2] = '2';
                                platJeu[posJoueur.y/34][posJoueur.x/34+1] = '3';
                                nbrObj++;
                            }
                            posJoueur.x = posJoueur.x + 34;
                            break;
                        case SDLK_ESCAPE :
                            return;
                        case SDLK_END :
                            nbrObj = 0;
                            break;
                        case SDLK_RCTRL :
                            nbrObj = 0;
                            reload = 1;
                            lvlEnCours--;
                            break;
                    }
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
                    bliterPlateau(platJeu,position,&xMario,&yMario,ecran,mur,caisse,objectif,mario,caisseOK);
                    SDL_BlitSurface(mario,NULL,ecran,&posJoueur);
                    SDL_Flip(ecran);
                    break;
            }
        }

        if (reload == 0)
        {
            SDL_BlitSurface(finNiveau,NULL,ecran,NULL);
            SDL_Flip(ecran);

            attente = 1;
            while (attente)
            {
                SDL_WaitEvent(&event);
                switch (event.type)
                {
                    case SDL_KEYDOWN :
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_RETURN :
                                attente = 0;
                                break;
                        }
                        break;
                }
            }
        }
        lvlEnCours++;
        reload = 0;
    }

    attente = 1;
    finNiveau = IMG_Load("fin jeu.jpg");
    while(attente)
    {
        SDL_BlitSurface(finNiveau,NULL,ecran,NULL);
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

    SDL_EnableKeyRepeat(0, 0);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);

    return;
}

void bliterPlateau(int platJeu[12][12],SDL_Rect position,int *xMario,int *yMario,SDL_Surface *ecran,SDL_Surface *mur,SDL_Surface *caisse,SDL_Surface *objectif,SDL_Surface *mario,SDL_Surface *caisseOK)
{
    int i = 0,j = 0;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
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
                    *xMario = position.x;
                    *yMario = position.y;
                    platJeu[i][j] = '0';
                    break;
                case '5' :
                    SDL_BlitSurface(caisseOK,NULL,ecran,&position);
                    break;
            }
        }
    }

}

