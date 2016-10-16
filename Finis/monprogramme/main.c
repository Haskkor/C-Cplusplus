#include <stdio.h>
#include <stdlib.h>

int main()
{
 int choixMenu;

 printf("=== Menu ===\n\n");
 printf("1. Royal Cheese\n2. Mc Deluxe\n3. Mc Bacon\n4. Big Mac\n\n");
 printf("Votre choix ? ");
 scanf("%d", &choixMenu);
 printf("\n");

 switch (choixMenu)
    {
        case 1 :
            printf("Va te pendre.") ;
            break ;
        case 2 :
            printf("Va mourir.") ;
            break ;
        case 3 :
            printf("Tu vas deceder.") ;
            break ;
        case 4 :
            printf("Meurs.") ;
            break ;
        default :
            printf("Aucun choix correct.") ;
            break ;
    }

 return 0 ;
}

