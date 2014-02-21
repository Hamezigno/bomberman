#include "Menu.h"
#pragma once

//Classe fille de la classe graphics qui gère l'affichage et les statuts des bonus
class Bonus: public Graphics{

private:
	
	//Le type du bonus défini en constante
	int type_bonus;

	//Le vecteur d'images des types de bonus
	SDL_Rect bo_clip[8];

public:

	//Constructeur par défaut
	Bonus();

	//Fixe les cadres des différentes images sur l'image en source
	void set_clip();

	//Fixe le type de bonus
	void set_bonus(int x);

	//Rend le type du bonus
	int  get_type();

	//Gestion de l'affichage du bonus
	void show();
};
