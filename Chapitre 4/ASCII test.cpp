#include<iostream.h>
using namespace std;

int main()
{
    char a;
    cout<<"Tapez un caractere : ";cin>>a;
    if( a>='A' && a<='Z')cout<<"Vous avez tape une majuscule."<<endl;
    else if( a>='a' && a<='z')cout<<"Vous avez tape une minuscule."<<endl;
    else if( a>='0' && a<='9')cout<<"Vous avez tape un chiffre."<<endl;
    else cout<<"Vous n'avez tapé ni une maj ni une min ni un chiffre."<<endl;
    system("PAUSE");
    return 0;
}
