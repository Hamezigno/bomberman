#include "Case.h"

#pragma once

//Classe dont la fonction principale est de rassembler toutes les cases du terrain
class Terrain {

private:

	//Nombre de cases du terrain
	int taille_vecteur;

	//Le vecteur d'�l�ments de la classe Case 
	vector<Case> terrain;

	//Le vecteur d'images des types de bonus
	SDL_Rect t_clip[4];


public:

	//Constructeur par d�faut
	Terrain();

	//Fixe le statut et la position de toutes les cases du terrain ainsi que les bonus
	void init_terrain();

	//Fixe les cadres des diff�rentes images sur l'image en source
	void set_clip();

	//R�cup�re la case portant le num�ro plac� en argument
	Case& get_terrain(int i);

	//G�re l'affichage des cases et des bonus
	void show();

	//Charge les images n�cessaires � l'image
	void load_sprite(); 

	//Lib�re les espaces o� ont �t� charg� les images
	void clean_up();
	
};