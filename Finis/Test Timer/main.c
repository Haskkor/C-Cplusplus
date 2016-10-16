#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *mario = NULL;
    SDL_Rect posMario;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    int continuer = 1,tempsActuel = 0,tempsPrecedent = 0,versLaDroite = 1,pause = 0;

    ecran = SDL_SetVideoMode(800,800,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

    posMario.x = 800 / 2 - 34 / 2;
    posMario.y = 800 / 2 - 34 / 2;

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    mario = IMG_Load("mario_bas.gif");
    SDL_BlitSurface(mario,NULL,ecran,&posMario);
    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_KEYDOWN :
                switch (event.key.keysym.sym)
                {
                    case SDLK_RETURN :
                        SDL_Delay(100);
                        if (pause == 0)
                        {
                            pause = 1;
                        }
                        else if (pause == 1)
                        {
                            pause = 0;
                        }
                        break;
                }
                break;
        }
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 1) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            if (pause == 0)
            {
                if (versLaDroite)
                {
                    posMario.x++;
                    posMario.y++;
                }
                else
                {
                    posMario.x--;
                    posMario.y--;
                }
            }
            if ((posMario.x == 800 - 34) || (posMario.y == 800 - 34))
            {
                versLaDroite = 0;
            }
            if ((posMario.x == 0) || (posMario.y == 0))
            {
                versLaDroite = 1;
            }
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }
        else
        {
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(mario, NULL, ecran, &posMario);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(mario);
    SDL_Quit();

    return EXIT_SUCCESS;
}
