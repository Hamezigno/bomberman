#include "Graphics.h" 


// On souhaite que chaque lien d'un menu ait deux statuts : "s�lectionn�" (Hover) ou "non selectionn� (normal) d'o� la cr�ation de cette struct
struct menuElement {

SDL_Surface* surfaceNormal;
SDL_Surface* surfaceHover;
};

class Menu : public Graphics {

private :
// Le num�ro du lien s�lectionn�
int m_currentIndex;

// Indicateur de s�lection
bool m_select;

// El�ments de graphismes (taille, couleur quand s�lectionn�, couleur quand non s�lectionn�)
int m_fontSize;
string m_fontPath;
SDL_Color m_colorHover; 
SDL_Color m_colorNormal; 
 
//Tableau des liens du menu
vector <menuElement> m_menuElementList;




public:

// Le constructeur du menu avec en argument le nom du fichier � charger qui sera le fond d'�cran
Menu(string name);
// Fonction d'affichage
void show();
 
// Ajouter une ligne 
void addRow(string text);

//Les setters graphiques (police, position, couleur selon la s�lection ou non )
void setFontStyle(string font, const int size);
void setPosition(int X, int Y);
void setColor(SDL_Color colorNormal, SDL_Color colorHover);
 
// Getters
int getCurrentIndex();
int getMenuSize();
bool getIsSelect();

// Fonctions de d�placement inter liens
void moveUp();
void moveDown();
void select();

// Destructeur
virtual ~Menu();
};