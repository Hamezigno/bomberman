#include "Menu.h" 

Menu::Menu(string name) : Graphics(name) {
}
 
// Setters
void Menu::setFontStyle(string font, const int size) {
this->m_fontSize = size;
this->m_fontPath = font;
}
 
void Menu::setColor(SDL_Color colorNormal, SDL_Color colorHover) {
this->m_colorNormal = colorNormal;
this->m_colorHover = colorHover;
}


// Getters
int Menu::getCurrentIndex() {
return this->m_currentIndex;
}
 
int Menu::getMenuSize() {
return this->m_menuElementList.size();
}
 
bool Menu::getIsSelect() {
return this->m_select;
}

void Menu::addRow(string text) {
 
// Variable locale pour nouveau lien
menuElement m_el;
 
//G�n�re la surface de s�lection
m_el.surfaceHover = surfacePolice(this->m_fontPath, this->m_fontSize,text, this->m_colorHover);
 
//G�n�re la surface normale
m_el.surfaceNormal = surfacePolice(this->m_fontPath, this->m_fontSize, text, this->m_colorNormal);
 
//Ajout dans le menu
this->m_menuElementList.push_back(m_el);
 
//Initialise le currentIndex � 0
this->m_currentIndex = 0;
}


// fonction d'affichage
void Menu::show() {
	// on r�cup�re la source (i.e le fichier charg� en argument du constructeur)
	apply_surface2(0,0,this->get_source(),NULL);
	// la position en y  o� on collera les liens
	int rowY; 
	// on d�finit la position pour chaque �l�ment et on les �carte par 10 pixels 
	for(int i = 0; i< getMenuSize(); i++) {
	rowY = this->e_y + i * this->m_menuElementList.at(i).surfaceHover->h + 10; 

	// On colle le lien du menu selon le statut "s�lectionn�" ou "non s�lectionn�" 
	if(this->m_currentIndex == i) {
		apply_surface2(e_x, rowY+400,this->m_menuElementList.at(i).surfaceHover,NULL); 
	}
	else {
		apply_surface2(e_x, rowY+400,this->m_menuElementList.at(i).surfaceNormal,NULL);
	}
	}
}	
		

// Ces fonctions de d�placement entre les liens sont utilis�es dans Jeu::handle_events() directement
void Menu::moveUp() {
	if(m_currentIndex >0) {
		m_currentIndex--;}
}

void Menu::moveDown() {
	if(m_currentIndex <this->getMenuSize()-1) {
		m_currentIndex++;
	}
}

Menu::~Menu() {
}