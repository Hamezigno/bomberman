#include "Timer.h"

using namespace std;

#pragma once

//Classe m�re qui receuille l'ensemble des m�thodes li�es aux applications graphiques
class Graphics{

private:

//Nom du fichier qui sera charg�
string filename;

//Ces diff�rents �l�ments sont en proected afin qu'ils puissent �tre modifi�s dans les classes filles
protected:

//Nombre de points de vie de l'entit�
int e_pv; 

//El�ments fixant la position dans le niveau
int e_x;
int e_y;

//Nombre de pixels de d�calage pour afficher cette entit� par rapport � l'unit� de 50 pixels utilis�e dans tout le programme
int dec_pixel ;

//Un Timer sp�cifique � l'entit�
Timer e_timer;

//Un pointeur vers la surface sur laquelle s'appliquera l'affichage
SDL_Surface *screen;

//La surface sur laquelle figure l'image � afficher
SDL_Surface *source;


public:

//Constructeurs par d�faut et surcharg�s
Graphics();
Graphics(string nom_img);
Graphics(string nom_img,int x);
Graphics(string nom_img, int x,int y,int pv, int pix) ;

//M�thode qui charge l'image et fixe la source
bool load_files();

//Affiche aux coordonn�es de l'entit� le clip (l'�l�ment de la source) mis en argument
void apply_surface( SDL_Rect* clip);

void apply_surface2(  int x, int y, SDL_Surface* source, SDL_Rect* clip );

//Initialise les fonctions SDL et la fen�tre
bool init();

//Lib�re la surface charg�e comme source
void clean_up();

//Lib�re la surface charg�e comme screen et met fin � l'utilisation des m�thodes SDL
void clean_up_screen();

//M�thodes retournant les diff�rentes caract�ristiques de l'entit� Graphics
SDL_Surface* get_screen();
SDL_Surface* get_source();
Timer get_timer();
int get_pv();
int getx();
int gety();

//Retourne en fonction des coordonn�es, le num�ro de la case du terrain
int get_numcase();

//Change les diff�rents �l�ments mis en protected
void set_source(SDL_Surface* Source);
void set_position(int x, int y);
void set_pv(int x);



};