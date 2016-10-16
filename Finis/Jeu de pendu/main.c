#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "SP.h"
#include "dico.h"


int main()
{
    char motSecret[50] = {0}; // Mot à trouver.
    int nbrCoups = 8 ; // Nombre de chances qu'il reste au joueur.
    char lettreJoueur = 0; // Lettre que le joueur propose.
    char *motCache = NULL; // Mot affiché en étoile.
    int gagne = 0 ; // Variable indiquant si le joueur a gagné ou pas.
    int tailleMot = 0; // Taille du mot choisit.
    int i = 0 ;

    printf("Bonjour.\nBienvenue dans le pendu.\nVous disposez de 8 essais pour trouver le mot cache.\nMerci de ne pas utiliser d'accents et de ne rentrer que des majuscules.\n");

    if (piocherMot(motSecret) == 0)
        {
            printf("Impossible de choisir un mot.");
            exit(0);
        }
    tailleMot = strlen(motSecret) ;
    motCache = malloc(tailleMot * sizeof(char));
    remplirMotCache(motCache,tailleMot);
    while ((nbrCoups > 0) && (gagne != 1))
        {
            printf("\n\nMot secret : ");
            i = 0 ;
            while (i <= tailleMot)
                {
                    printf("%c",motCache[i]);
                    i++;
                }
            printf("\nIl vous reste %d chances avant de perdre.\n",nbrCoups);
            printf("Proposez une lettre : ");
            lettreJoueur = lireCaractere();
            verifierMot(lettreJoueur,motSecret,motCache,&nbrCoups,tailleMot);
            gagne = (partieGagnee(motCache,tailleMot)) ;
        }

    if (nbrCoups == 0)
        {
            printf("\n\nVous avez perdu. Mot secret : %s.\n\n",motSecret);
        }
    else
        {
            printf("\n\nVous avez gagne. Mot secret : %s.\n\n",motSecret);
        }

    return (0);
}
