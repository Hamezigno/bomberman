#include "Bombe.h"

#pragma once

//Classe qui rassemble les bombes d'un Bomber
class v_Bombe 
{
private:
	//Nombre de bombes disponibles au maximum dans l'invertaire du Bomber
	int nb_bombes_max;

	//Puissance de toutes les bombes du vecteur
	int puissance;

	//L'inventaire du Bomber, un vecteur de Bomber
	vector<Bombe> inventaire;

	//Le vecteur d'images des types d'affichage de la bombe et des flammes
	SDL_Rect b_clip[12];

	// Effet sonore joué lors de l'explosion d'une bombe
	Mix_Chunk *explosion ;


public:

	//Constructeur par défaut
	v_Bombe();

	//Initialise le vecteur en fixant l'argument source de chacune de ses bombes
	void init_inventaire();

	//Retourne le numéro dans le vecteur de la première bombe disponible ou -1 si aucune ne l'est
	int bombe_dispo();

	//Méthode liée au bonus bombe, augmente de 1 la taille du vecteur et créée la bombe à ce nouvel emplacement
	void ajouter_bombe();

	//Augmente la puissance de la bombe du nombre mis en argument
	void augmenter_puissance(int x);
	
	//Charge l'image relative aux bombes et aux flammes
	void load_sprite();

	//Gère l'affichage des bombes et des flammes
	void show(Terrain &terrain);

	//Fixe les cadres des différentes images sur l'image en source
	void set_clip();

	//Libère l'espace alloué par l'image chargée en source 
	void clean_up();
	
	//Retourne la bombe à la i ème position du vecteur
	Bombe* get_bombe(int i);

	//Retourne la puissance de la bombe
	int get_puissance();

	//Retourne le nombre maximal de bombes disponibles
	int get_nb_bombes_max();
};