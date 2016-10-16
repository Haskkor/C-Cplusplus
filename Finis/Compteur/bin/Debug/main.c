#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

int main ( int argc, char** argv )
{
    SDL_Surface *ecran = NULL;
    SDL_Surface *texte = NULL;
    SDL_Rect posTexte;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0,0,0};
    int tpsNow = 0,tpsBfr = 0,continuer = 1,compteur = 0;
    char tabTps[20] = "";

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

    police = TTF_OpenFont("SerpentisBlack.ttf", 65);

    tpsNow = SDL_GetTicks();
    sprintf(tabTps,"Temps : %d",compteur);
    texte = TTF_RenderText_Blended(police, tabTps, couleurNoire);

    while (continuer == 1)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;
        }
        SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));

        tpsNow = SDL_GetTicks();
        if (tpsNow - tpsBfr >= 1000)
        {
            compteur += 1;
            sprintf(tabTps,"Temps : %d",compteur);
            SDL_FreeSurface(texte);
            texte = TTF_RenderText_Blended(police, tabTps, couleurNoire);
            tpsBfr = tpsNow;
        }
        posTexte.x = ecran->w / 2 - texte->w / 2;
        posTexte.y = ecran->h / 2 - texte->h / 2;
        SDL_BlitSurface(texte,0,ecran,&posTexte);
        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;
}

