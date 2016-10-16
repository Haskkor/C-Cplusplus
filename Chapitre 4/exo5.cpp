#include<iostream.h>
using namespace std;

int main()
{
    int a,b,c;
    for (a=0;a<10;a++)
    {
        cout<<"chiffre : ";cin>>b;
        if(a==0)c=b;
        else if(b<c)c=b;
        }
     cout<<c<<endl;
     system("PAUSE");
     return 0;
} 
