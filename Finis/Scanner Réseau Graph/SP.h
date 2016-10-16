// Trouve l'IP de l'utilisateur
int getIP();

// Vérifie le retour du ping
int verifPing();

// Blit les différents éléments à l'écran
void bliterTabScreen(SDL_Surface *ecran,SDL_Surface *computerDown,SDL_Surface *computerUp,SDL_Surface *boutonVert,int tabScreen[11][24]);

// Affiche la progression du scan en permanence
void scanEnCours(SDL_Surface *ecran,int i);

// Affiche l'adresse IP et le masque de sous réseaux de l'utilisateur
void infosPersos(SDL_Surface *ecran,char *myIP,char *subMask);
























    /*jeton = strtok(myIP,".");

    while (jeton != NULL)
    {
        printf("L'octet est : %s\n", jeton);
        jeton = strtok(NULL,".");
    }*/



    //printf("%d\n",chknet("1.1.1.1"));
    //retPing = system("ping 1.1.1.1");
    //printf("%d",retPing);




    //printf("%d\n",chknet(adrIP));
    /*int chknet(char *ip)
    {
        struct sockaddr_in name;
        struct hostent * hent;
        int sock;
        int retour = 0;

        //creation de la socket en icmp

        if(!(sock = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)))
        {
            return (-1);
        }

        memset(&name,0,sizeof(struct sockaddr_in));
        name.sin_family = AF_INET;
        name.sin_addr.s_addr = inet_addr(ip);

        if (connect(sock,(struct sockaddr *) &name,sizeof(struct sockaddr)) == 0)
        {
            retour = 1;
        }
        else
        {
            retour = 0;
        }

        //shutdown(sock,SHUT_RDWR);

        //close(sock);

        return(retour);
    }*/






    /*printf("%s\n",getPrefixIp(myIP));

    char *getPrefixIp(char *ip)
    {
        char *prefix;
        prefix = malloc(16 * sizeof(char));
        int i, count, j;
        j=0;
        count=0;
        for (i=0;i<15;i++) {
            if (ip[i]=='.') {
                count++;
                if (count<3)
                    prefix[j] = '.';
                else
                    prefix[j] = '\0';
            }else{
                if (count<3)
                    prefix[j] = ip[i];
            }
            j=j+1;
        }
        return prefix;
    }*/
