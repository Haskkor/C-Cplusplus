#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>


int main ( int argc, char** argv )
{
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("Snake",NULL);
    SDL_WM_SetIcon(IMG_Load("joy_ico.png"),NULL);

    // Création d'un enregistrement contenant pour chaque partie du serpent, sa position en X, en Y et sa direction.
    typedef struct tabSnake tabSnake;
    struct tabSnake
    {
        int sI;
        int sY;
        int sChoix;
    };

    SDL_Surface *ecran = SDL_SetVideoMode(640, 480, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);

    // Ouverture de la police.
    TTF_Font *police = NULL;
    TTF_Font *policeAcc = NULL;
    police = TTF_OpenFont("gameretro.ttf", 90);
    policeAcc = TTF_OpenFont("gamefutur.ttf",18);

    SDL_Color couleurRouge = {255,0,0};
    FILE *fichier = NULL;
    SDL_Surface *snakeR = IMG_Load("globe_R.gif");
    SDL_Surface *snakeU = IMG_Load("globe_U.gif");
    SDL_Surface *snakeD = IMG_Load("globe_D.gif");
    SDL_Surface *snakeL = IMG_Load("globe_L.gif");
    SDL_Surface *bol = IMG_Load("bol.gif");
    SDL_Surface *fond = IMG_Load("snake.jpg");
    SDL_Surface *mur = IMG_Load("puce.gif");
    SDL_Surface *texte = TTF_RenderText_Blended(police, "Vous avez termine le niveau!", couleurRouge);
    SDL_Surface *texteAcc;
    SDL_Event event,event2;
    SDL_Rect posSnake,posBol,posMur,posTexte;

    int compteur = 0,nbrLvl = 0,lvlEnCours = 1,choixLvl = 0,continuer = 1,platJeu[48][64],i = 0,j = 0,tpsNow = 0,tpsBfr = 0,sX = 0,sY = 0,choix = '4',tailleSnake = 3,cheminSnake[100],k = tailleSnake,vitesse = 100,tempsBolBfr = 0,bolX = 0,bolY = 0,parcours = 0,bolBool = 0,perdu = 0;
    tabSnake tablSnake[200];

    // Ouverture du fichier des niveaux.
    fichier = fopen("niveaux.txt","r");

    // Initialisation du plateau.
    while (parcours != EOF)
    {
        parcours = fgetc(fichier);
        if (parcours == '\n')
            {
                nbrLvl++;
            }
    }

    // Message d'accueil.
    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));
    texteAcc = TTF_RenderText_Blended(policeAcc, "The motherfucking SNAKE eating ramen", couleurRouge);
    posTexte.x = ecran->w / 2 - texteAcc->w / 2;
    posTexte.y = ecran->h / 2 - texteAcc->h / 2;
    SDL_BlitSurface(texteAcc,0,ecran,&posTexte);
    SDL_Flip(ecran);
    SDL_Delay(5000);

    // Boucle principale.
    while (lvlEnCours < nbrLvl)
    {
        // Initialisation de la position du serpent.
        sX = 10;
        sY = 10;
        platJeu[sX][sY] = '4';
        choix = '4';

        choixLvl = lvlEnCours;
        rewind(fichier);
        while (choixLvl > 0)
        {
            parcours = fgetc(fichier);
            if (parcours == '\n')
                {
                        choixLvl--;
                }
        }
        parcours = '0';
        i = 0;
        j = 0;
        for (i=0;i<48;i++)
        {
            j = 0;
            for (j=0;j<64;j++)
            {
                parcours = fgetc(fichier);
                platJeu[i][j] = parcours;
            }
        }

        // Vérifie si le joueur a perdu ou non et peut donc continuer.
        if (perdu == 0)
        {
            continuer = 1;
        }

        // Boucle de jeu par niveau.
        while (continuer == 1)
        {
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;
                    case SDL_KEYDOWN:
                        {
                            switch (event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE :
                                    continuer = 0;
                                    break;
                                case SDLK_UP :
                                    if (choix != '2')
                                    {
                                        choix = '1';
                                    }
                                    break;
                                case SDLK_DOWN :
                                    if (choix != '1')
                                    {
                                        choix = '2';
                                    }
                                    break;
                                case SDLK_LEFT :
                                    if (choix != '4')
                                    {
                                        choix = '3';
                                    }
                                    break;
                                case SDLK_RIGHT :
                                    if (choix != '3')
                                    {
                                        choix = '4';
                                    }
                                    break;
                            }
                            break;
                        }
                }
            }

            // Gestion du temps.
            tpsNow = SDL_GetTicks();
            if (tpsNow - tpsBfr > vitesse)
            {
                // Gestion des bols de nourriture.
                compteur++;
                if ((bolBool == 0) || (compteur * vitesse == 12000))
                {
                    srand(time(NULL));
                    do
                    {
                        bolX = (rand() % 63);
                        bolY = (rand() % 47);
                    }
                    while (platJeu[bolY][bolX] != '0');
                    platJeu[bolY][bolX] = '5';
                    posBol.x = bolX * 10;
                    posBol.y = bolY * 10;
                    bolBool = 1;
                    compteur = 0;
                }

                // Initialisation de la deuxième "boule" du serpent.
                tablSnake[0].sI = sX;
                tablSnake[0].sY = sY;
                tablSnake[0].sChoix = platJeu[sX][sY];

                // Enregistrement des déplacements du serpent dans un tableau. Le premier élément décale tous les autres vers l'arrière.
                k = tailleSnake;
                while (k > 1)
                {
                    cheminSnake[k] = cheminSnake[k - 1];
                    k--;
                }

                cheminSnake[1] = tablSnake[0].sChoix;

                // Insertion des déplacements du serpent dans le plateau de jeu.
                for (i=1;i<tailleSnake;i++)
                {
                    platJeu[tablSnake[i].sI][tablSnake[i].sY] = cheminSnake[i + 1];
                    tablSnake[i].sChoix = cheminSnake[i + 1];
                }

                // Placement des parties du serpent en fonction de la partie précédente.
                for (i=1;i<tailleSnake+1;i++)
                {
                    switch (tablSnake[i-1].sChoix)
                    {
                        case '1' :
                            tablSnake[i].sY = tablSnake[i-1].sY;
                            if (tablSnake[i-1].sI == 47)
                            {
                                tablSnake[i].sI = 0;
                            }
                            else
                            {
                                tablSnake[i].sI = tablSnake[i-1].sI + 1;
                            }
                            break;
                        case '2' :
                            tablSnake[i].sY = tablSnake[i-1].sY;
                            if (tablSnake[i-1].sI == 0)
                            {
                                tablSnake[i].sI = 47;
                            }
                            else
                            {
                                tablSnake[i].sI = tablSnake[i-1].sI - 1;
                            }
                            break;
                        case '3' :
                            tablSnake[i].sI = tablSnake[i-1].sI;
                            if (tablSnake[i-1].sY == 63)
                            {
                                tablSnake[i].sY = 0;
                            }
                            else
                            {
                                tablSnake[i].sY = tablSnake[i-1].sY + 1;
                            }
                            break;
                        case '4' :
                            tablSnake[i].sI = tablSnake[i-1].sI;
                            if (tablSnake[i-1].sY == 0)
                            {
                                tablSnake[i].sY = 63;
                            }
                            else
                            {
                                tablSnake[i].sY = tablSnake[i-1].sY - 1;
                            }
                            break;
                    }
                }

                // Gestion du déplacement du serpent en prenant en compte l'arrivée sur une extrémité du plateau, les collisions et
                // les bols.
                switch (choix)
                {
                    case '1' :
                        if (sX == 0)
                        {
                            platJeu[sX][sY] = '0';
                            sX = 47;
                            platJeu[sX][sY] = choix;
                        }
                        else
                        {
                            if ((platJeu[sX - 1][sY] == '1') || (platJeu[sX - 1][sY] == '2') || (platJeu[sX - 1][sY] == '3') || (platJeu[sX - 1][sY] == '4') || (platJeu[sX - 1][sY] == '6'))
                            {
                                perdu = 1;
                                continuer = 0;
                            }
                            else
                            {
                                if (platJeu[sX - 1][sY] == '5')
                                {
                                    tailleSnake++;
                                    if (tailleSnake % 10 == 0)
                                    {
                                        vitesse = vitesse - 10;
                                    }
                                    platJeu[sX - 1][sY] = choix;
                                    platJeu[sX][sY] = '0';
                                    sX--;
                                    bolBool = 0;
                                }
                                else
                                {
                                    platJeu[sX - 1][sY] = choix;
                                    platJeu[sX][sY] = '0';
                                    sX--;
                                }
                            }
                        }
                        break;
                    case '2' :
                        if (sX == 47)
                        {
                            platJeu[sX][sY] = '0';
                            sX = 0;
                            platJeu[sX][sY] = choix;
                        }
                        else
                        {
                            if ((platJeu[sX + 1][sY] == '1') || (platJeu[sX + 1][sY] == '2') || (platJeu[sX + 1][sY] == '3') || (platJeu[sX + 1][sY] == '4') || (platJeu[sX + 1][sY] == '6'))
                            {
                                perdu = 1;
                                continuer = 0;
                            }
                            else
                            {
                                if (platJeu[sX + 1][sY] == '5')
                                {
                                    tailleSnake++;
                                    if (tailleSnake % 10 == 0)
                                    {
                                        vitesse = vitesse - 10;
                                    }
                                    platJeu[sX + 1][sY] = choix;
                                    platJeu[sX][sY] = '0';
                                    sX++;
                                    bolBool = 0;
                                }
                                else
                                {
                                    platJeu[sX + 1][sY] = choix;
                                    platJeu[sX][sY] = '0';
                                    sX++;
                                }
                            }
                        }
                        break;
                    case '3' :
                        if (sY == 0)
                        {
                            platJeu[sX][sY] = '0';
                            sY = 63;
                            platJeu[sX][sY] = choix;
                        }
                        else
                        {
                            if ((platJeu[sX][sY - 1] == '1') || (platJeu[sX][sY - 1] == '2') || (platJeu[sX][sY - 1] == '3') || (platJeu[sX][sY - 1] == '4') || (platJeu[sX][sY - 1] == '6'))
                            {
                                perdu = 1;
                                continuer = 0;
                            }
                            else
                            {
                                if (platJeu[sX][sY - 1] == '5')
                                {
                                    tailleSnake++;
                                    if (tailleSnake % 10 == 0)
                                    {
                                        vitesse = vitesse - 10;
                                    }
                                    platJeu[sX][sY - 1] = choix;
                                    platJeu[sX][sY] = '0';
                                    sY--;
                                    bolBool = 0;
                                }
                                else
                                {
                                    platJeu[sX][sY - 1] = choix;
                                    platJeu[sX][sY] = '0';
                                    sY--;
                                }
                            }
                        }
                        break;
                    case '4' :
                        if (sY == 63)
                        {
                            platJeu[sX][sY] = '0';
                            sY = 0;
                            platJeu[sX][sY] = choix;
                        }
                        else
                        {
                            if ((platJeu[sX][sY + 1] == '1') || (platJeu[sX][sY + 1] == '2') || (platJeu[sX][sY + 1] == '3') || (platJeu[sX][sY + 1] == '4') || (platJeu[sX][sY + 1] == '6'))
                            {
                                perdu = 1;
                                continuer = 0;
                            }
                            else
                            {
                                if (platJeu[sX][sY + 1] == '5')
                                {
                                    tailleSnake++;
                                    if (tailleSnake % 10 == 0)
                                    {
                                        vitesse = vitesse - 10;
                                    }
                                    platJeu[sX][sY + 1] = choix;
                                    platJeu[sX][sY] = '0';
                                    sY++;
                                    bolBool = 0;
                                }
                                else
                                {
                                    platJeu[sX][sY + 1] = choix;
                                    platJeu[sX][sY] = '0';
                                    sY++;
                                }
                            }
                        }
                        break;
                }

                // Effacement du serpent sur les cases dont il est sorti.
                platJeu[tablSnake[0].sI][tablSnake[0].sY] = tablSnake[0].sChoix;
                tablSnake[tailleSnake].sChoix = '0';
                platJeu[tablSnake[tailleSnake].sI][tablSnake[tailleSnake].sY] = tablSnake[tailleSnake].sChoix;

                tpsBfr = tpsNow;
            }
            else
            {
                SDL_Delay(vitesse - (tpsNow - tpsBfr));
            }

            SDL_FillRect(ecran, 0, SDL_MapRGB(ecran->format, 100, 100, 100));
            SDL_BlitSurface(fond,0,ecran,0);

            // Blit des différentes parties.
            for (i=0;i<48;i++)
            {
                j = 0;
                for (j=0;j<64;j++)
                {
                    posSnake.x = j * 10;
                    posSnake.y = i * 10;
                    posMur.x = j * 10;
                    posMur.y = i * 10;
                    switch (platJeu[i][j])
                    {
                        case '1' :
                            SDL_BlitSurface(snakeU,0,ecran,&posSnake);
                            break;
                        case '2' :
                            SDL_BlitSurface(snakeD,0,ecran,&posSnake);
                            break;
                        case '3' :
                            SDL_BlitSurface(snakeL,0,ecran,&posSnake);
                            break;
                        case '4' :
                            SDL_BlitSurface(snakeR,0,ecran,&posSnake);
                            break;
                        case '5' :
                            SDL_BlitSurface(bol,0,ecran,&posBol);
                            break;
                        case '6' :
                            SDL_BlitSurface(mur,0,ecran,&posMur);
                            break;
                    }
                }
            }
            SDL_Flip(ecran);

            // Passage au niveau supérieur.
            if (tailleSnake == 85)
            {
                lvlEnCours++;
                tailleSnake = 3;
                vitesse = 100;
                continuer = 0;
                continuer = 0;

                // Affichage d'un message quand le niveau est gagné.
                SDL_FillRect(ecran, 0, SDL_MapRGB(ecran->format, 100, 100, 100));
                SDL_BlitSurface(fond,0,ecran,0);
                posTexte.x = ecran->w / 2 - texte->w / 2;
                posTexte.y = ecran->h / 2 - texte->h / 2;
                SDL_BlitSurface(texte,0,ecran,&posTexte);
                SDL_Flip(ecran);
                SDL_Delay(4000);
            }
        }
    }

    SDL_FreeSurface(snakeU);
    SDL_FreeSurface(snakeD);
    SDL_FreeSurface(snakeL);
    SDL_FreeSurface(snakeR);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(bol);
    TTF_CloseFont(police);
    TTF_Quit();

    return 0;

}
