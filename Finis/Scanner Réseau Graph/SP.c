#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <Iphlpapi.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL_image.h>
#include "SP.h"
#define ping "ping"




int getIP()
{
    char mon_nom[64];
    int compteur;

    HOSTENT *ip_resolue;
    SOCKADDR_IN valip;

    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);

    gethostname(mon_nom, sizeof(mon_nom));
    ip_resolue = gethostbyname(mon_nom);

    // Adresse étrange
    if(ip_resolue->h_addr_list[0] != NULL)
    {
        for (compteur = 0; ip_resolue->h_addr_list[compteur+1] != NULL; compteur++) {}
            memcpy(&valip.sin_addr.s_addr, ip_resolue->h_addr_list[compteur], ip_resolue->h_length);
    }

    // Adresse sur le réseau
    if((ip_resolue->h_addr_list[0] != NULL)&&(ip_resolue->h_addr_list[1] != NULL))
    {
        memcpy(&valip.sin_addr.s_addr, ip_resolue->h_addr_list[0], ip_resolue->h_length);
    }

    return inet_ntoa(valip.sin_addr);

}




int verifPing()
{
    FILE *fichPing = NULL;
    int i = 0;
    char parcours;

    fichPing = fopen("pingOut.txt","r");

    while(i<3)
    {
        parcours = fgetc(fichPing);
        if (parcours == '\n')
        {
            i++;
        }
    }

    i = 0;

    parcours = fgetc(fichPing);
    if(parcours == 'R')
    {
        parcours = fgetc(fichPing);
        parcours = fgetc(fichPing);
        if(parcours == 'p')
        {
            parcours = fgetc(fichPing);
            if(parcours == 'o')
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }
        else
        {
            return(0);
        }
    }
    else
    {
        return(0);
    }

    fclose(fichPing);

}




void bliterTabScreen(SDL_Surface *ecran,SDL_Surface *computerDown,SDL_Surface *computerUp,SDL_Surface *boutonVert,int tabScreen[11][24])
{
    SDL_Rect posComp;
    int i = 0,j = 0;

    for (i=0;i<11;i++)
    {
        j = 0;
        for (j=0;j<24;j++)
        {
            posComp.x = j * 25;
            posComp.y = i * 25;
            switch (tabScreen[i][j])
            {
                case '0' :
                    SDL_BlitSurface(computerDown,NULL,ecran,&posComp);
                    break;
                case '1' :
                    SDL_BlitSurface(computerUp,NULL,ecran,&posComp);
                    break;
                case '2' :
                    SDL_BlitSurface(boutonVert,NULL,ecran,&posComp);
            }
        }
    }

}




void scanEnCours(SDL_Surface *ecran,int i)
{
    char strCompteur[10];
    SDL_Surface *compteur = NULL;
    SDL_Rect posCompteur;
    TTF_Font *police = NULL;

    police = TTF_OpenFont("Kingthings Organica.ttf", 15);
    SDL_Color couleurPolice = {0,0,0};

    sprintf(strCompteur, "%d / 254",i);
    compteur = TTF_RenderText_Blended(police,strCompteur,couleurPolice);

    posCompteur.x = ((ecran->w) - (compteur->w));
    posCompteur.y = ((ecran->h) - (compteur->h));

    SDL_BlitSurface(compteur,0,ecran,&posCompteur);

    return;

}




void infosPersos(SDL_Surface *ecran,char *myIP,char *subMask)
{
    char strInfos[100];
    SDL_Surface *infos = NULL;
    SDL_Rect posInfos;
    TTF_Font *police = NULL;

    police = TTF_OpenFont("Kingthings Organica.ttf", 15);
    SDL_Color couleurPolice = {0,0,0};

    sprintf(strInfos, "IP : %s   SubnetMask : %s",myIP,subMask);
    infos = TTF_RenderText_Blended(police,strInfos,couleurPolice);

    posInfos.x = 0;
    posInfos.y = (ecran->h - infos->h);

    SDL_BlitSurface(infos,0,ecran,&posInfos);

    return;

}


