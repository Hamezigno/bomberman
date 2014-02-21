#include "v_Bombe.h" 

#pragma once 

//Classe fille de la classe Graphics qui g�re toutes les m�tohdes au Bomber
class Bomber : public Graphics
{

private :

	//Le vecteur d'images du Bomber sur la droite
	SDL_Rect b_Right[3];

	//Le vecteur d'images du Bomber sur la gauche
	SDL_Rect b_Left[3];

	//Le vecteur d'images du Bomber vers le haut
	SDL_Rect b_Up[3];

	//Le vecteur d'images du Bomber vers le bas
	SDL_Rect b_Down[3];

	//Le vecteur d'images du Bomber � sa mort
	SDL_Rect b_Death[3];

	//Le num�ro du Bomber ou celui du joueur de mani�re �quivalente
	int b_number; 

	//Argument inutile pouvant avoir n'importe quel nom ou type mais sans qui le .exe ne fonctionne pas correctement
	int a;

	//La vitesse du Bomber sur l'axe des abscisses
	int b_vitessex ;

	//La vitesse du Bomber sur l'axe des ordonn�es
	int b_vitessey ;

	//L'inventaire (vecteur de bombes) du Bomber
	v_Bombe *inventaire;

	//La position du Bomber (face, dos, de porfil sur la gauche ou de profil sur la droite)
	int b_statut; 

	//La partie du mouvement que le Bomber est en train d'effectuer
	int b_frame ; 

	//Indicateur sur le fait que ce Bomber joue cette partie
	bool joue;

	//Indicateur si le Bomber a le pouvoir coup de pied
	bool coup_de_pied;

	//Num�ro de la case o� se trouve la bombe que le Bomber pousse
	int pousse;

	Mix_Chunk *son ;

	


public :
	//Constructeur par d�faut
	Bomber();

	//Constructeur surcharg� qui donne en argument le num�ro du Bomber,
	//sa position au d�but du jeu et le vecteur de bombes du Bomber
	Bomber(int nb,int x,int y,v_Bombe* vect_bombe);

	//Fixe les cadres des diff�rentes images sur l'image en source
	void set_clip();

	//Initialise les arguments de l'inventaire du Bomber
	void init_inventaire();

	//G�re le mouvement du Bomber
	void bomber_move(Terrain& terrain) ; 

	//G�re l'affichage du Bomber et son mouvement
	void bomber_show(Terrain &terrain) ;
	
	//G�re l'interaction du Bomber avec les bonus
	void Bonus_activ(Terrain& terrain);

	//G�re l'interaction du Bomber avec le feu
	void Feu_activ(Terrain &terrain);

	//Rend l'�tat du Bomber
	bool mort();

	//Remplace la vitesse du Bomber par celle mise en argument
	void set_vitesse_x(int x);

	//Remplace la vitesse du Bomber par celle mise en argument
	void set_vitesse_y(int x);

	//Change l'argument du Bomber par celui mis en argument
	void set_joue(bool v);

	//Rend l'inventaire du Bomber
	v_Bombe* get_inventaire();

	//Indique si le Bomber pousse la bombe ou non
	int get_pousse();

	//Rend le statut du Bomber
	int get_staut();

	//Change l'entier mis en pousse du Bomber par celui mis en argument
	void set_pousse(int x);
}; 
