#include <stdlib.h>
#include <SDL/SDL.h>

int main ( int argc, char** argv )
{
    FILE *fichier = NULL;
    int i = 0, j = 0,platJeu[48][64];

    fichier = fopen("niveaux.txt","w");

    for (i=0;i<48;i++)
    {
        j = 0;
        for (j=0;j<64;j++)
        {
            platJeu[i][j] = '0';
        }
    }

    for (i=0;i<48;i++)
    {
        j = 0;
        for (j=0;j<64;j++)
        {
            fprintf(fichier,"%c",platJeu[i][j]);
        }
    }
}
