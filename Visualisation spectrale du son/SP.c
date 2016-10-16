#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>
#include <errno.h>
#include <dirent.h>
#include <windows.h>
#include "SP.h"

#define LARGEUR_FENETRE_VSS         512
#define HAUTEUR_FENETRE_VSS         150
#define RATIO                       (HAUTEUR_FENETRE_VSS / 255.0)
#define DELAI_RAFRAICHISSEMENT      25
#define TAILLE_SPECTRE              512






void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}




int listerMorceaux(char tabTunes[500][500])
{
    // Déclaration des pointeurs utilisés pour la lecture d'un dossier
    DIR *dir;
    struct dirent *dp;
    int trouve = 0, i = 499, nbrTunes = 0;
    char tempFile[500] = {'0'};

    dir = opendir ("C:\\Documents and Settings\\CER3100426\\Mes documents\\PRIVE\\C\\Visualisation spectrale du son");

    while ((dp = readdir (dir)) != NULL)
    {
        for (i = 0;i < 500; i++)
        {
            tempFile[i] = '0';
        }
        sprintf(tempFile,"%s",dp->d_name);
        trouve = 0;
        i = 499;
        while ((trouve == 0) && (i > 4))
        {
            if(tempFile[i] == '3')
            {
                if(tempFile[i - 1] == 'p')
                {
                    if(tempFile[i - 2] == 'm')
                    {
                        if(tempFile[i - 3] == '.')
                        {
                            trouve = 1;
                            while (i >= 0)
                            {
                                tabTunes[nbrTunes][i] = tempFile[i];
                                i--;
                            }
                            nbrTunes++;
                        }
                    }
                }
            }
            i--;
        }

    }

    return(nbrTunes);
}




void initialiserTabTunes(char tabTunes[500][500])
{
    int i = 0, j = 0;

    for (i = 0;i < 500;i++)
    {
        j = 0;
        for (j = 0;j < 500;j++)
        {
            tabTunes[i][j] = '\0';
        }
    }

    return;
}




void afficherSpectre(SDL_Surface *vSS,float spectreD[TAILLE_SPECTRE],float spectreG[TAILLE_SPECTRE])
{
    int i = 0, j = 0, hauteur = 0;

    SDL_LockSurface(vSS);
    for (i = 0;i < 256;i++)
    {
        hauteur = spectreD[i * 2] * HAUTEUR_FENETRE_VSS * 20;
        if (hauteur > HAUTEUR_FENETRE_VSS)
        {
            hauteur = HAUTEUR_FENETRE_VSS;
        }
        for(j = HAUTEUR_FENETRE_VSS - hauteur;j < HAUTEUR_FENETRE_VSS; j++)
        {
            setPixel(vSS, 255 + i, j, SDL_MapRGB(vSS->format,(255 - (j/RATIO)),(j / (RATIO)),0));
        }
    }
    for (i = 254;i >= 0;i--)
    {
        hauteur = spectreG[(255-i)*2] * HAUTEUR_FENETRE_VSS * 20;
        if (hauteur > HAUTEUR_FENETRE_VSS)
        {
            hauteur = HAUTEUR_FENETRE_VSS;
        }
        for(j = HAUTEUR_FENETRE_VSS - hauteur;j < HAUTEUR_FENETRE_VSS; j++)
        {
            setPixel(vSS, i, j, SDL_MapRGB(vSS->format,(255 - (j/RATIO)),(j / (RATIO)),0));
        }
    }
    SDL_UnlockSurface(vSS);

    return;
}




int afficherTabTunes(char tabTunes[500][500],SDL_Surface *ecran,int tuneChoisie)
{
    SDL_Surface *morceau[12];
    int i = 0, j = 0, numTune = 0;
    SDL_Rect posTunes[12];
    char tempTunes[40];

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0,0,0};
    SDL_Color couleurRouge = {255,0,0};

    police = TTF_OpenFont("times.ttf", 12);

    for(i = 0;i < 12;i++)
    {
        for (j = 0;j < 37; j++)
        {
            tempTunes[j] = tabTunes[i][j];
        }
        tempTunes[40] = '\0';
        tempTunes[39] = '.';
        tempTunes[38] = '.';
        tempTunes[37] = '.';
        posTunes[i].x = 540;
        posTunes[i].y = 35 + 20*i;
        if (i == tuneChoisie)
        {
            morceau[i] = TTF_RenderText_Blended(police, tempTunes, couleurRouge);
            numTune = i;
        }
        else
        {
            morceau[i] = TTF_RenderText_Blended(police, tempTunes, couleurNoire);
        }
        SDL_BlitSurface(morceau[i],0,ecran,&posTunes[i]);
    }
    TTF_CloseFont(police);

    return(numTune);
}




int lectureMusique(FMOD_SYSTEM *system,FMOD_SOUND *musique,FMOD_RESULT resultat,int tuneAJouer,char tabTunes[500][500],unsigned int *tempsTune)
{
    int tuneJouee = 999;
    unsigned int tempTempsTune = 0;

    // Ouverture du morceau, test puis lecture.
	// Envoi de la durée du morceau au main
    FMOD_Sound_GetLength(musique, &tempTempsTune, FMOD_TIMEUNIT_MS);
    *tempsTune = tempTempsTune;

    if (resultat != FMOD_OK)
	{
		fprintf(stderr, "Impossible de lire le fichier mp3\n");
		exit(EXIT_FAILURE);
	}

	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

	tuneJouee = tuneAJouer;

    return(tuneJouee);
}




void afficherTemps(SDL_Surface *ecran, unsigned int tempsTune, FMOD_CHANNEL *canal)
{
    char temp[50];
    int minutesTune = 0, secondesTune = 0, minPosTune = 0, secPosTune = 0;
    unsigned int posTune = 0;
    float tempsTuneFloat = 0.0,secondesTuneFloat = 0.0,posTuneFloat = 0.0,secPosTuneFloat = 0.0;
    SDL_Surface *minTune = NULL, *secTune = NULL, *pPTune = NULL, *minutesPosTune = NULL, *secondesPosTune = NULL, *pPPosTune = NULL, *slashSep = NULL;
    SDL_Rect posMinTune, posSecTune, posPPTune, posMinutesPosTune, posSecondesPosTune, posPPPosTune, posSlashSep;

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0,0,0};
    police = TTF_OpenFont("times.ttf", 12);

    FMOD_Channel_GetPosition(canal, &posTune, FMOD_TIMEUNIT_MS);

    // Calculs pour le temps total du morceau
    tempsTuneFloat = tempsTune;
    minutesTune = tempsTune / 1000 / 60;
    secondesTuneFloat = tempsTuneFloat / 1000 / 60 - minutesTune;
    secondesTune = secondesTuneFloat * 60;

    // Calculs pour le temps en cours du morceau
    posTuneFloat = posTune;
    minPosTune = posTune / 1000 / 60;
    secPosTuneFloat = posTuneFloat / 1000 / 60 - minPosTune;
    secPosTune = secPosTuneFloat * 60;

    // Affichage des minutes pour le temps total du morceau
    if (minutesTune < 10)
    {
        sprintf(temp,"0%d",minutesTune);
    }
    else
    {
        sprintf(temp,"%d",minutesTune);
    }
    minTune = TTF_RenderText_Blended(police, temp, couleurNoire);

    // Affichage du caractère ":" séparant les minutes et les secondes pour le temps total du morceau
    pPTune = TTF_RenderText_Blended(police,":",couleurNoire);

    // Affichage des secondes pour le temps total du morceau
    if (secondesTune < 10)
    {
        sprintf(temp,"0%d",secondesTune);
    }
    else
    {
        sprintf(temp,"%d",secondesTune);
    }
    secTune = TTF_RenderText_Blended(police, temp, couleurNoire);

    // Affichage du slash séparant le temps en cours et le temps total
    slashSep = TTF_RenderText_Blended(police, "/", couleurNoire);

     // Affichage des minutes pour le temps en cours du morceau
    if (minPosTune < 10)
    {
        sprintf(temp,"0%d",minPosTune);
    }
    else
    {
        sprintf(temp,"%d",minPosTune);
    }
    minutesPosTune = TTF_RenderText_Blended(police, temp, couleurNoire);

    // Affichage du caractère ":" séparant les minutes et les secondes pour le temps en cours du morceau
    pPPosTune = TTF_RenderText_Blended(police,":",couleurNoire);

    // Affichage des secondes pour le temps en cours du morceau
    if (secPosTune < 10)
    {
        sprintf(temp,"0%d",secPosTune);
    }
    else
    {
        sprintf(temp,"%d",secPosTune);
    }
    secondesPosTune = TTF_RenderText_Blended(police, temp, couleurNoire);

    posMinTune.x = (ecran->w)/2 + 95;
    posMinTune.y = (ecran->h)/2 + 10;
    posPPTune.x = posMinTune.x + minTune->w;
    posPPTune.y = posMinTune.y;
    posSecTune.x = posPPTune.x + pPTune->w;
    posSecTune.y = posMinTune.y;
    posSlashSep.x = posMinTune.x - slashSep->w;
    posSlashSep.y = posMinTune.y;
    posSecondesPosTune.x = posSlashSep.x - secondesPosTune->w;
    posSecondesPosTune.y = posMinTune.y;
    posPPPosTune.x = posSecondesPosTune.x - pPPosTune->w;
    posPPPosTune.y = posMinTune.y;
    posMinutesPosTune.x = posPPPosTune.x - minutesPosTune->w;
    posMinutesPosTune.y = posMinTune.y;

    SDL_BlitSurface(minTune,0,ecran,&posMinTune);
    SDL_BlitSurface(pPTune,0,ecran,&posPPTune);
    SDL_BlitSurface(secTune,0,ecran,&posSecTune);
    SDL_BlitSurface(slashSep,0,ecran,&posSlashSep);
    SDL_BlitSurface(minutesPosTune,0,ecran,&posMinutesPosTune);
    SDL_BlitSurface(pPPosTune,0,ecran,&posPPPosTune);
    SDL_BlitSurface(secondesPosTune,0,ecran,&posSecondesPosTune);

    TTF_CloseFont(police);

    return;
}




void afficherVolume(SDL_Surface *ecran, float volume)
{
    int pourcentVolume = 0;
    float tempInt = 0;
    char temp[5];
    SDL_Surface *textVolume = NULL;
    SDL_Rect posTextVolume;

    posTextVolume.x = 132;
    posTextVolume.y = 178;

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0,0,0};
    police = TTF_OpenFont("times.ttf", 12);

    tempInt = volume * 100;
    pourcentVolume = tempInt;
    sprintf(temp,"%d",pourcentVolume);

    textVolume = TTF_RenderText_Blended(police, temp, couleurNoire);
    SDL_BlitSurface(textVolume,0,ecran,&posTextVolume);

    return;
}




void afficherTempsRecherche(SDL_Surface *ecran, unsigned int tempsPixel, int posSourisx, int posSourisy)
{
    char temp[50];
    float tempsRecherche = 0.0, secTpsRechercheFloat = 0.0;
    int secTpsRecherche = 0, minTpsRecherche = 0;
    SDL_Surface *minTempsRecherche = NULL, *secTempsRecherche = NULL, *pPTempsRecherche = NULL;
    SDL_Rect posMinTempsRecherche, posSecTempsRecherche, posPPTempsRecherche;

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0,0,0};
    police = TTF_OpenFont("times.ttf", 12);

    // Calculs pour le temps en recherche du morceau
    tempsRecherche = tempsPixel;
    minTpsRecherche = tempsPixel / 1000 / 60;
    secTpsRechercheFloat = tempsRecherche / 1000 / 60 - minTpsRecherche;
    secTpsRecherche = secTpsRechercheFloat * 60;

    // Affichage des minutes pour le temps en recherche du morceau
    if (minTpsRecherche < 10)
    {
        sprintf(temp,"0%d",minTpsRecherche);
    }
    else
    {
        sprintf(temp,"%d",minTpsRecherche);
    }
    minTempsRecherche = TTF_RenderText_Blended(police, temp,couleurNoire);

    // Affichage du caractère ":" séparant les minutes et les secondes pour le temps en recherche
    pPTempsRecherche = TTF_RenderText_Blended(police,":",couleurNoire);

    // Affichage des secondes pour le temps en recherche du morceau
    if (secTpsRecherche < 10)
    {
        sprintf(temp, "0%d", secTpsRecherche);
    }
    else
    {
        sprintf(temp,"%d",secTpsRecherche);
    }
    secTempsRecherche = TTF_RenderText_Blended(police,temp,couleurNoire);

    posMinTempsRecherche.x = posSourisx + minTempsRecherche->w;
    posMinTempsRecherche.y = posSourisy + minTempsRecherche->h;
    posPPTempsRecherche.x = posMinTempsRecherche.x + minTempsRecherche->w;
    posPPTempsRecherche.y = posMinTempsRecherche.y;
    posSecTempsRecherche.x = posPPTempsRecherche.x + pPTempsRecherche->w;
    posSecTempsRecherche.y = posMinTempsRecherche.y;

    SDL_BlitSurface(minTempsRecherche,0,ecran,&posMinTempsRecherche);
    SDL_BlitSurface(pPTempsRecherche,0,ecran,&posPPTempsRecherche);
    SDL_BlitSurface(secTempsRecherche,0,ecran,&posSecTempsRecherche);

    return;
}




int deplacementPtBarAvancement(FMOD_CHANNEL *canal, FMOD_SOUND *musique)
{
    unsigned int tempTempsTune = 0, posTune = 0;
    float tempsPixel = 0.0, tempTempsTuneFloat = 0.0, posTuneFloat = 0.0;

    FMOD_Channel_GetPosition(canal, &posTune, FMOD_TIMEUNIT_MS);
    FMOD_Sound_GetLength(musique, &tempTempsTune, FMOD_TIMEUNIT_MS);

    tempTempsTuneFloat = tempTempsTune;
    posTuneFloat = posTune;
    tempsPixel = tempTempsTuneFloat / 500;
    posTuneFloat = posTuneFloat / tempsPixel;

    posTune = posTuneFloat;

    return(posTune);
}
















