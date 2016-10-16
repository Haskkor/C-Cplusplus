#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "SP.h"


void compteDepart(SDL_Surface *ecran,FMOD_SYSTEM *system)
{
    FMOD_SOUND *tick = NULL;
    FMOD_System_CreateSound(system, "clock-tick.wav", FMOD_CREATESAMPLE, 0, &tick);

    TTF_Font *police = NULL;
    police = TTF_OpenFont("ka.ttf", 180);
    SDL_Color couleurRouge = {255,0,0};
    SDL_Surface *texte;
    SDL_Rect posTexte;

    texte = TTF_RenderText_Blended(police, "3", couleurRouge);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,tick,0,NULL);
    posTexte.x = ecran->w / 2 - texte->w / 2;
    posTexte.y = ecran->h / 2 - texte->h / 2;
    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(texte,0,ecran,&posTexte);
    SDL_Flip(ecran);
    SDL_Delay(1000);

    texte = TTF_RenderText_Blended(police, "2", couleurRouge);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,tick,0,NULL);
    posTexte.x = ecran->w / 2 - texte->w / 2;
    posTexte.y = ecran->h / 2 - texte->h / 2;
    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(texte,0,ecran,&posTexte);
    SDL_Flip(ecran);
    SDL_Delay(1000);

    texte = TTF_RenderText_Blended(police, "1", couleurRouge);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,tick,0,NULL);
    posTexte.x = ecran->w / 2 - texte->w / 2;
    posTexte.y = ecran->h / 2 - texte->h / 2;
    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(texte,0,ecran,&posTexte);
    SDL_Flip(ecran);
    SDL_Delay(1000);

    return;
}



void montrerResultats(SDL_Surface *ecran,int cptHit,int cptShoot,FMOD_SYSTEM *system)
{
    float ratioP = 0, res = 0, ratioPC = 0;
    char tabCT[40], tabNBC[40], ratioTable[40], tabSF[40];

    TTF_Font *police = NULL;
    SDL_Rect posNbrCibles, posNbrCoups, posRatio, posScoreFinal, posFond;

    FMOD_SOUND *cheers = NULL;
    FMOD_System_CreateSound(system, "bravo.mp3", FMOD_CREATESAMPLE, 0, &cheers);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,cheers,0,NULL);

    SDL_Surface *nbrCibles = NULL, *nbrCoups = NULL, *ratio = NULL, *scoreFinal = NULL, *fond = NULL;
    police = TTF_OpenFont("ka.ttf", 35);
    SDL_Color couleur = {0,255,0};
    fond = IMG_Load("mod_target512.png");

    ratioP =(float) (cptHit) / cptShoot;
    res = cptHit * ratioP;
    ratioPC = ratioP * 100;

    majHS(res);

    sprintf(tabSF, "Score final %0.2f points",res);
    sprintf(tabCT, "Cibles touchees %d", cptHit);
    sprintf(tabNBC, "Coups tires %d", cptShoot);
    sprintf(ratioTable, "Ratio %0.2f", ratioPC);

    nbrCibles = TTF_RenderText_Blended(police,tabCT,couleur);
    nbrCoups = TTF_RenderText_Blended(police,tabNBC,couleur);
    ratio = TTF_RenderText_Blended(police,ratioTable,couleur);
    scoreFinal =TTF_RenderText_Blended(police,tabSF,couleur);

    posNbrCibles.x = ecran->w / 2 - nbrCibles->w / 2;
    posNbrCibles.y = 160 - nbrCibles->h / 2;
    posNbrCoups.x = ecran->w / 2 - nbrCoups->w / 2;
    posNbrCoups.y = 320 - nbrCoups->h / 2;
    posRatio.x = ecran->w / 2 - ratio->w / 2;
    posRatio.y = 480 - ratio->h / 2;
    posScoreFinal.x = ecran->w / 2 - scoreFinal->w / 2;
    posScoreFinal.y = 640 - scoreFinal->h / 2;
    posFond.x = ecran->w / 2 - fond->w / 2;
    posFond.y = ecran->h / 2 - fond->w / 2;

    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(fond,0,ecran,&posFond);
    SDL_BlitSurface(nbrCibles,0,ecran,&posNbrCibles);
    SDL_BlitSurface(nbrCoups,0,ecran,&posNbrCoups);
    SDL_BlitSurface(ratio,0,ecran,&posRatio);
    SDL_BlitSurface(scoreFinal,0,ecran,&posScoreFinal);

    SDL_Flip(ecran);

    SDL_Delay(5000);

    return;

}



void menuJeu(SDL_Surface *ecran,FMOD_SYSTEM *system,int *continuer,int *mainloop)
{
    int menu = 1,boolSouris = 0,dif = 0,timSouris = 0,son = 0;
    SDL_Surface *butJouer = NULL, *butScore = NULL, *butQuit = NULL, *fond = NULL;
    SDL_Rect posButJouer, posButScore, posButQuit;
    SDL_Event event;

    SDL_ShowCursor(SDL_ENABLE);

    FMOD_SOUND *bip = NULL;
    FMOD_System_CreateSound(system, "shaker.wav", FMOD_CREATESAMPLE, 0, &bip);

    butJouer = IMG_Load("go_button.png");
    butScore = IMG_Load("resultsbutton.png");
    butQuit = IMG_Load("Stop.png");
    fond = IMG_Load("m14.jpg");

    posButJouer.x = ecran->w / 4 - butJouer->w / 2;
    posButJouer.y = ecran->h / 4 - butJouer->h / 2;
    posButScore.x = ecran->w / 4 * 3 - butScore->w / 2;
    posButScore.y = ecran->h / 4 - butScore->h / 2;
    posButQuit.x = ecran->w / 2 - butQuit->w / 2;
    posButQuit.y = ecran->h / 4 * 3 - butQuit->h / 2;

    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(fond,0,ecran,0);
    SDL_BlitSurface(butJouer,0,ecran,&posButJouer);
    SDL_BlitSurface(butScore,0,ecran,&posButScore);
    SDL_BlitSurface(butQuit,0,ecran,&posButQuit);
    SDL_Flip(ecran);

    while(menu == 1)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_MOUSEMOTION :
                if (event.motion.x >= posButJouer.x && event.motion.x < posButJouer.x + butJouer->w && event.motion.y >= posButJouer.y && event.motion.y < posButJouer.y + butJouer->h)
                {
                    if (son == 1)
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,bip,0,NULL);
                        son = 0;
                    }
                }
                if (event.motion.x >= posButScore.x && event.motion.x < posButScore.x + butScore->w && event.motion.y >= posButScore.y && event.motion.y < posButScore.y + butScore->h)
                {
                    if (son == 1)
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,bip,0,NULL);
                        son = 0;
                    }
                }
                if (event.motion.x >= posButQuit.x && event.motion.x < posButQuit.x + butQuit->w && event.motion.y >= posButQuit.y && event.motion.y < posButQuit.y + butQuit->h)
                {
                    if (son == 1)
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,bip,0,NULL);
                        son = 0;
                    }
                }
                if ((!(event.motion.x >= posButJouer.x && event.motion.x < posButJouer.x + butJouer->w && event.motion.y >= posButJouer.y && event.motion.y < posButJouer.y + butJouer->h)) && (!(event.motion.x >= posButScore.x && event.motion.x < posButScore.x + butScore->w && event.motion.y >= posButScore.y && event.motion.y < posButScore.y + butScore->h)) && (!(event.motion.x >= posButQuit.x && event.motion.x < posButQuit.x + butQuit->w && event.motion.y >= posButQuit.y && event.motion.y < posButQuit.y + butQuit->h)))
                {
                    son = 1;
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                boolSouris = 1;
                break;
            case SDL_MOUSEBUTTONUP :
                if (boolSouris == 1)
                {
                    dif = SDL_GetTicks();
                    if (dif - timSouris > 120)
                    {
                        timSouris = SDL_GetTicks();
                    }
                    boolSouris = 0;
                    if (event.motion.x >= posButJouer.x && event.motion.x < posButJouer.x + butJouer->w && event.motion.y >= posButJouer.y && event.motion.y < posButJouer.y + butJouer->h)
                    {
                        menu = 0;
                    }
                    if (event.motion.x >= posButScore.x && event.motion.x < posButScore.x + butScore->w && event.motion.y >= posButScore.y && event.motion.y < posButScore.y + butScore->h)
                    {
                        highScores(ecran);
                        menu = 0;
                        *continuer = 0;
                    }
                    if(event.motion.x >= posButQuit.x && event.motion.x < posButQuit.x + butQuit->w && event.motion.y >= posButQuit.y && event.motion.y < posButQuit.y + butQuit->h)
                    {
                        menu = 0;
                        *continuer = 0;
                        *mainloop = 0;
                    }
                }
                break;
        }
    }

    return;

}




void highScores(SDL_Surface *ecran)
{
    float tabScore[4] = {0};
    char tab1[20], tab2[20], tab3[20], tab4[20], tab5[20];
    FILE *fichier = NULL;
    fichier = fopen("highscores.txt","r");

    fscanf(fichier, "%f\n%f\n%f\n%f\n%f", &tabScore[0], &tabScore[1], &tabScore[2], &tabScore[3], &tabScore[4]);

    SDL_Surface *hs1 = NULL, *hs2 = NULL, *hs3 = NULL, *hs4 = NULL, *hs5 = NULL, *titre = NULL;
    SDL_Rect posHS1, posHS2, posHS3, posHS4, posHS5, posTitre;
    TTF_Font *police = NULL, *policeTitre = NULL;
    police = TTF_OpenFont("ka.ttf", 15);
    policeTitre = TTF_OpenFont("ka.ttf", 25);
    SDL_Color couleurBlanche = {255,255,255};

    sprintf(tab1, "1 - %0.2f points",tabScore[0]);
    sprintf(tab2, "2 - %0.2f points",tabScore[1]);
    sprintf(tab3, "3 - %0.2f points",tabScore[2]);
    sprintf(tab4, "4 - %0.2f points",tabScore[3]);
    sprintf(tab5, "5 - %0.2f points",tabScore[4]);

    hs1 = TTF_RenderText_Blended(police,tab1,couleurBlanche);
    hs2 = TTF_RenderText_Blended(police,tab2,couleurBlanche);
    hs3 = TTF_RenderText_Blended(police,tab3,couleurBlanche);
    hs4 = TTF_RenderText_Blended(police,tab4,couleurBlanche);
    hs5 = TTF_RenderText_Blended(police,tab5,couleurBlanche);
    titre = TTF_RenderText_Blended(policeTitre,"Meilleurs Scores",couleurBlanche);

    posHS1.x = ecran->w / 2 - hs1->w / 2;
    posHS1.y = 200;
    posHS2.x = ecran->w / 2 - hs2->w / 2;
    posHS2.y = 300;
    posHS3.x = ecran->w / 2 - hs3->w / 2;
    posHS3.y = 400;
    posHS4.x = ecran->w / 2 - hs4->w / 2;
    posHS4.y = 500;
    posHS5.x = ecran->w / 2 - hs5->w / 2;
    posHS5.y = 600;
    posTitre.x = ecran->w / 2 - titre->w / 2;
    posTitre.y = 50;

    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(titre,0,ecran,&posTitre);
    SDL_BlitSurface(hs1,0,ecran,&posHS1);
    SDL_BlitSurface(hs2,0,ecran,&posHS2);
    SDL_BlitSurface(hs3,0,ecran,&posHS3);
    SDL_BlitSurface(hs4,0,ecran,&posHS4);
    SDL_BlitSurface(hs5,0,ecran,&posHS5);

    SDL_Flip(ecran);

    SDL_Delay(5000);

    return;


}



void majHS(float res)
{
    float tabScore[5] = {0},varStock,varStockk;
    int i = 4;
    FILE *fichier = NULL;

    fichier = fopen("highscores.txt","r+");
    fscanf(fichier, "%f\n%f\n%f\n%f\n%f", &tabScore[0], &tabScore[1], &tabScore[2], &tabScore[3], &tabScore[4]);
    tabScore[5] = res;

    for (i = 5; i > 0; i--)
    {
        varStock = tabScore[i];
        if (tabScore[i] > tabScore[i - 1])
        {
            varStockk = tabScore[i - 1];
            tabScore[i - 1] = varStock;
            tabScore[i] = varStockk;
        }
    }

    rewind(fichier);

    fprintf(fichier,"%f\n%f\n%f\n%f\n%f",tabScore[0],tabScore[1],tabScore[2],tabScore[3],tabScore[4]);

    fclose(fichier);

    return;
}


