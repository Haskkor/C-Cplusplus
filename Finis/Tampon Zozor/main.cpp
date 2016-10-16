#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

void initialiserPositions(SDL_Rect positionImages[100]);

void bliterFond (SDL_Surface *ecran, SDL_Surface *fond, int choixFond, SDL_Rect posFond);

void bliterImages (SDL_Rect positionImages[100],SDL_Surface *ecran,SDL_Surface *zozor,SDL_Surface *sapin,SDL_Surface *noel,SDL_Surface *smiley,int choix, int tabChoix[100]);

void bliterCurseur (SDL_Rect posImg, SDL_Surface *ecran,SDL_Surface *zozor,SDL_Surface *sapin,SDL_Surface *noel,SDL_Surface *smiley,int choix);

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *zozor = NULL, *sapin = NULL, *noel = NULL, *smiley = NULL, *fond = NULL;
    SDL_Event event;
    SDL_Rect positionImages[100], posImg, posFond;
    int continuer = 1, rang = 0,choix = 1,choixFond = 1,tabChoix[100] = {0};

    ecran = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    sapin = IMG_Load("sapin.png");
    zozor = SDL_LoadBMP("zozor.bmp");
    smiley = IMG_Load("smiley.png");
    noel = IMG_Load("noel.png");
    fond = IMG_Load("fond.bmp");

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,50,50,50));
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format,0,0,255));
    SDL_ShowCursor(SDL_DISABLE);

    initialiserPositions(positionImages);
    posFond.x = 0;
    posFond.y = 0;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_VIDEORESIZE :
                ecran = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
                SDL_Flip(ecran);
                break;
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                        continuer = 0;
                        break;
                    case SDLK_DELETE :
                        initialiserPositions(positionImages);
                        rang = 0;
                        break;
                    case SDLK_KP1 :
                        choix = 1;
                        break;
                    case SDLK_KP2 :
                        choix = 2;
                        break;
                    case SDLK_KP3 :
                        choix = 3;
                        break;
                    case SDLK_KP4 :
                        choix = 4;
                        break;
                    case SDLK_1 :
                        choixFond = 1;
                        break;
                    case SDLK_2 :
                        choixFond = 2;
                        break;
                    case SDLK_3 :
                        choixFond = 3;
                        break;
                    case SDLK_4 :
                        choixFond = 4;
                        break;
                }
                break;
            case SDL_MOUSEMOTION :
                posImg.x = event.motion.x;
                posImg.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONUP :
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (rang < 100)
                    {
                    positionImages[rang].x = event.button.x;
                    positionImages[rang].y = event.button.y;
                    tabChoix[rang] = choix;
                        rang++;
                    }
                }
        }
        bliterFond(ecran,fond,choixFond,posFond);
        bliterCurseur(posImg,ecran,zozor,sapin,noel,smiley,choix);
        bliterImages(positionImages,ecran,zozor,sapin,noel,smiley,choix,tabChoix);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_FreeSurface(smiley);
    SDL_FreeSurface(sapin);
    SDL_FreeSurface(noel);
    SDL_Quit();

    EXIT_SUCCESS;

}

void bliterFond (SDL_Surface *ecran, SDL_Surface *fond, int choixFond, SDL_Rect posFond)
{
    switch (choixFond)
    {
        case 1 :
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,50,50,50));
            break;
        case 2 :
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
            break;
        case 3 :
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            break;
        case 4 :
            SDL_BlitSurface(fond,NULL,ecran,&posFond);
            break;
    }
}

void initialiserPositions (SDL_Rect positionImages[100])
{
    int i = 0 ;

    for (i=0;i<100;i++)
    {
        positionImages[i].x = -1;
        positionImages[i].y = -1;
    }
}

void bliterCurseur (SDL_Rect posImg, SDL_Surface *ecran,SDL_Surface *zozor,SDL_Surface *sapin,SDL_Surface *noel,SDL_Surface *smiley,int choix)
{
    switch(choix)
    {
        case 1 :
            SDL_BlitSurface(zozor,NULL,ecran,&posImg);
            break;
        case 2 :
            SDL_BlitSurface(sapin,NULL,ecran,&posImg);
            break;
        case 3 :
            SDL_BlitSurface(noel,NULL,ecran,&posImg);
            break;
        case 4 :
            SDL_BlitSurface(smiley,NULL,ecran,&posImg);
            break;
    }
}

void bliterImages (SDL_Rect positionImages[100],SDL_Surface *ecran,SDL_Surface *zozor,SDL_Surface *sapin,SDL_Surface *noel,SDL_Surface *smiley,int choix, int tabChoix[100])
{
    int i = 0 ;

    for (i=0;i<100;i++)
    {
        if ((positionImages[i].x > -1) && (positionImages[i].y > -1))
        {
            switch (tabChoix[i])
            {
                case 1 :
                    SDL_BlitSurface(zozor,NULL,ecran,&positionImages[i]);
                    break;
                case 2 :
                    SDL_BlitSurface(sapin,NULL,ecran,&positionImages[i]);
                    break;
                case 3 :
                    SDL_BlitSurface(noel,NULL,ecran,&positionImages[i]);
                    break;
                case 4 :
                    SDL_BlitSurface(smiley,NULL,ecran,&positionImages[i]);
                    break;
            }
        }
    }
}
