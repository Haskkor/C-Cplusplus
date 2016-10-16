#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();

int main ( int argc, char** argv )
{
    int i = 0 ;
    SDL_Surface *ecran = NULL, *lignePixel[256] = {NULL};
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect position;
    ecran = SDL_SetVideoMode(640, 256, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Dégradé n&b", NULL);
    for (i=0;i<=255;i++)
        lignePixel[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,640,1,32,0,0,0,0);
    for (i=0;i<=255;i++)
    {
        SDL_FillRect(lignePixel[i], NULL, SDL_MapRGB(ecran->format, i, i, i));
        position.x = 0;
        position.y = i;
        SDL_BlitSurface(lignePixel[i], NULL, ecran, &position);
    }
    SDL_Flip(ecran);
    pause();
    for (i=0;i<=255;i++)
    {
        SDL_FreeSurface(lignePixel[i]);
    }
    SDL_Quit();

    return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}






