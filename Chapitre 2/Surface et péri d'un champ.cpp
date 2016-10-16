#include<iostream.h>
using namespace std

int main()
{
    double largeur,longueur,surface,perimetre;
    
    cout<<"Largeur champ : ";cin>>largeur;
    cout<<"Longueur champ : ";cin>>longueur;
    
    surface=largeur*longueur;
    perimetre=2*(largeur+longueur);
    
    cout<<"La surface est : "<<surface<<endl;
    cout<<"Le péri est : "<<perimetre<<endl;
    
    return 0;
}
