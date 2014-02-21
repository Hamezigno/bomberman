#include "Bonus.h"

#pragma once;

//Classe fille de la fonction fille qui définit une case du terrain
class Case : public Graphics{

private :
	//Indicatrice sur la présence d'une bombe sur la case
	int c_bombe;

	//Indicatrice sur le fait que la case soit en feu
	bool feu;

	//Le vecteur d'images des types de cases
	SDL_Rect clip[4];

	//Une entité bonus affectée à chaque case
	Bonus bonus;
	

public : 
	//Constructeur par défaut
	Case();

	//Gestion du feu sur la case
	void test_case_feu();

	//Fixe les différents arguments mis en private de la classe (setters)
	void setbombe(int x);
	void set_feu(bool x);

	//Retourne en fonction du nombre de points de vie le type de la case défini en constante
	int getStatut();

	// Getters
	int getbombe();
	bool get_feu();
	Bonus* getbonus();
	

} ;
