#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>
#include <errno.h>
#include <dirent.h>
#include "SP.h"

#define LARGEUR_FENETRE_VSS         512
#define HAUTEUR_FENETRE_VSS         150
#define RATIO                       (HAUTEUR_FENETRE_VSS / 255.0)
#define DELAI_RAFRAICHISSEMENT      25
#define TAILLE_SPECTRE              512




int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *vSS = NULL, *liste = NULL, *stopBut = NULL, *playBut = NULL, *nextBut = NULL, *prevBut = NULL;
    SDL_Surface *tuneName = NULL, *barSound = NULL, *pointBarSound = NULL, *barAvancement = NULL, *ptBarAvancement = NULL;
    SDL_Event event;
    SDL_Rect posVSS, posListe, posBut[4], posTuneName, posBarSound, posPointBarSound, posBarAvancement, posPtBarAvancement;
    float spectreG[TAILLE_SPECTRE],spectreD[TAILLE_SPECTRE], volume = 1.0, tempUn = 0.0, tempDeux = 0.0, tempTrois = 0.0;
    int continuer = 1, tuneChoisie = 100,lecture = 1, tuneAJouer = 0,clic = 0,boolSouris = 0,spectre = 0,changerBut = 1, nbrTunes = 0;
    int start = 1, stopPress = 0, tuneJouee = 100, clicPointBarSound = 0, i = 0, clicPointBarAvancement = 0, posSourisx = 0;
    int posSourisy = 0;
    char tabTunes[500][500],tempTuneName[500], *tagArtist, *tagName;
    unsigned int posInTune = 0, tempsTune = 0, tempTempsTune = 0, tempsPixel = 0, tempTempsPixel = 0;
    Uint32 timSpectre,majSpectre = 0,timClic = 0,timSouris = 0,dif = 0;

    FMOD_SYSTEM *system;
	FMOD_SOUND *musique;
	FMOD_RESULT resultat;
	FMOD_CHANNEL *canal;
	FMOD_CHANNELGROUP *canalGen;
	FMOD_BOOL etat;
	FMOD_TAG tag, tag2;

	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    // Initialisation du tableau de morceaux
    initialiserTabTunes(tabTunes);

	// Récupérer la liste de morceaux disponibles dans le dossier
	nbrTunes = listerMorceaux(tabTunes);

    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Font *police = NULL;
    police = TTF_OpenFont("times.ttf", 12);
    SDL_Color couleurRouge = {255,0,0};
    SDL_WM_SetIcon(IMG_Load("spectrum.png"),NULL);
	ecran = SDL_SetVideoMode(768, 300, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Lecteur musical", NULL);

	vSS = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_FENETRE_VSS, HAUTEUR_FENETRE_VSS, 32, 0, 0, 0, 0);

	liste = IMG_Load("BlankScroll.gif");
	stopBut = IMG_Load("Button-Stop-48.png");
	playBut = IMG_Load("Button-Play-48.png");
	prevBut = IMG_Load("Button-Previous-48.png");
	nextBut = IMG_Load("Button-Next-48.png");
	pointBarSound = IMG_Load("dot_2.png");
	barSound = IMG_Load("scroll10-100.jpg");
	barAvancement = IMG_Load("divider.jpg");
	SDL_SetColorKey(barAvancement, SDL_SRCCOLORKEY, SDL_MapRGB(barAvancement->format, 255, 255, 255));
	ptBarAvancement = IMG_Load("dot_2.png");

	SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,236,233,216));

    posVSS.x = 5;
	posVSS.y = 5;
	posListe.x = 522;
	posListe.y = 0;
	posBut[0].x = 10;
	posBut[0].y = ecran->h - playBut->h - 10;
    posBut[1].x = playBut->w + 20;
	posBut[1].y = ecran->h - stopBut->h - 10;
    posBut[2].x = (playBut->w * 3) + 20;
	posBut[2].y = ecran->h - prevBut->h - 10;
    posBut[3].x = (playBut->w * 4) + 20;
	posBut[3].y = ecran->h - nextBut->h - 10;
    posTuneName.x = 5;
    posTuneName.y = ecran->h - 15;
    posBarSound.x = 20;
    posBarSound.y = 180;
    posPointBarSound.x = (posBarSound.x + barSound->w - (pointBarSound->w / 2));
    posPointBarSound.y = posBarSound.y - 2;
    posBarAvancement.x = 20;
    posBarAvancement.y = 220;
    posPtBarAvancement.x = posBarAvancement.x - (ptBarAvancement->w / 2);
    posPtBarAvancement.y = posBarAvancement.y - 2;

    while (continuer == 1)
    {
        SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,236,233,216));

        // Affichage de la liste de morceaux à jouer
        SDL_BlitSurface(liste,0,ecran,&posListe);
        tuneAJouer = afficherTabTunes(tabTunes,ecran,tuneChoisie);

        SDL_PollEvent(&event);
		switch(event.type)
		{
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION :
                if (event.motion.x >= posBut[0].x + 7 && event.motion.x < posBut[0].x + playBut->w - 7 && event.motion.y >= posBut[0].y + 7 && event.motion.y < posBut[0].y + playBut->h - 7)
                {
                    if (stopPress == 1)
                    {
                        playBut = IMG_Load("Button-Play-48-red.png");
                    }
                    else
                    {
                        if (changerBut == 1)
                        {
                            FMOD_System_GetMasterChannelGroup(system, &canalGen);
                            FMOD_ChannelGroup_GetPaused(canalGen, &etat);

                                if (lecture == 0)
                                {
                                    playBut = IMG_Load("Button-Pause-48-red.png");
                                    changerBut = 0;
                                }
                                else
                                {
                                    if (etat)
                                    {
                                        playBut = IMG_Load("Button-Play-48-red.png");
                                        changerBut = 0;
                                    }
                                    else
                                    {
                                        playBut = IMG_Load("Button-Pause-48-red.png");
                                        changerBut = 0;
                                    }
                                }
                                if (start == 1)
                                {
                                    playBut = IMG_Load("Button-Play-48-red.png");
                                }
                        }
                    }
                }
                if (event.motion.x >= posBut[1].x + 7 && event.motion.x < posBut[1].x + stopBut->w - 7 && event.motion.y >= posBut[1].y + 7 && event.motion.y < posBut[1].y + stopBut->h - 7)
                {
                    if (changerBut == 1)
                    {
                        stopBut = IMG_Load("Button-Stop-48-red.png");
                        changerBut = 0;
                    }
                }
                if (event.motion.x >= posBut[2].x + 7 && event.motion.x < posBut[2].x + prevBut->w - 7 && event.motion.y >= posBut[2].y + 7 && event.motion.y < posBut[2].y + prevBut->h - 7)
                {
                    if (changerBut == 1)
                    {
                        prevBut = IMG_Load("Button-Previous-48-red.png");
                        changerBut = 0;
                    }
                }
                if (event.motion.x >= posBut[3].x + 7 && event.motion.x < posBut[3].x + nextBut->w - 7 && event.motion.y >= posBut[3].y + 7 && event.motion.y < posBut[3].y + nextBut->h - 7)
                {
                    if (changerBut == 1)
                    {
                        nextBut = IMG_Load("Button-Next-48-red.png");
                        changerBut = 0;
                    }
                }
                if (event.motion.x >= posPointBarSound.x && event.motion.x < posPointBarSound.x + pointBarSound->w && event.motion.y >= posPointBarSound.y && event.motion.y < posPointBarSound.y + pointBarSound->h)
                {
                    if ((changerBut == 1) && (clicPointBarSound != 1))
                    {
                        pointBarSound = IMG_Load("dot_2_green.png");
                        changerBut = 0;
                    }
                }
                if (event.motion.x >= posPtBarAvancement.x && event.motion.x < posPtBarAvancement.x + ptBarAvancement->w && event.motion.y >= posPtBarAvancement.y && event.motion.y < posPtBarAvancement.y + ptBarAvancement->h)
                {
                    if ((changerBut == 1) && (clicPointBarAvancement != 1))
                    {
                        ptBarAvancement = IMG_Load("dot_2_green.png");
                        changerBut = 0;
                    }
                }
                if ((!(event.motion.x >= posBut[0].x + 7 && event.motion.x < posBut[0].x + playBut->w - 7 && event.motion.y >= posBut[0].y + 7 && event.motion.y < posBut[0].y + playBut->h - 7)) && (!(event.motion.x >= posBut[1].x + 7 && event.motion.x < posBut[1].x + stopBut->w - 7 && event.motion.y >= posBut[1].y + 7 && event.motion.y < posBut[1].y + stopBut->h - 7)) && (!(event.motion.x >= posBut[2].x + 7 && event.motion.x < posBut[2].x + prevBut->w - 7 && event.motion.y >= posBut[2].y + 7 && event.motion.y < posBut[2].y + prevBut->h - 7)) && (!(event.motion.x >= posBut[3].x + 7 && event.motion.x < posBut[3].x + nextBut->w - 7 && event.motion.y >= posBut[3].y + 7 && event.motion.y < posBut[3].y + nextBut->h - 7)) && (!(event.motion.x >= posPointBarSound.x && event.motion.x < posPointBarSound.x + pointBarSound->w && event.motion.y >= posPointBarSound.y && event.motion.y < posPointBarSound.y + pointBarSound->h)) && (!(event.motion.x >= posPtBarAvancement.x && event.motion.x < posPtBarAvancement.x + ptBarAvancement->w && event.motion.y >= posPtBarAvancement.y && event.motion.y < posPtBarAvancement.y + ptBarAvancement->h)))
                {
                    changerBut = 1;
                    FMOD_System_GetMasterChannelGroup(system, &canalGen);
                    FMOD_ChannelGroup_GetPaused(canalGen, &etat);
                    if (start == 1)
                    {
                        etat = 1;
                    }
                    if (lecture == 0)
                    {
                        playBut = IMG_Load("Button-Pause-48.png");
                    }
                    else
                    {
                        if (stopPress == 1)
                        {
                            playBut = IMG_Load("Button-Play-48.png");
                        }
                        else
                        {
                            if (etat)
                            {
                                playBut = IMG_Load("Button-Play-48.png");
                            }
                            else
                            {
                                playBut = IMG_Load("Button-Pause-48.png");
                            }
                        }
                        if (clicPointBarSound == 0)
                        {
                            pointBarSound = IMG_Load("dot_2.png");
                        }
                        if (clicPointBarAvancement == 0)
                        {
                            ptBarAvancement = IMG_Load("dot_2.png");
                        }
                    }
                    stopBut = IMG_Load("Button-Stop-48.png");
                    prevBut = IMG_Load("Button-Previous-48.png");
                    nextBut = IMG_Load("Button-Next-48.png");
                }
                if (clicPointBarAvancement == 1)
                {
                    FMOD_Sound_GetLength(musique, &tempTempsTune, FMOD_TIMEUNIT_MS);
                    tempTempsPixel = tempTempsTune / 500;
                    tempsPixel = (posPtBarAvancement.x + (ptBarAvancement->w / 2) - posBarAvancement.x) * tempTempsPixel;
                    posSourisx = event.motion.x;
                    posSourisy = event.motion.y;
                    afficherTempsRecherche(ecran,tempsPixel,posSourisx,posSourisy);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                boolSouris = 1;
                if (event.motion.x >= posBut[0].x + 7 && event.motion.x < posBut[0].x + playBut->w - 7 && event.motion.y >= posBut[0].y + 7 && event.motion.y < posBut[0].y + playBut->h - 7)
                {
                    FMOD_System_GetMasterChannelGroup(system, &canalGen);
                    FMOD_ChannelGroup_GetPaused(canalGen, &etat);
                    if (etat)
                    {
                        playBut = IMG_Load("Button-Play-48-clic.png");
                    }
                    else
                    {
                        playBut = IMG_Load("Button-Pause-48-clic.png");
                    }
                }
                if (event.motion.x >= posBut[1].x + 7 && event.motion.x< posBut[1].x + stopBut->w - 7 && event.motion.y >= posBut[1].y + 7 && event.motion.y < posBut[1].y + stopBut->h - 7)
                {
                    stopBut = IMG_Load("Button-Stop-48-clic.png");
                }
                if (event.motion.x >= posBut[2].x + 7 && event.motion.x< posBut[2].x + prevBut->w - 7 && event.motion.y >= posBut[2].y + 7 && event.motion.y < posBut[2].y + prevBut->h - 7)
                {
                    prevBut = IMG_Load("Button-Previous-48-clic.png");
                }
                if (event.motion.x >= posBut[3].x + 7 && event.motion.x< posBut[3].x + nextBut->w - 7 && event.motion.y >= posBut[3].y + 7 && event.motion.y < posBut[3].y + nextBut->h - 7)
                {
                    nextBut = IMG_Load("Button-Next-48-clic.png");
                }
                if (event.motion.x >= posPointBarSound.x && event.motion.x < posPointBarSound.x + pointBarSound->w && event.motion.y >= posPointBarSound.y && event.motion.y < posPointBarSound.y + pointBarSound->h)
                {
                    pointBarSound = IMG_Load("dot_2_clic.png");
                    clicPointBarSound = 1;
                }
                if (event.motion.x >= posBarSound.x && event.motion.x < posBarSound.x + barSound->w && event.motion.y > posBarSound.y && event.motion.y < posBarSound.y + barSound->h)
                {
                    posPointBarSound.x = event.motion.x - (pointBarSound->w / 2);
                }
                if (event.motion.x >= posPtBarAvancement.x && event.motion.x < posPtBarAvancement.x + ptBarAvancement->w && event.motion.y >= posPtBarAvancement.y && event.motion.y < posPtBarAvancement.y + ptBarAvancement->h)
                {
                    ptBarAvancement = IMG_Load("dot_2_clic.png");
                    clicPointBarAvancement = 1;
                }
                if (event.motion.x >= posBarAvancement.x && event.motion.x < posBarAvancement.x + barAvancement->w && event.motion.y > posBarAvancement.y && event.motion.y < posBarAvancement.y + barAvancement->h)
                {
                    posPtBarAvancement.x = event.motion.x - (ptBarAvancement->w / 2);
                    clicPointBarAvancement = 1;
                }
                if (clicPointBarAvancement == 1)
                {
                    FMOD_Sound_GetLength(musique, &tempTempsTune, FMOD_TIMEUNIT_MS);
                    tempTempsPixel = tempTempsTune / 500;
                    tempsPixel = (posPtBarAvancement.x + (ptBarAvancement->w / 2) - posBarAvancement.x) * tempTempsPixel;
                    posSourisx = event.motion.x;
                    posSourisy = event.motion.y;
                    afficherTempsRecherche(ecran,tempsPixel,posSourisx,posSourisy);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (boolSouris == 1)
                {
                    dif = SDL_GetTicks();
                    if (dif - timSouris > 120)
                    {
                        if ((event.motion.x > 540 && event.motion.x < 770) && (event.motion.y > 35 && event.motion.y < 330))
                        {
                            if ((clic == 0) || (((event.motion.y - 35) / 20) != tuneChoisie))
                            {
                                tuneChoisie = ((event.motion.y - 35) / 20);
                                timClic = SDL_GetTicks();
                                clic = 1;
                            }
                            else
                            {
                                clic = 0;
                                if ((((event.motion.y - 35) / 20) == tuneChoisie) && (SDL_GetTicks() - timClic < 500))
                                {
                                    stopPress = 0;
                                    start = 0;
                                    FMOD_Channel_Stop(canal);
                                    lecture = 0;
                                    tuneAJouer = tuneChoisie;
                                    playBut = IMG_Load("Button-Pause-48.png");
                    				FMOD_System_GetMasterChannelGroup(system, &canal);
                                    FMOD_ChannelGroup_GetPaused(canal, &etat);
                                    if (etat)
                                    {
                                        FMOD_ChannelGroup_SetPaused(canalGen, 0);
                                    }
                                }
                            }
                        }
                        if (event.motion.x >= posBut[0].x + 7 && event.motion.x < posBut[0].x + playBut->w - 7 && event.motion.y >= posBut[0].y + 7 && event.motion.y < posBut[0].y + playBut->h - 7)
                        {
                            FMOD_System_GetMasterChannelGroup(system, &canal);
                            FMOD_ChannelGroup_GetPaused(canal, &etat);
                            if (start == 1)
                            {
                                tuneAJouer = 0;
                                lecture = 0;
                                tuneChoisie = tuneAJouer;
                            }
                            if (stopPress == 1)
                            {
                                tuneAJouer = tuneChoisie;
                                lecture = 0;
                            }
                            start = 0;
                            stopPress = 0;
                            if (lecture == 0)
                            {
                                playBut = IMG_Load("Button-Pause-48-red.png");
                            }
                            else
                            {
                                if (etat)
                                {
                                    playBut = IMG_Load("Button-Pause-48-red.png");
                                    FMOD_ChannelGroup_SetPaused(canalGen, 0);
                                }
                                else
                                {
                                    playBut = IMG_Load("Button-Play-48-red.png");
                                    FMOD_ChannelGroup_SetPaused(canalGen, 1);

                                }
                            }
                        }
                        if (event.motion.x >= posBut[1].x + 7 && event.motion.x< posBut[1].x + stopBut->w - 7 && event.motion.y >= posBut[1].y + 7 && event.motion.y < posBut[1].y + stopBut->h - 7)
                        {
                            stopBut = IMG_Load("Button-Stop-48-red.png");
                            playBut = IMG_Load("Button-Play-48.png");
                            lecture = 1;
                            spectre = 0;
                            stopPress = 1;
                            FMOD_Channel_Stop(canal);
                        }
                        if (event.motion.x >= posBut[2].x + 7 && event.motion.x< posBut[2].x + prevBut->w - 7 && event.motion.y >= posBut[2].y + 7 && event.motion.y < posBut[2].y + prevBut->h - 7)
                        {
                            prevBut = IMG_Load("Button-Previous-48-red.png");
                            FMOD_Channel_GetPosition(canal, &posInTune, FMOD_TIMEUNIT_MS);
                            if (posInTune > 2000)
                            {
                                FMOD_Channel_Stop(canal);
                                lecture = 0;
                            }
                            else
                            {
                                 if (tuneAJouer > 0)
                                {
                                    tuneChoisie--;
                                    FMOD_Channel_Stop(canal);
                                    lecture = 0;
                                    tuneAJouer-- ;
                                }
                            }
                        }
                        if (event.motion.x >= posBut[3].x + 7 && event.motion.x< posBut[3].x + nextBut->w - 7 && event.motion.y >= posBut[3].y + 7 && event.motion.y < posBut[3].y + nextBut->h - 7)
                        {
                            nextBut = IMG_Load("Button-Next-48-red.png");
                            if (tuneAJouer < nbrTunes - 1)
                            {
                                tuneChoisie++;
                                FMOD_Channel_Stop(canal);
                                lecture = 0;
                                tuneAJouer++ ;
                            }
                        }
                        if (event.motion.x >= posPointBarSound.x && event.motion.x < posPointBarSound.x + pointBarSound->w && event.motion.y >= posPointBarSound.y && event.motion.y < posPointBarSound.y + pointBarSound->h)
                        {
                            pointBarSound = IMG_Load("dot_2_green.png");
                            clicPointBarSound = 0;
                        }
                        if (clicPointBarSound == 1)
                        {
                            pointBarSound = IMG_Load("dot_2.png");
                            clicPointBarSound = 0;
                        }
                        if (clicPointBarAvancement == 1)
                        {
                            FMOD_Sound_GetLength(musique, &tempTempsTune, FMOD_TIMEUNIT_MS);
                            tempTempsPixel = tempTempsTune / 500;
                            tempsPixel = (posPtBarAvancement.x + (ptBarAvancement->w / 2) - posBarAvancement.x) * tempTempsPixel;
                            FMOD_Channel_SetPosition(canal, tempsPixel,FMOD_TIMEUNIT_MS );
                            ptBarAvancement = IMG_Load("dot_2.png");
                            clicPointBarAvancement = 0;
                        }
                        if (event.motion.x >= posPtBarAvancement.x && event.motion.x < posPtBarAvancement.x + ptBarAvancement->w && event.motion.y >= posPtBarAvancement.y && event.motion.y < posPtBarAvancement.y + ptBarAvancement->h)
                        {
                            ptBarAvancement = IMG_Load("dot_2_green.png");
                            clicPointBarAvancement = 0;
                        }
                    }
                    timSouris = SDL_GetTicks();
                    boolSouris = 0;
                }
                break;
        }

        timSpectre = SDL_GetTicks();
        SDL_FillRect(vSS,0,SDL_MapRGB(vSS->format,0,0,0));

        if (timSpectre - majSpectre < DELAI_RAFRAICHISSEMENT)
        {
            SDL_Delay(DELAI_RAFRAICHISSEMENT - (timSpectre - majSpectre));
        }
        majSpectre = timSpectre;

        // Lecture du morceau et affichage du spectre
        if (lecture == 0)
        {
            resultat = FMOD_System_CreateSound(system, tabTunes[tuneAJouer], FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
            tuneJouee = lectureMusique(system,musique,resultat,tuneAJouer,tabTunes,&tempsTune);
            lecture = 1;
            spectre = 1;
            posPtBarAvancement.x = posBarAvancement.x - (ptBarAvancement->w / 2);
            posPtBarAvancement.y = posBarAvancement.y - 2;
        }
        if (spectre == 1)
        {
            FMOD_System_GetChannel(system, 0, &canal);

            // Obtention du spectre et rangement dans un tableau de float en fonction de la fréquence
            FMOD_Channel_GetSpectrum(canal, spectreD, TAILLE_SPECTRE, 1,  FMOD_DSP_FFT_WINDOW_RECT);
            FMOD_Channel_GetSpectrum(canal, spectreG, TAILLE_SPECTRE, 0,  FMOD_DSP_FFT_WINDOW_RECT);

            // Affichage du spectre droit et gauche
            afficherSpectre(vSS,spectreD,spectreG);
        }

        // Gestion du son
        if (clicPointBarSound == 1)
        {
            tempUn = posPointBarSound.x;
            tempDeux = posBarSound.x;
            tempTrois = pointBarSound->w;
            volume = ((tempUn - tempDeux + (tempTrois / 2)) / 100);
            if ((event.motion.x > posBarSound.x) && (event.motion.x < (posBarSound.x + barSound->w)))
            {
                posPointBarSound.x = event.motion.x - (pointBarSound->w / 2);
            }
            if (event.motion.x > (posBarSound.x + barSound->w))
            {
                posPointBarSound.x = (posBarSound.x + barSound->w - (pointBarSound->w / 2));
                volume = 1.0;
            }
            if (event.motion.x < posBarSound.x)
            {
                posPointBarSound.x = posBarSound.x - (pointBarSound->w / 2);
                volume = 0.0;
            }
            FMOD_Channel_SetVolume(canal,volume);
        }
        afficherVolume(ecran,volume);

        // Gestion de l'avancement dans le morceau
        if (clicPointBarAvancement == 1)
        {
            if ((event.motion.x > posBarAvancement.x) && (event.motion.x < (posBarAvancement.x + barAvancement->w)))
            {
                posPtBarAvancement.x = event.motion.x - (ptBarAvancement->w / 2);
            }
            if (event.motion.x > (posBarAvancement.x + barAvancement->w))
            {
                posPtBarAvancement.x = (posBarAvancement.x + barAvancement->w - (ptBarAvancement->w / 2));
            }
            if (event.motion.x < posBarAvancement.x)
            {
                posPtBarAvancement.x = posBarAvancement.x - (ptBarAvancement->w / 2);
            }
        }

        // Affichage du titre et de l'artiste du morceau
        if ((start != 1) && (stopPress != 1))
        {
            FMOD_Sound_GetTag(musique,"ARTIST",-1,&tag);
            FMOD_Sound_GetTag(musique,"TITLE",-1,&tag2);
            tagArtist = (char *)tag.data;
            tagName = (char *)tag2.data;
            if (tag2.datalen >= 32)
            {
                sprintf(tempTuneName,"%s",tabTunes[tuneJouee]);
                i = 499;
                while (i > 3)
                {
                    if (tempTuneName[i] == '3')
                    {
                        if (tempTuneName[i - 1] == 'p')
                        {
                            if (tempTuneName[i - 2] == 'm')
                            {
                                if (tempTuneName[i - 3] == '.')
                                {
                                    tempTuneName[i - 3] = '\0';
                                    i = 2;
                                }
                            }
                        }
                    }
                    i--;
                }
                sprintf(tempTuneName,"%s - %s",tempTuneName, tagArtist);
            }
            else
            {
                sprintf(tempTuneName,"%s - %s",tagName, tagArtist);
            }
            tuneName = TTF_RenderText_Blended(police, tempTuneName, couleurRouge);
            SDL_BlitSurface(tuneName,0,ecran,&posTuneName);
        }

        // Passage au morceau suivant à la fin du morceau en cours
        FMOD_Channel_GetPosition(canal, &posInTune, FMOD_TIMEUNIT_MS);
        if (start != 1)
        {
            if ((posInTune == tempsTune) && (tuneAJouer == nbrTunes - 1))
            {
                FMOD_Channel_Stop(canal);
                playBut = IMG_Load("Button-Play-48.png");
                lecture = 1;
                spectre = 0;
                stopPress = 1;
                tempsTune = 0;
            }
            else
            {
                if (posInTune == tempsTune)
                {
                    FMOD_Channel_Stop(canal);
                    tuneChoisie = tuneJouee + 1;
                    lecture = 0;
                }
            }
        }

        // Affichage de la durée du morceau et de l'avancement
        if ((stopPress != 1) && (start != 1))
        {
            afficherTemps(ecran,tempsTune,canal);
        }

        SDL_BlitSurface(vSS,0,ecran,&posVSS);
        SDL_BlitSurface(playBut,0,ecran,&posBut[0]);
        SDL_BlitSurface(stopBut,0,ecran,&posBut[1]);
        SDL_BlitSurface(prevBut,0,ecran,&posBut[2]);
        SDL_BlitSurface(nextBut,0,ecran,&posBut[3]);
        SDL_BlitSurface(barSound,0,ecran,&posBarSound);
        SDL_BlitSurface(pointBarSound,0,ecran,&posPointBarSound);
        SDL_BlitSurface(barAvancement,0,ecran,&posBarAvancement);
        SDL_BlitSurface(ptBarAvancement,0,ecran,&posPtBarAvancement);
        SDL_Flip(ecran);

        // Déplacement du point de la barre d'avancement en fonction du temps
        if ((clicPointBarAvancement != 1) && (start != 1))
        {
            posPtBarAvancement.x = (deplacementPtBarAvancement(canal, musique) + posBarAvancement.x - (ptBarAvancement->w / 2));
        }

        // Temporisation afin de soulager le processeur
        SDL_Delay(15);
    }

	FMOD_Sound_Release(musique);
	FMOD_System_Close(system);
	FMOD_System_Release(system);
	SDL_FreeSurface(vSS);
	SDL_FreeSurface(liste);
    SDL_Quit();

    return(0);
}




