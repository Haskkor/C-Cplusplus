#include<iostream.h>
using namespace std;

int main()
{
    int n;
    bool ok;
    
    do
    {
         cout<<"Tapez un chiffre entre 1 et 20";cin>>n;
         ok= n<=20 && n>=0;
         if(!ok)cout<<"ERREUR! RECOMMENCEZ!"<<endl;
         }while(!ok);
         
         n=n+17;
         cout<<"La valeur finale est:"<<n<<endl;
         system("PAUSE");
         
    return 0;
}
