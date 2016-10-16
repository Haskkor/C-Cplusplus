#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

void jouer(SDL_Surface *ecran);

void bliterPlateau(int platJeu[12][12],SDL_Rect position,int *xMario,int *yMario,SDL_Surface *ecran,SDL_Surface *mur,SDL_Surface *caisse,SDL_Surface *objectif,SDL_Surface *mario,SDL_Surface *caisseOK);
