#include "Timer.h"

using namespace std;

#pragma once

//Classe mère qui receuille l'ensemble des méthodes liées aux applications graphiques
class Graphics{

private:

//Nom du fichier qui sera chargé
string filename;

//Ces différents éléments sont en proected afin qu'ils puissent être modifiés dans les classes filles
protected:

//Nombre de points de vie de l'entité
int e_pv; 

//Eléments fixant la position dans le niveau
int e_x;
int e_y;

//Nombre de pixels de décalage pour afficher cette entité par rapport à l'unité de 50 pixels utilisée dans tout le programme
int dec_pixel ;

//Un Timer spécifique à l'entité
Timer e_timer;

//Un pointeur vers la surface sur laquelle s'appliquera l'affichage
SDL_Surface *screen;

//La surface sur laquelle figure l'image à afficher
SDL_Surface *source;


public:

//Constructeurs par défaut et surchargés
Graphics();
Graphics(string nom_img);
Graphics(string nom_img,int x);
Graphics(string nom_img, int x,int y,int pv, int pix) ;

//Méthode qui charge l'image et fixe la source
bool load_files();

//Affiche aux coordonnées de l'entité le clip (l'élément de la source) mis en argument
void apply_surface( SDL_Rect* clip);

void apply_surface2(  int x, int y, SDL_Surface* source, SDL_Rect* clip );

//Initialise les fonctions SDL et la fenêtre
bool init();

//Libère la surface chargée comme source
void clean_up();

//Libère la surface chargée comme screen et met fin à l'utilisation des méthodes SDL
void clean_up_screen();

//Méthodes retournant les différentes caractéristiques de l'entité Graphics
SDL_Surface* get_screen();
SDL_Surface* get_source();
Timer get_timer();
int get_pv();
int getx();
int gety();

//Retourne en fonction des coordonnées, le numéro de la case du terrain
int get_numcase();

//Change les différents éléments mis en protected
void set_source(SDL_Surface* Source);
void set_position(int x, int y);
void set_pv(int x);



};