#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sous-programmes.h"




void creerChaineVide(ChaineDyn *ch)
{
    ch->nbCar = 0;
    ch->ptrCar = calloc(TAILLE_MAX , sizeof(char));

    return;
}




int lireChiffre()
{
    char tampon[TAILLE_MAX];
    int i = 0;

    fgets(tampon,5,stdin);
    while (sscanf(tampon,"%d",&i) != 1)
    {
        printf("Erreur de saisie, recommencez : ");
        fgets(tampon,5,stdin);
    }

    return(atoi(tampon));
}




void lireChaine(ChaineDyn *ch)
{
    int dernier = 0, i = 0;
    char chips[TAILLE_MAX];


    fgets(chips,TAILLE_MAX,stdin);
    dernier = strlen(chips) - 1;
    if (chips[dernier] == '\n')
    {
        chips[dernier] = '\0';
    }
    ch->nbCar = dernier;
    for (i=0;i<ch->nbCar;i++)
    {
        ch->ptrCar[i] = chips[i];
    }

    return;
}




void afficherChaineDyn (const ChaineDyn *ch)
{
    int i;                  // Indice de parcours.

    printf("\nVotre chaine fait %d caracteres.\n",ch->nbCar);
    printf("L'adresse de votre chaine est %d.\n",ch->ptrCar);
    printf("Le contenu de votre chaine est : ");
    for (i = 0;i<ch->nbCar;i++)
    {
        printf("%c",ch->ptrCar[i]);
    }
    printf(".\n");

    return;
}




void libererChaine(ChaineDyn *ch)
{
    free(ch->ptrCar);
    ch->nbCar = 0;
    ch->ptrCar = NULL;

    return;
}




void purger()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {}
}




int longueurChaine(const ChaineDyn ch)
{
    return(ch.nbCar);
}




void copierBlocOctets(PointeurCar ptrAlloc,char *ch2,int lgch2)
{
    int i;

    for (i = 0;i<lgch2;i++)
    {
        ptrAlloc[i] = ch2[i];
    }

    return;
}




void convertirChaine(ChaineDyn *ch1, const char *ch2, Indicateur *succes)
{
    int lgCh2;              // Longueur de la chaîne ch2
    PointeurCar ptrAlloc;   // Pointeur sur le bloc d'octets alloué dynamiquement pour stocker la nouvelle chaîne

    lgCh2 = strlen(ch2);
    if (lgCh2 == 0)
    {
        ptrAlloc = NULL;
    }
    else
    {
        ptrAlloc = malloc(lgCh2 * sizeof(char));
        if (ptrAlloc == NULL)
        {
            *succes = ERR_ALLOC;
            return;
        }
        copierBlocOctets(ptrAlloc,ch2,lgCh2);
    }
    if (ch1->ptrCar != NULL)
    {
        free(ch1->ptrCar);
    }
    ch1->nbCar = lgCh2;
    ch1->ptrCar = ptrAlloc;

    return;
}




void copierChaine(ChaineDyn *ch1, const ChaineDyn ch2, Indicateur *succes)
{
    int lgCh2;              // Longueur de la chaîne ch2
    PointeurCar ptrAlloc;   // Pointeur sur le bloc d'octets alloué dynamiquement pour stocker la nouvelle chaîne

    lgCh2 = ch2.nbCar;
    if (lgCh2 == 0)
    {
        ptrAlloc = NULL;
    }
    else
    {
        ptrAlloc = malloc(lgCh2 * sizeof(char));
        if (ptrAlloc == NULL)
        {
            *succes = ERR_ALLOC;
            return;
        }
        copierBlocOctets(ptrAlloc,ch2.ptrCar,lgCh2);
    }
    if (ch1->ptrCar != NULL)
    {
        free(ch1->ptrCar);
    }
    ch1->nbCar = lgCh2;
    ch1->ptrCar = ptrAlloc;

    return;
}




void collerChaine(ChaineDyn *ch1, const ChaineDyn ch2, Indicateur *succes)
{
    int lgCh1;              // Longueur de la chaîne ch1
    int lgCh2;              // Longueur de la chaîne ch2
    PointeurCar ptrAlloc;   // Pointeur sur le bloc d'octets alloué dynamiquement pour stocker la nouvelle chaîne

    lgCh2 = ch2.nbCar;
    if (lgCh2 > 0)
    {
        lgCh1 = ch1->nbCar;
        ptrAlloc = malloc((lgCh1 + lgCh2) * sizeof(char));
        if (ptrAlloc == NULL)
        {
            *succes = ERR_ALLOC;
            return;
        }
        copierBlocOctets(ptrAlloc,ch1->ptrCar,lgCh1);
        copierBlocOctets(ptrAlloc+lgCh1,ch2.ptrCar,lgCh2);
        if (ch1->ptrCar != NULL)
        {
            free(ch1->ptrCar);
        }
        ch1->nbCar = lgCh1 + lgCh2;
        ch1->ptrCar = ptrAlloc;
    }

    return;
}




int comparerChaine(const ChaineDyn ch1, const ChaineDyn ch2)
{
    int lgMin;               // Longueur de la chaîne la plus courte.
    int result;              // Résultat de la comparaison.
    PointeurCar p1;          // Pointeur sur le caractère courant de ch1.
    PointeurCar p2;          // Pointeur sur le caractère courant de ch2.
    int cpt;                 // Compteur de caractères.
    bool fini;               // Indicateur de contrôle de la boucle.

    if (ch1.nbCar <= ch2.nbCar)
    {
        lgMin = ch1.nbCar;
    }
    else
    {
        lgMin = ch2.nbCar;
    }
    cpt = lgMin;
    p1 = ch1.ptrCar;
    p2 = ch2.ptrCar;
    fini = false;
    while (fini == false)
    {
        if (cpt > 0)
        {
            if (*p1 == *p2)
            {
                p1 = p1 + 1;
                p2 = p2 + 1;
                cpt--;
            }
            else
            {
                fini = true;
            }
        }
        else
        {
            fini = true;
        }
    }
    if (cpt != 0)
    {
        if (*p1 > *p2)
        {
            result = 1;
        }
        else
        {
            result = -1;
        }
    }
    else
    {
        if (ch1.nbCar == ch2.nbCar)
        {
            result = 0;
        }
        else
        {
            if (ch1.nbCar > ch2.nbCar)
            {
                result = 1;
            }
            else
            {
                result = -1;
            }
        }
    }

    return(result);
}




void extraireSousChaine(ChaineDyn *ch1, const ChaineDyn ch2, const int p, const int n, Indicateur *succes)
{
    int lgCh2;                  // Longueur de la chaîne ch2.
    int lgSousCh2;              // Longueur de la sous chaîne à extraire.
    PointeurCar ptrAlloc;       // Pointeur sur le bloc d'octets alloué dynamiquement pour stocker la sous chaîne à extraire.

    lgCh2 = ch2.nbCar;
    if ((p < 1) || (p > lgCh2) || (n < 0))
    {
        *succes = ERR_PARAM;
        return;
    }
    lgSousCh2 = lgCh2 - p + 1;
    if (lgSousCh2 > n)
    {
        lgSousCh2 = n;
    }
    if (lgSousCh2 == 0)
    {
        ptrAlloc = NULL;
    }
    else
    {
        ptrAlloc = malloc(lgSousCh2 * sizeof(char));
        if (ptrAlloc == NULL)
        {
            *succes = ERR_ALLOC;
            return;
        }
        copierBlocOctets(ptrAlloc,(ch2.ptrCar + p - 1), lgSousCh2);
    }
    if (ch1->ptrCar != NULL)
    {
        free(ch1->ptrCar);
    }
    ch1->nbCar = lgSousCh2;
    ch1->ptrCar = ptrAlloc;

    return;
}




void copierSousChaine(ChaineDyn *ch1, const ChaineDyn ch2, const int n, Indicateur *succes)
{
    PointeurCar ptrAlloc;   // Pointeur sur le bloc d'octets alloué dynamiquement pour stocker la nouvelle chaîne

    if (n < 0)
    {
        *succes = ERR_PARAM;
        return;
    }
    if (n == 0)
    {
        ch1->ptrCar = NULL;
    }
    else
    {
        ptrAlloc = malloc(n * sizeof(char));
        if (ptrAlloc == NULL)
        {
            *succes = ERR_ALLOC;
            return;
        }
        copierBlocOctets(ptrAlloc,ch2.ptrCar,n);
    }
    if (ch1->ptrCar != NULL)
    {
        free(ch1->ptrCar);
    }
    ch1->nbCar = n;
    ch1->ptrCar = ptrAlloc;

    return;
}




void collerSousChaine(ChaineDyn *ch1, const ChaineDyn ch2, const int n, Indicateur *succes)
{
    int lgCh1;              // Longueur de la chaîne ch1
    PointeurCar ptrAlloc;   // Pointeur sur le bloc d'octets alloué dynamiquement pour stocker la nouvelle chaîne

    if (n < 0)
    {
        *succes = ERR_PARAM;
        return;
    }
    if (n > 0)
    {
        lgCh1 = ch1->nbCar;
        ptrAlloc = malloc((lgCh1 + n) * sizeof(char));
        if (ptrAlloc == NULL)
        {
            *succes = ERR_ALLOC;
            return;
        }
        copierBlocOctets(ptrAlloc,ch1->ptrCar,lgCh1);
        copierBlocOctets(ptrAlloc+lgCh1,ch2.ptrCar,n);
        if (ch1->ptrCar != NULL)
        {
            free(ch1->ptrCar);
        }
        ch1->nbCar = lgCh1 + n;
        ch1->ptrCar = ptrAlloc;
    }

    return;
}




int comparerSousChaine(const ChaineDyn ch1, const ChaineDyn ch2, const int n, Indicateur *succes)
{
    int result;              // Résultat de la comparaison.
    PointeurCar p1;          // Pointeur sur le caractère courant de ch1.
    PointeurCar p2;          // Pointeur sur le caractère courant de ch2.
    int cpt;                 // Compteur de caractères.
    bool fini;               // Indicateur de contrôle de la boucle.

    if (n < 0)
    {
        *succes = ERR_PARAM;
        return(3);
    }
    cpt = n;
    p1 = ch1.ptrCar;
    p2 = ch2.ptrCar;
    fini = false;
    while (fini == false)
    {
        if (cpt > 0)
        {
            if (*p1 == *p2)
            {
                p1 = p1 + 1;
                p2 = p2 + 1;
                cpt--;
            }
            else
            {
                fini = true;
            }
        }
        else
        {
            fini = true;
        }
    }
    if (cpt != 0)
    {
        if (*p1 > *p2)
        {
            result = 1;
        }
        else
        {
            result = -1;
        }
    }
    else
    {
        if ((ch1.nbCar < n) && (ch1.nbCar < ch2.nbCar))
        {
            result = -1;
        }
        else
        {
            if ((ch2.nbCar < ch1.nbCar) && (ch2.nbCar < n))
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
    }

    return(result);
}














