#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "Commun.h"
#include "Editeur.h"
#include "Jeu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL,*logo = NULL,*textelogo = NULL;
    SDL_Rect pos,postexte;
    SDL_Event event;
    int mainloop = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Mario Sokoban",NULL);
    SDL_WM_SetIcon(IMG_Load("joy_ico.png"),NULL);
    ecran = SDL_SetVideoMode(W_PLAT,H_PLAT,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    logo = IMG_Load("10109.gif");
    textelogo = IMG_Load("texte.PNG");

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

    pos.x = ecran->w/2 - logo->w/2;
    pos.y = ecran->h/2 - logo->h/2;
    postexte.x = ecran->w/2 - textelogo->w/2;
    postexte.y = ecran->h/8*6;
    SDL_BlitSurface(logo,NULL,ecran,&pos);
    SDL_BlitSurface(textelogo,NULL,ecran,&postexte);
    SDL_Flip(ecran);

    while(mainloop)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                mainloop = 0;
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN :
                        mainloop = 0;
                        break;
                }
                break;
        }
    }

    mainloop = 1;
    pos.x = 0;
    pos.y = 0;
    logo = IMG_Load("menu.jpg");

    while(mainloop)
    {
        SDL_BlitSurface(logo,NULL,ecran,&pos);
        SDL_Flip(ecran);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                mainloop = 0;
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP1 :
                        jouer(ecran);
                        break;
                    case SDLK_KP2 :
                        editer();
                        break;
                    case SDLK_ESCAPE :
                        return EXIT_SUCCESS;
                        break;
                }
            break;
        }
    }

    SDL_FreeSurface(logo);
    SDL_FreeSurface(textelogo);
    SDL_Quit();

    return EXIT_SUCCESS;
}

