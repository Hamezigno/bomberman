#include "Bonus.h"

#pragma once;

//Classe fille de la fonction fille qui d�finit une case du terrain
class Case : public Graphics{

private :
	//Indicatrice sur la pr�sence d'une bombe sur la case
	int c_bombe;

	//Indicatrice sur le fait que la case soit en feu
	bool feu;

	//Le vecteur d'images des types de cases
	SDL_Rect clip[4];

	//Une entit� bonus affect�e � chaque case
	Bonus bonus;
	

public : 
	//Constructeur par d�faut
	Case();

	//Gestion du feu sur la case
	void test_case_feu();

	//Fixe les diff�rents arguments mis en private de la classe (setters)
	void setbombe(int x);
	void set_feu(bool x);

	//Retourne en fonction du nombre de points de vie le type de la case d�fini en constante
	int getStatut();

	// Getters
	int getbombe();
	bool get_feu();
	Bonus* getbonus();
	

} ;
