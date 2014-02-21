//Bibiliothèques SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <sstream>
#include<string>
#include<vector>

#pragma once
using namespace std;

//Initialisation des constantes graphiques 

//Les dimensions de l'écran

const int SCREEN_WIDTH = (50)*15;
const int SCREEN_HEIGHT = (50)*15;
const int SCREEN_BPP = 32;

//The frames per second
const int FRAMES_PER_SECOND = 10;

//Initialisation du format des couleurs
const SDL_Color textColor = { 0, 0, 0 };


//Initialisation des status des bombes

const int BOMBE_nowhere =0;
const int BOMBE_put = 1;

//Les dimensions du bomber

const int BOMBER_WIDTH = 50;
const int BOMBER_HEIGHT = 76;
const int BOMBER_HEIGHT2=50;

//Initialisation des postures du bomber

const int BOMBER_RIGHT = 0;
const int BOMBER_LEFT = 1;
const int BOMBER_UP = 2;
const int BOMBER_DOWN = 3;

//Initialisation des statuts des cases du terrain

const int CASE_nowhere = 3;
const int CASE_pilier = 0;
const int CASE_brique = 1 ;
const int CASE_feu=2;

//Initialisation des statuts des bonus

const int BONUS_BOMBE=1;
const int BONUS_FEU=2;
const int BONUS_FEU_OR=3;
const int BONUS_PIED=4;
const int BONUS_MALADIE=5;


//Initialisation des différentes probabilités des bonus et des briques

const double prob_brique=0.66;
const double prob_bonus=0.35;
const double prob_bonus_feu=0.30;
const double prob_bonus_bombe=0.33;
const double prob_bonus_feu_or=0.05;
const double prob_maladie=0.20;
const double prob_pied=1-prob_bonus_feu-prob_bonus_bombe- prob_bonus_feu_or-prob_maladie;

//Initialisation de la méthode de chargement des images
SDL_Surface *load_image( std::string filename );

// Fonction qui "convertit" une police en surface. Est utilisée par la classe Menu pour faciliter l'affichage des liens
SDL_Surface* surfacePolice(string file, int size, string text, SDL_Color couleur);


