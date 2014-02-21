#include "Graphics.h" 


// On souhaite que chaque lien d'un menu ait deux statuts : "sélectionné" (Hover) ou "non selectionné (normal) d'où la création de cette struct
struct menuElement {

SDL_Surface* surfaceNormal;
SDL_Surface* surfaceHover;
};

class Menu : public Graphics {

private :
// Le numéro du lien sélectionné
int m_currentIndex;

// Indicateur de sélection
bool m_select;

// Eléments de graphismes (taille, couleur quand sélectionné, couleur quand non sélectionné)
int m_fontSize;
string m_fontPath;
SDL_Color m_colorHover; 
SDL_Color m_colorNormal; 
 
//Tableau des liens du menu
vector <menuElement> m_menuElementList;




public:

// Le constructeur du menu avec en argument le nom du fichier à charger qui sera le fond d'écran
Menu(string name);
// Fonction d'affichage
void show();
 
// Ajouter une ligne 
void addRow(string text);

//Les setters graphiques (police, position, couleur selon la sélection ou non )
void setFontStyle(string font, const int size);
void setPosition(int X, int Y);
void setColor(SDL_Color colorNormal, SDL_Color colorHover);
 
// Getters
int getCurrentIndex();
int getMenuSize();
bool getIsSelect();

// Fonctions de déplacement inter liens
void moveUp();
void moveDown();
void select();

// Destructeur
virtual ~Menu();
};