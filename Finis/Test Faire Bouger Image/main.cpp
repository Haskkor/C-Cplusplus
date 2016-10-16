#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL,*zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Test de mouvement image",NULL);

    zozor = SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format,0,0,255));

    positionZozor.x = (ecran->w /2) - (zozor->w /2);
    positionZozor.y = (ecran->h /2) - (zozor->h /2);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
    SDL_Flip(ecran);
    SDL_EnableKeyRepeat(10, 1);
    SDL_ShowCursor(SDL_DISABLE);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP :
                if (event.button.button == SDL_BUTTON_RIGHT)
                    continuer = 0;
                else
                    if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            positionZozor.x = event.button.x;
                            positionZozor.y = event.button.y;
                        }
                break;
            case SDL_MOUSEMOTION :
                positionZozor.x = event.motion.x;
                positionZozor.y = event.motion.y;
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                        continuer = 0;
                        break;
                    case SDLK_UP :
                        positionZozor.y--;
                        break;
                    case SDLK_DOWN :
                        positionZozor.y++;
                        break;
                    case SDLK_RIGHT :
                        positionZozor.x++;
                        break;
                    case SDLK_LEFT :
                        positionZozor.x--;
                        break;
                }
                break;
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
        SDL_BlitSurface(zozor,NULL,ecran,&positionZozor);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();


    EXIT_SUCCESS;

}
