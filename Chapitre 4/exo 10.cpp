#include<iostream.h>
using namespace std;

int main()
{
    int x=0,choix;
        cout<<"x vaut : "<<x<<endl;
        cout<<"1 : Ajouter 1"<<endl;
        cout<<"2 : Multiplier par 2";endl;
        cout<<"3 : Soustraire 4";endl;
        cout<<"4 : Quitter";endl;
        cout<<"Votre choix : ";cin>>choix;
        
        switch(choix)
                     {
                     case 1: x++;
                     case 2: x=x*2;
                     case 3: x=x-4;
                     }
                     
        cout<<"La valeur finale de x vaut : "<<x<<endl;
        system("PAUSE");
                     
        return 0;
}
