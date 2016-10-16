#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "SP.h"


char lireCaractere()
{
    char lettreJoueur = 0;
    lettreJoueur = getchar();
    lettreJoueur = toupper(lettreJoueur);
    while (getchar() != '\n');
    return lettreJoueur ;
}

void verifierMot(const char lettreJoueur, const char motSecret[], char *motCache, int *pointNbrCoups, int tailleMot)
{
    int i = 0 ;
    int bon = 0 ;
    while (i <= tailleMot)
           {
               if (motSecret[i] == lettreJoueur)
                    {
                        motCache[i] = lettreJoueur;
                        bon = 1 ;
                    }
               i++;
           }
    if (bon == 0)
        {
            *pointNbrCoups = *pointNbrCoups - 1;
        }
}

int partieGagnee(const char *motCache,int tailleMot)
{
    int i = 0;
    while ((motCache[i] != '*') && (i <= tailleMot))
        {
            i++;
        }
    if (i > tailleMot)
        {
            return(1);
        }
    else
        {
            return(0);
        }
}

void remplirMotCache(char *motCache, int tailleMot)
{
    int i = 0;
    while (i < tailleMot)
        {
            motCache[i] = '*';
            i++;
        }
    motCache[i] = '.';
}



