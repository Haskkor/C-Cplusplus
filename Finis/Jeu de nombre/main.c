#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
 int nombreJoueur = 0 , nombreMystere = 0 ;
 const int MAX = 100, MIN = 1;

 srand(time(NULL));
 nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;

 do
 {
    printf("Quel est le nombre? : ");
    scanf("%d", &nombreJoueur);
    if (nombreJoueur > nombreMystere)
    {
        printf("Trop grand.\n");
    }
    else if (nombreJoueur < nombreMystere)
    {
        printf("Trop petit.\n");
    }
    else
    {
        printf("Tu as gagne.");
    }
 }
 while (nombreJoueur != nombreMystere) ;
}
