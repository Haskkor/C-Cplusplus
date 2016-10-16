#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>



int main(int argc, char *argv[])
{
    // Déclaration des pointeurs utilisés pour la lecture d'un dossier
    DIR *dir;
    struct dirent *dp;
    char *arg;

    if ((dir = opendir ("C:\\Documents and Settings\\CER3100426\\Mes documents\\PRIVE\\C\\Visualisation spectrale du son")) == NULL)
    {
        perror ("Cannot open .");
        exit (1);
    }

    while ((dp = readdir (dir)) != NULL)
    {
        arg = dp->d_name;
        printf("%s\n", arg);
            //closedir(dir);
    }

    return(0);

}
