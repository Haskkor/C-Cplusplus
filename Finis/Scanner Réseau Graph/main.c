#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <Iphlpapi.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "SP.h"
#define ping "ping"

int main(int argc, char *argv[])
{
    char myIP[14],*IP = getIP(),tmpfile[50],pingEtAdr[50],adrIP[11][24][14],*subMask,*dns,strDNS[100],strIP[30];;
    int i = 0,tabScreen[24][24],iTabScreen = 0,jTabScreen = 0,continuer = 1,posClicX = 0,posClicY = 0,clicPoste = 0;
    struct hostent *host;
    struct in_addr in;
    SDL_Surface *ecran = NULL,*computerDown = NULL,*computerUp = NULL,*surfIP = NULL, *surfDNS = NULL, *boutonVert = NULL;

    SDL_Rect posIP,posDNS;
    SDL_Event event;

    IP_ADAPTER_INFO * FixedInfo;
    ULONG ulOutBufLen;

    TTF_Init();
    TTF_Font *policeIPDNS = NULL;
    policeIPDNS = TTF_OpenFont("Kingthings Organica.ttf", 15);
    SDL_Color couleurNoire = {0,0,0};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Scanner Reseaux",NULL);
    SDL_WM_SetIcon(IMG_Load("Computer_down.png"),NULL);

    ecran = SDL_SetVideoMode(600,400,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    computerDown = IMG_Load("Computer_down.png");
    computerUp = IMG_Load("Computer_up.gif");
    boutonVert = IMG_Load("button_green.png");
    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));

    // Initialise tabScreen
    for(iTabScreen=0;iTabScreen<11;iTabScreen++)
    {
        jTabScreen = 0;
        if (iTabScreen < 10)
        {
            for(jTabScreen=0;jTabScreen<24;jTabScreen++)
            {
                tabScreen[iTabScreen][jTabScreen] = '0';
            }
        }
        else
        {
            for(jTabScreen=0;jTabScreen<14;jTabScreen++)
            {
                tabScreen[iTabScreen][jTabScreen] = '0';
            }
        }
    }

    // Trouve le masque de sous réseaux
    FixedInfo = (IP_ADAPTER_INFO *) GlobalAlloc( GPTR, sizeof( IP_ADAPTER_INFO ) );
    ulOutBufLen = sizeof( IP_ADAPTER_INFO );
    if ( ERROR_SUCCESS != GetAdaptersInfo( FixedInfo, &ulOutBufLen ) )
    {
        return FALSE;
    }
    subMask = FixedInfo->IpAddressList.IpMask.String;

    // Suppression de la dernière partie de l'adresse ip
    sprintf(myIP,"%s",IP);
    for (i=14;i<=14;i--)
    {
        if (IP[i] != '.')
        {
            IP[i] = '\0';
        }
        else
        {
            break;
        }
    }

    while (continuer == 1)
    {
        iTabScreen = 0;
        jTabScreen = 0;

        for (i=1;i<255;i++)
        {
            // Ecrit l'adresse ip et les options du ping dans une chaîne
            sprintf(tmpfile,"%s%d -n 1 -w 10 > pingOut.txt",IP,i);

            // Concatène le mot ping et la chaîne contenant l'ip et les options
            strcpy(pingEtAdr, "ping ");
            strcat(pingEtAdr, &tmpfile);

            // Ping de l'adresse en cours
            system(pingEtAdr);

            // Vérification de la validité du ping
            if (verifPing() == 1)
            {
                tabScreen[iTabScreen][jTabScreen] = '1';
                sprintf(adrIP[iTabScreen][jTabScreen],"%s%d",IP,i);
            }
            else
            {
                tabScreen[iTabScreen][jTabScreen] = '0';
            }
            jTabScreen++;
            if (jTabScreen == 24)
            {
                jTabScreen = 0;
                iTabScreen++;
            }

            SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,228,228,228));

            // Attend les évènements en continu
            SDL_PollEvent(&event);
            switch(event.type)
            {
                // Clic sur la croix pour quitter
                case SDL_QUIT :
                    i = 256;
                    continuer = 0;
                    break;
                // Clic sur un poste pour en connaitre l'ip et le dns
                case SDL_MOUSEBUTTONDOWN :
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (tabScreen[event.motion.y / 25][event.motion.x / 25] == '1')
                        {
                            tabScreen[posClicY][posClicX] = '1';
                            posClicX = event.motion.x / 25;
                            posClicY = event.motion.y / 25;
                            in.s_addr = inet_addr(adrIP[posClicY][posClicX]);
                            host = gethostbyaddr((char *)&in, 4, AF_INET);
                            if (host)
                            {
                                dns = host->h_name;
                            }
                            else
                            {
                                dns = "Pas de dns disponible.";
                            }

                            sprintf(strIP, "IP : %s",adrIP[posClicY][posClicX]);
                            surfIP = TTF_RenderText_Blended(policeIPDNS,strIP,couleurNoire);
                            sprintf(strDNS, "DNS : %s",dns);
                            surfDNS = TTF_RenderText_Blended(policeIPDNS,strDNS,couleurNoire);
                            tabScreen[posClicY][posClicX] = '2';
                            clicPoste = 1;
                        }
                        else
                        {
                            clicPoste = 0;
                            tabScreen[posClicY][posClicX] = '1';
                        }
                    }
                    break;

            }

            // Affichage du scan en cours
            scanEnCours(ecran,i);
            // Affichage des infos IP et DNS
            if (clicPoste == 1)
            {
                posIP.x = ((ecran->w / 2) - (surfIP->w / 2));
                posIP.y = 300;
                posDNS.x = ((ecran->w / 2) - (surfDNS->w / 2));
                posDNS.y = 330;
                SDL_BlitSurface(surfIP,0,ecran,&posIP);
                SDL_BlitSurface(surfDNS,0,ecran,&posDNS);
            }
            // Affichage des infos de l'utilisateur
            infosPersos(ecran,myIP,subMask);
            // Blit des différents éléments
            bliterTabScreen(ecran,computerDown,computerUp,boutonVert,tabScreen);
            // Blit du curseur
            SDL_Flip(ecran);

        }


    }


    return(0);
}
