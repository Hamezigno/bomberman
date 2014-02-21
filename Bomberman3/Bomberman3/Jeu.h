#include"Bomber.h"
#pragma once

//Classe qui regroupe l'ensemble des entit�s n�cessaires � une partie et regroupe les m�thodes li�es � la gestion g�n�rale de la partie
class Jeu : public Graphics{
private:

	//Nombre de joeurs pr�sents � cette partie
	int nb_joueurs;

	//Indicateur que la partie est en cours ou non
	int start_game;

	//Le Timer g�n�ral de la partie
	Timer* tps_partie;
	Timer* rebours ;
	TTF_Font* font_time; 
	TTF_Font* victoire_font;
	TTF_Font* compte_a_rebours; 
	SDL_Surface* timer_ticks;
	Mix_Chunk *bonus ;


	//Un objet graphique qui g�re l'affichage du fond du terrain
	Graphics* test;

	//Le terrain o� les joueurs �volueront
	Terrain* terrain;
	
	//L'inventaire de chacun des joueurs
	v_Bombe* inventaire1;
	v_Bombe* inventaire2;
	v_Bombe* inventaire3;
	v_Bombe* inventaire4;

	//Les joueurs eux-m�mes, le quatri�me est disponible seulement si l'ordianteur dispose d'un pav� num�rique
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
	//Constructeur surcharg� de la partie avec pour argument le nombre de joueurs
	Jeu();

	//Destructeur de la classe
	~Jeu();

	// Fonction de d�termination des menus 
	void set_menu() ;

	//Initialise toutes les instances de la classe, 
	//en particulier les �l�ments graphiques de ces instances
	void init_jeu();

	//G�re les �v�nements li� � la pression sur une touche du clavier ou aux clics de la souris
	bool handle_events();

	//
	int update();

	//Lib�re l'espace allou� pour les diff�rentes images n�cessaires aux instances de la classe
	void clean();

	//G�re l'affichage de l'ensemble des entit�s de la partie
	void show();

	//G�re l'utilisation du pouvoir coup de pied du Bomber
	void pousse_bombe();

	//Met fin � la partie si les conditions idoines sont r�unies
	void set_fin_partie();

	//Retourne le pointeur sur le joueur num�ro x
	Bomber* get_joueur(int x);

	// fonction qui permet de choisir le nombre de joueurs depuis le menu
	void set_nb_joueurs(int x ) ;

	// Compte � rebours qui s'enclenche avant le d�but de la partie 
	void compte_rebours () ;


};