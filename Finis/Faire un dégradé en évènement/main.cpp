#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    int continuer = 1, i = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640,640,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_WM_SetCaption("Dégradé Event",NULL);
    SDL_EnableKeyRepeat(10,10);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
            {
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                        continuer = 0;
                        break;
                    case SDLK_UP :
                        if (i<254)
                        {
                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,i,i,i));
                            i++;
                        }
                        else
                            {
                                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
                            }
                        break;
                    case SDLK_DOWN :
                        if (i>1)
                        {
                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,i,i,i));
                            i--;
                        }
                        else
                            {
                                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            }
                        break;
                }
            break;
            }
        SDL_Flip(ecran);
    }

    SDL_Quit();

    EXIT_SUCCESS;

}
