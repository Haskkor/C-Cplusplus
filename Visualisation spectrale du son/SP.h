#define LARGEUR_FENETRE_VSS         512
#define HAUTEUR_FENETRE_VSS         150
#define RATIO                       (HAUTEUR_FENETRE_VSS / 255.0)
#define DELAI_RAFRAICHISSEMENT      25
#define TAILLE_SPECTRE              512



// Dessine un pixel sur une surface
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

// Récupérer la liste de morceaux disponibles dans le dossier
int listerMorceaux(char tabTunes[500][500]);

// Initialisation du tableau de morceaux
void initialiserTabTunes(char tabTunes[500][500]);

// Affichage du spectre
void afficherSpectre(SDL_Surface *vSS,float spectreD[TAILLE_SPECTRE],float spectreG[TAILLE_SPECTRE]);

// Affichage de la liste de morceaux à jouer
int afficherTabTunes(char tabTunes[500][500],SDL_Surface *ecran,int tuneChoisie);

// Lecture du morceau et affichage du spectre
int lectureMusique(FMOD_SYSTEM *system,FMOD_SOUND *musique,FMOD_RESULT resultat,int tuneAJouer,char tabTunes[500][500],unsigned int *tempsTune);

// Affiche la durée du morceau et la progression de la lecture
void afficherTemps(SDL_Surface *ecran, unsigned int tempsTune, FMOD_CHANNEL *canal);

// Affiche le pourcentage de volume sonore
void afficherVolume(SDL_Surface *ecran, float volume);

// Affiche le temps quand le bouton de la barre de recherche est pressé
void afficherTempsRecherche(SDL_Surface *ecran, unsigned int tempsPixel,int posSourisx, int posSourisy);

// Déplace le point de la barre d'avancement en fonction du temps
int deplacementPtBarAvancement(FMOD_CHANNEL *canal, FMOD_SOUND *musique);
