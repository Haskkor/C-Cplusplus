#include<iostream.h>
using namespace std

;int main()
{
    double a,b,temp;
    cout<<"Chiffre 1: ";cin>>a;
    cout<<"chiffre 2: ";cin>>b;
    
    temp=a;
    a=b;
    b=temp;
    
    cout<<"Chiffre 1: "<<a<<endl;
    cout<<"Chiffre 2: "<<b<<endl;
    
    return 0
}
    
