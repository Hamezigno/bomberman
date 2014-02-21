#include"Bomber.h"
#pragma once

//Classe qui regroupe l'ensemble des entités nécessaires à une partie et regroupe les méthodes liées à la gestion générale de la partie
class Jeu : public Graphics{
private:

	//Nombre de joeurs présents à cette partie
	int nb_joueurs;

	//Indicateur que la partie est en cours ou non
	int start_game;

	//Le Timer général de la partie
	Timer* tps_partie;
	Timer* rebours ;
	TTF_Font* font_time; 
	TTF_Font* victoire_font;
	TTF_Font* compte_a_rebours; 
	SDL_Surface* timer_ticks;
	Mix_Chunk *bonus ;


	//Un objet graphique qui gère l'affichage du fond du terrain
	Graphics* test;

	//Le terrain où les joueurs évolueront
	Terrain* terrain;
	
	//L'inventaire de chacun des joueurs
	v_Bombe* inventaire1;
	v_Bombe* inventaire2;
	v_Bombe* inventaire3;
	v_Bombe* inventaire4;

	//Les joueurs eux-mêmes, le quatrième est disponible seulement si l'ordianteur dispose d'un pavé numérique
	Bomber* joueur1;
	Bomber* joueur2;
	Bomber* joueur3;
	Bomber* joueur4;

	Menu* menu_pcpal ;
	Menu* menu_options ;
	Menu* menu_options2 ;
	Menu* menu_options3;
	Menu* choix_joueurs ;
	Menu* victoire ;
	Menu* egalite ;
	int retour ;

	Menu* menu_repertoire[6] ;
	Mix_Music *musique ;
	Mix_Chunk *timer_beep ;

	int menu_page  ;


public:
	//Constructeur surchargé de la partie avec pour argument le nombre de joueurs
	Jeu();

	//Destructeur de la classe
	~Jeu();

	// Fonction de détermination des menus 
	void set_menu() ;

	//Initialise toutes les instances de la classe, 
	//en particulier les éléments graphiques de ces instances
	void init_jeu();

	//Gère les événements lié à la pression sur une touche du clavier ou aux clics de la souris
	bool handle_events();

	//
	int update();

	//Libère l'espace alloué pour les différentes images nécessaires aux instances de la classe
	void clean();

	//Gère l'affichage de l'ensemble des entités de la partie
	void show();

	//Gère l'utilisation du pouvoir coup de pied du Bomber
	void pousse_bombe();

	//Met fin à la partie si les conditions idoines sont réunies
	void set_fin_partie();

	//Retourne le pointeur sur le joueur numéro x
	Bomber* get_joueur(int x);

	// fonction qui permet de choisir le nombre de joueurs depuis le menu
	void set_nb_joueurs(int x ) ;

	// Compte à rebours qui s'enclenche avant le début de la partie 
	void compte_rebours () ;


};