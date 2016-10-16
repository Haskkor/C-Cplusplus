#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Lit un caractère donné par le joueur et le retourne au programme.
char lireCaractere();

// Vérifie qu'un caractère entré par le joueur soit présent dans le mot et modifie le mot caché.
void verifierMot(const char lettreJoueur, const char motSecret[], char *motCache, int *pointNbrCoups, int tailleMot);

// Compte le nombre de lettres dans le mot secret.
int compterLettres(const char motSecret[]);

// Vérifie que le joueur n'ait pas gagné.
int partieGagnee(const char *motCache,int tailleMot);

// Remplit le mot caché avec des '*'.
void remplirMotCache(char *motCache, int tailleMot);
