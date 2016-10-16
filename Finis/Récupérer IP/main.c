#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib" )


int main()
{
    char mon_nom[64];
    char *IP;
    int compteur;

    HOSTENT* ip_resolue;
    SOCKADDR_IN valip;
    SOCKADDR_IN sin;

    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);

    gethostname(mon_nom, sizeof(mon_nom));
    ip_resolue = gethostbyname(mon_nom);

    // Adresse étrange
    if(ip_resolue->h_addr_list[0] != NULL)
    {
        for (compteur = 0; ip_resolue->h_addr_list[compteur+1] != NULL; compteur++) {}
            memcpy(&valip.sin_addr.s_addr, ip_resolue->h_addr_list[compteur], ip_resolue->h_length);
       // printf("\nAdresse(s) IP : %s",inet_ntoa(valip.sin_addr));
    }

    // Adresse sur le réseau
    if((ip_resolue->h_addr_list[0] != NULL)&&(ip_resolue->h_addr_list[1] != NULL))
    {
        memcpy(&valip.sin_addr.s_addr, ip_resolue->h_addr_list[0], ip_resolue->h_length);
       // printf(" / %s",inet_ntoa(valip.sin_addr));
    }

    IP = inet_ntoa(valip.sin_addr);
    printf("%s", IP);

    getch();
    return(0);
}
