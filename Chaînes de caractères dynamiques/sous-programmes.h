#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Taille maximale des chaînes.
#define TAILLE_MAX 256




// Définition d'un type char* en PointeurCar.
typedef char *PointeurCar;

// Définition d'une structure contenant le nombre de la caractère de la chaîne dynamique et le pointeur sur la chaîne.
typedef struct
{
    int nbCar;              // Nombre de caractères de la chaîne
    PointeurCar ptrCar;     // Pointeur sur le tableau de caractères contenant la suite de caractères ASCII constituant la chaïne
}ChaineDyn;

// Définition d'un type énuméré booléen.
typedef enum {false, true} bool;

// Définition d'un type énuméré indicateur pour les erreurs.
typedef enum {ERR_ALLOC = 0, ERR_PARAM = 1} Indicateur;




// Initialise ch à chaîne vide.
void creerChaineVide(ChaineDyn *ch);

// Lit un chiffre et vérifie que l'utilisateur n'ait pas commis d'erreurs.
int lireChiffre();

// Affiche la longueur, le pointeur et le contenu de la chaîne ch passée en paramètre.
void afficherChaineDyn (const ChaineDyn *ch);

// Lit une chaîne de caractères et les alloue à un ChaineDyn.
void lireChaine(ChaineDyn *ch);

// Libère le bloc d'octets alloué à la chaîne ch en mémoire dynamique et réinitialise ch en chaîne vide.
void libererChaine(ChaineDyn *ch);

// Vide le buffer clavier en consommant tout les caractères présents dans ce buffer jusqu'à ce qu'il soit vide.
void purger();

// Retourne un entier égal à la longueur de la chaîne ch.
int longueurChaine(const ChaineDyn ch);

// Copier des caractères d'une chaîne à une autre.
void copierBlocOctets(PointeurCar ptrAlloc,char *ch2,int lgch2);

// Affecte les caractères de ch2 qui est une chaîne du langage C, à la chaîne ch1 qui est une chaîne du type ChaineDyn.
void convertirChaine(ChaineDyn *ch1, const char *ch2, Indicateur *succes);

// Affecte la chaîne ch2 à la chaîne ch1.
void copierChaine(ChaineDyn *ch1, const ChaineDyn ch2, Indicateur *succes);

// Concatène la chaîne ch2 à la chaîne ch1.
void collerChaine(ChaineDyn *ch1, const ChaineDyn ch2, Indicateur *succes);

// Compare lexicographiquement 2 chaînes et retourne : 0 si ch1 == ch2 ; +1 si ch1 > ch2 ; -1 si ch1 < ch2.
int comparerChaine(const ChaineDyn ch1, const ChaineDyn ch2);

// Extrait de la chaîne ch2, la sous chaîne de n caractères commençant à la position p et l'affecte à la chaîne ch1.
void extraireSousChaine(ChaineDyn *ch1, const ChaineDyn ch2, const int p, const int n, Indicateur *succes);

// Affecte les n premiers caractères de la chaîne ch2 à la chaîne ch1.
void copierSousChaine(ChaineDyn *ch1, const ChaineDyn ch2, const int n, Indicateur *succes);

// Concatène les n premiers caractères de la chaîne ch2 à la chaîne ch1.
void collerSousChaine(ChaineDyn *ch1, const ChaineDyn ch2, const int n, Indicateur *succes);

// Compare lexicographiquement 2 sous chaines et retourne : 0 si ch1 == ch2 ; +1 si ch1 > ch2 ; -1 si ch1 < ch2.
int comparerSousChaine(const ChaineDyn ch1, const ChaineDyn ch2, const int n, Indicateur *succes);











