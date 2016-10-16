#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

int main ( int argc, char** argv )
{
    SDL_Surface *ecran = NULL, *score = NULL, *cAR = NULL;
    SDL_Rect posScore, posCAR;
    SDL_Event event;
    TTF_Font *fontScore = NULL;
    SDL_Color couleurNoire = {0,0,0};
    int tpsNow = 0, tpsBfr = 0, continuer = 1, compteur = 10, compteurCps = 0;
    Uint32 timSouris = 0,dif = 0;
    char tabTps[20] = "", tabCps[20] = "";

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

    fontScore = TTF_OpenFont("HIROSHT.TTF",35);

    sprintf(tabCps, "Nombre de clics : %d.",compteurCps);
    score = TTF_RenderText_Blended(fontScore,tabCps,couleurNoire);
    posScore.x = 320 - score->w / 2;
    posScore.y = 120 - score->h / 2;
    posCAR.x = 170;
    posCAR.y = 320;

    while (continuer == 1)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN :
                dif = SDL_GetTicks();
                if (dif - timSouris > 120)
                {
                    compteurCps++;
                    sprintf(tabCps, "Nombre de clics : %d.",compteurCps);
                    SDL_FreeSurface(score);
                    score = TTF_RenderText_Blended(fontScore,tabCps,couleurNoire);
                    timSouris = SDL_GetTicks();
                }
                break;
        }
        if (compteur == 10)
        {
            sprintf(tabTps, "Fin dans : %d.",compteur);
            SDL_FreeSurface(cAR);
            cAR = TTF_RenderText_Blended(fontScore,tabTps,couleurNoire);
        }

        if (tpsNow - tpsBfr >= 1000)
        {
            compteur--;
            sprintf(tabTps, "Fin dans : %d.",compteur);
            SDL_FreeSurface(cAR);
            cAR = TTF_RenderText_Blended(fontScore,tabTps,couleurNoire);
            tpsBfr = tpsNow;
        }
        if (compteur == 0)
        {
            continuer = 0;
        }
        SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));
        SDL_BlitSurface(score,0,ecran,&posScore);
        SDL_BlitSurface(cAR,0,ecran,&posCAR);
        SDL_Flip(ecran);
        tpsNow = SDL_GetTicks();
    }

    sprintf(tabCps, "%d",compteurCps);
    sprintf(tabTps, "Score final : ",compteur);
    score = TTF_RenderText_Blended(fontScore,tabCps,couleurNoire);
    cAR = TTF_RenderText_Blended(fontScore,tabTps,couleurNoire);
    posScore.x = 320 - score->w / 2;
    posScore.y = 300 - score->h / 2;
    posCAR.x = 320 - cAR->w / 2;
    posCAR.y = 120 - cAR->h / 2;
    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));
    SDL_BlitSurface(score,0,ecran,&posScore);
    SDL_BlitSurface(cAR,0,ecran,&posCAR);
    SDL_Flip(ecran);
    SDL_Delay(4000);

    TTF_CloseFont(fontScore);
    TTF_Quit();
    SDL_FreeSurface(score);
    SDL_FreeSurface(cAR);
    SDL_Quit();

    return EXIT_SUCCESS;

}
