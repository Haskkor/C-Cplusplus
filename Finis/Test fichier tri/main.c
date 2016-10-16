#include <stdio.h>
#include <stdlib.h>

int main()
{
    float tabScore[5] = {0},res = 20.000000,res2;
    int i = 4;
    FILE *fichier = NULL;

    fichier = fopen("highscores.txt","r+");
    fscanf(fichier, "%f\n%f\n%f\n%f\n%f", &tabScore[0], &tabScore[1], &tabScore[2], &tabScore[3], &tabScore[4]);
    tabScore[5] = res;

    for (i = 5; i > 0; i--)
    {
        res2 = tabScore[i];
        if (tabScore[i] > tabScore[i - 1])
        {
            res = tabScore[i - 1];
            tabScore[i - 1] = res2;
            tabScore[i] = res;
        }
    }

    printf("      %f %f %f %f %f %f",tabScore[0],tabScore[1],tabScore[2],tabScore[3],tabScore[4],tabScore[5]);
    rewind(fichier);

    fprintf(fichier,"%f\n%f\n%f\n%f\n%f",tabScore[0],tabScore[1],tabScore[2],tabScore[3],tabScore[4]);

    return;
}
