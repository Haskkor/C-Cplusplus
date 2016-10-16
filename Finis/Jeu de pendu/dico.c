#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dico.h"


int piocherMot(char *motChoisi)
{
    int nbrDeMots = 0,numeroDeMot = 0;
    int charEnCours = 0;
    FILE *dico = NULL;
    dico = fopen("C:\\Documents and Settings\\CER3100426\\Mes documents\\PRIVE\\C\\Jeu de pendu\\pli07.txt", "r");
    if (dico == NULL)
        {
            return (0);
        }
    while (charEnCours != EOF)
        {
            charEnCours = fgetc(dico);
            if (charEnCours == '\n')
                {
                    nbrDeMots++;
                }
        }
    numeroDeMot = nombreAleatoire(nbrDeMots);
    rewind(dico);
    while (numeroDeMot > 0)
        {
            charEnCours = fgetc(dico);
            if (charEnCours == '\n')
                {
                    numeroDeMot--;
                }
        }
    fgets(motChoisi,50,dico);
    motChoisi[strlen(motChoisi) - 1] = '\0';
    fclose(dico);
    return (1);
}

int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}


