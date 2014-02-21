#include "Terrain.h"
#pragma once

//Classe fille de la classe Graphics qui regroupe toutes les m�thodes li�es aux bombes du personnage
class Bombe : public Graphics
{
    private:
    //Les diff�rents statuts de la bombe (put ou nowhere)
    int b_statut;
	//Le nombre maximum de cases atteint par le feu de la bombe 
	int b_puissance;
 
	//Le nombre de millisecondes restants avant la d�tonation normale de la bombe 
	//si celle_ci explose avant
	int temps_avant_detonation;


	
 // Arguments de la bombe relatifs � l'affichage de la flamme

	//Indicatrice sur le d�clenchement de la bombe
	int f_flag; 

	//Taille de la flamme dans chacune des directions
	int f_haut;
	int f_bas;
	int f_gauche;
	int f_droite;  

	//Vecteur des statuts des cases dans chacune des directions
	//depuis la position de la bombe
	vector<int> v_haut;
	vector<int> v_bas ;
	vector<int> v_gauche;
	vector<int> v_droite;
    
public:
    
	//Constructeur par d�faut
    Bombe();

	//Constructeur par d�faut avec pour argument la puissance de la bombe construite
	Bombe(int x);
	
	//Retire le statut de feu actif des cases de l'�l�ment de la classe Terrain 
	//mis en argument une fois le temps d'activation du feu d�pass�
	void clean_feu(Terrain &terrain);

	//Rend la diff�rence de temps entre le moment o� la bombe a �t� pos�e
	//et celui o� elle a �t� activ�e par le feu d'une autre bombe
	int cha�ne(Terrain &terrain);

	//Affiche le rectangle d'image mis en argument aux coordonn�es mises en argument
	void apply_surface(int x, int y, SDL_Rect *clip) ;

	//Rend la place dans le vecteur mis en argument de l'entier mis en argument
	int PlaceDansVecteur(int y, vector<int> W) ;
	
	//Initialise les 4 vecteurs de statut des cases autour de la bombe sur l'�l�ment de la classe Terrain mis en argument
	void set_vecteurs(Terrain &terrain);

	//Initialise la longueur de chaque feu dans chacune des 4 directions
	void set_longueur_feu();

	//Initialise les vecteurs de statut, la longueur des flammes et r�adapte
	//la taille de ces vecteurs suivant la puissance de la bombe
	void set_all(Terrain &terrain);

	//Fixe les diff�rents arguments mis en private de la classe
	void set_statut(int x);
	void set_puissance(int x);
	void set_f_flag(int x);
	void set_temps(int x);
	
	//Retourne les diff�rents arguments mis en private de la classe
	int get_statut();
	int getPuissance();
	int get_h();
	int get_b();
	int get_g();
	int get_d();
	int get_f_flag();
	int get_temps();



};