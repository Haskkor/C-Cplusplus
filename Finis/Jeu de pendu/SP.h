#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Lit un caract�re donn� par le joueur et le retourne au programme.
char lireCaractere();

// V�rifie qu'un caract�re entr� par le joueur soit pr�sent dans le mot et modifie le mot cach�.
void verifierMot(const char lettreJoueur, const char motSecret[], char *motCache, int *pointNbrCoups, int tailleMot);

// Compte le nombre de lettres dans le mot secret.
int compterLettres(const char motSecret[]);

// V�rifie que le joueur n'ait pas gagn�.
int partieGagnee(const char *motCache,int tailleMot);

// Remplit le mot cach� avec des '*'.
void remplirMotCache(char *motCache, int tailleMot);
