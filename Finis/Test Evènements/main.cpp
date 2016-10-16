#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    int continuer = 1;
    SDL_Surface *ecran = NULL;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE);
    SDL_WM_SetCaption("Gestion des évènements en SDL",NULL);

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        SDL_WaitEvent(&event); /* On attend un évènement qu'on récupère dans event */
        switch(event.type) /* On teste le type d'évènement */
        {
            case SDL_QUIT: /* Si c'est un évènement QUITTER */
                continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
                break;
            case SDL_KEYDOWN: /* Si appui d'une touche */
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;
                }
                break;
        }
    }


    SDL_Quit();

    return EXIT_SUCCESS;

}
