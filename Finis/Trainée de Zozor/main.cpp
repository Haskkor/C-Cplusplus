#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionsZozor[3];
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640,640,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Trainée Zozor",NULL);

    zozor = SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor,SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format,0,0,255));

    positionsZozor[0].x = (ecran->w/2) - (zozor->w/2);
    positionsZozor[0].y = (ecran->h/2) - (zozor->h/2);

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    SDL_BlitSurface(zozor,NULL,ecran,&positionsZozor[1]);
    SDL_Flip(ecran);
    SDL_ShowCursor(SDL_DISABLE);



    while(continuer == 1)
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
                }
                break;
            case SDL_MOUSEMOTION :
                positionsZozor[0].x = event.motion.x ;
                positionsZozor[0].y = event.motion.y ;
                positionsZozor[1].x = event.motion.x + 20;
                positionsZozor[1].y = event.motion.y + 20;
                positionsZozor[2].x = event.motion.x + 40;
                positionsZozor[2].y = event.motion.y + 40;
                break;
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
        SDL_BlitSurface(zozor,NULL,ecran,&positionsZozor[0]);
        SDL_BlitSurface(zozor,NULL,ecran,&positionsZozor[1]);
        SDL_BlitSurface(zozor,NULL,ecran,&positionsZozor[2]);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();

    EXIT_SUCCESS;


}

