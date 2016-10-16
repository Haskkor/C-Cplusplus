#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sous-programmes.h"


int main()
{
    int choix = 0, temp = 0, resultat = 0,n = 0,p = 0;
    char chTemp[TAILLE_MAX];
    Indicateur succes;
    ChaineDyn ch1, ch2;
    bool continuer = true;

    // Boucle principale.
    while(continuer == true)
    {
        succes = -1;
        printf("\n\n0 - Quitter.\n1 - Afficher la chaine.\n2 - Convertir une chaine.\n3 - Longueur de la chaine.\n4 - Copier la ");
        printf("chaine.\n5 - Concatener les chaines.\n6 - Extraire une partie de la chaine.\n7 - Comparer les chaines.\n8 - Copier ");
        printf("la sous chaine.\n9 - Concatener la sous chaine.\n10 - Comparer les sous chaines.\n");
        printf("\nEntrez votre choix : ");
        choix = lireChiffre();
        // Switch du choix de l'utilisateur.
        switch(choix)
        {
            case 0 :
                // Quitter.
                continuer = false;
                break;
            case 1 :
                // Afficher la chaîne.
                creerChaineVide(&ch1);
                printf("\nEntrez une chaine a afficher : ");
                lireChaine(&ch1);
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                break;
            case 2 :
                // Convertir une chaîne.
                creerChaineVide(&ch1);
                printf("\nEntrez une chaine a convertir : ");
                scanf("%s",chTemp);
                convertirChaine(&ch1,&chTemp,&succes);
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                // Vide le buffer clavier.
                purger();
                break;
            case 3 :
                // Longueur de la chaîne.
                creerChaineVide(&ch1);
                printf("\nEntrez une chaine dont vous voulez connaitre la taille : ");
                lireChaine(&ch1);
                temp = longueurChaine(ch1);
                printf("\nVotre chaine fait %d caracteres.",temp);
                break;
            case 4 :
                // Copier la chaîne.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez une chaine a copier : ");
                lireChaine(&ch2);
                copierChaine(&ch1,ch2,&succes);
                printf("\nVoici le resultat de la copie : ");
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                libererChaine(&ch2);
                break;
            case 5 :
                // Concaténer les chaînes.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez la chaine qui sera fixe : ");
                lireChaine(&ch1);
                printf("\nEntrez la chaine qui sera collee a la premiere : ");
                lireChaine(&ch2);
                collerChaine(&ch1,ch2,&succes);
                printf("\nVoici le resultat de la concatenation : ");
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                libererChaine(&ch2);
                break;
            case 6 :
                // Extraire une partie de la chaîne.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez la chaine qui sera fixe : ");
                lireChaine(&ch2);
                printf("\nEntrez le nombre de caracteres a garder : ");
                n = lireChiffre();
                printf("\nEntrez la position de depart de la sous chaine : ");
                p = lireChiffre();
                printf("%s",ch2.ptrCar);
                extraireSousChaine(&ch1,ch2,p,n,&succes);
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                libererChaine(&ch2);
                break;
            case 7 :
                // Comparer les chaînes.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez la premiere chaine : ");
                lireChaine(&ch1);
                printf("\nEntrez la deuxieme chaine : ");
                lireChaine(&ch2);
                resultat = comparerChaine(ch1,ch2);
                // Switch du résultat de la comparaison.
                switch(resultat)
                {
                    case 0 :
                        printf("\nLes chaines sont identiques.");
                        break;
                    case 1 :
                        printf("\nLa premiere chaine est superieure a la seconde.");
                        break;
                    case -1 :
                        printf("\nLa seconde chaine est superieure a la premiere.");
                        break;
                }
                break;
            case 8 :
                // Copier la sous chaîne.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez une chaine de depart : ");
                lireChaine(&ch2);
                printf("\nEntrez le nombre de caracteres a garder : ");
                n = lireChiffre();
                copierSousChaine(&ch1,ch2,n,&succes);
                printf("\nVoici le resultat de la copie : ");
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                libererChaine(&ch2);
                break;
            case 9 :
                // Concaténer la sous chaîne.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez la chaine qui sera fixe : ");
                lireChaine(&ch1);
                printf("\nEntrez la chaine dont une partie sera collee a la premiere chaine : ");
                lireChaine(&ch2);
                printf("\nEntrez le nombre de caracteres a concatener : ");
                n = lireChiffre();
                collerSousChaine(&ch1,ch2,n,&succes);
                printf("\nVoici le resultat de la concatenation : ");
                afficherChaineDyn(&ch1);
                libererChaine(&ch1);
                libererChaine(&ch2);
                break;
            case 10 :
                // Comparer les sous chaînes.
                creerChaineVide(&ch1);
                creerChaineVide(&ch2);
                printf("\nEntrez la premiere chaine : ");
                lireChaine(&ch1);
                printf("\nEntrez la deuxieme chaine : ");
                lireChaine(&ch2);
                printf("\nEntrez le nombre de caracteres a comparer : ");
                n = lireChiffre();
                resultat = comparerSousChaine(ch1,ch2,n,&succes);
                // Switch du résultat de la comparaison.
                switch(resultat)
                {
                    case 0 :
                        printf("\nLes chaines sont identiques.");
                        break;
                    case 1 :
                        printf("\nLa premiere chaine est superieure a la seconde.");
                        break;
                    case -1 :
                        printf("\nLa seconde chaine est superieure a la premiere.");
                        break;
                    default :
                        break;
                }
                break;
            default :
                printf("\nErreur de saisie.\n");
                break;
        }
        switch(succes)
        {
            case 0 :
                printf("\n\nErreur de paramètre. Veuillez recommencer.\nAppuyez sur une touche pour continuer.\n\n");
                getchar();
                break;
            case 1 :
                printf("\n\nErreur d'allocation. Veuillez recommencer.\nAppuyez sur une touche pour continuer.\n\n");
                getchar();
                break;
        }
    }

    return(0);
}









