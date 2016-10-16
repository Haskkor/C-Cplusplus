#include<iostream.h>
using namespace std;

int main()
{
    int A,B,C;
    
    cout<<"Chiffre A : ";cin>>A;
    cout<<"Chiffre B : ";cin>>B;
    cout<<"Chiffre C : ";cin>>C;
    
    if( (C<A && C>B || C>A && C<B))
    cout<<"C est compris entre A et B"<<endl;
    else cout<<"C n'est pas compris entre A et B"<<endl;
    system("PAUSE");
    
    return 0;
}
    
    
