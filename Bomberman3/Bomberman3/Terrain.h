#include "Case.h"

#pragma once

//Classe dont la fonction principale est de rassembler toutes les cases du terrain
class Terrain {

private:

	//Nombre de cases du terrain
	int taille_vecteur;

	//Le vecteur d'éléments de la classe Case 
	vector<Case> terrain;

	//Le vecteur d'images des types de bonus
	SDL_Rect t_clip[4];


public:

	//Constructeur par défaut
	Terrain();

	//Fixe le statut et la position de toutes les cases du terrain ainsi que les bonus
	void init_terrain();

	//Fixe les cadres des différentes images sur l'image en source
	void set_clip();

	//Récupère la case portant le numéro placé en argument
	Case& get_terrain(int i);

	//Gère l'affichage des cases et des bonus
	void show();

	//Charge les images nécessaires à l'image
	void load_sprite(); 

	//Libère les espaces où ont été chargé les images
	void clean_up();
	
};