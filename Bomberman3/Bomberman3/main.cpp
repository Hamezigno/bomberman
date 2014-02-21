#include"Jeu.h"


using namespace std;


int main( int argc, char* args[] )
{
	//Initialisation d'un booléen indiquant si oui ou non le jeu continue à tourner ou pas
	bool quit=false;

	//Construction d'un élément de la classe auquel on donne le nombre de personnes participant à la partie
	Jeu partie;

	//Préparation du menu 
	partie.set_menu() ;

	//Préparation de la partie
	partie.init_jeu();

	

	//Tant que le jeu est en cours
	while (quit==false)
	{
		//Indicateur de temps écoulé depuis la dernière mise à jour de l'affichage
		unsigned int elapsed;

		//Temps au moment de la dernière mise à jour de l'affichage
		unsigned int lasttime = SDL_GetTicks();	

		
		//Gère la gestion des touches et indique si la partie est toujours en cours ou non
		quit=partie.handle_events();

		//Gère l'affichage des différentes instances de la classe jeu
		partie.show();

		//Gère la fin de la partie
		partie.set_fin_partie();

		//Gère la gestion des touches et indique si la partie est toujours en cours ou non
		//quit=partie.handle_events();

		partie.pousse_bombe();

		partie.update();

		//Met à jour le temps écoulé depuis la dernière mise à jour de l'affichage 
		elapsed = SDL_GetTicks()-lasttime; 

		//Si ce temps est plus petit que 70 millisecondes
		if (elapsed<70)
		{	
			//Relance l'affichage
			SDL_Delay(70-elapsed);
		}
	}

	//Libère l'espace alloué pour le chargement des différentes images utilisées
	partie.clean();


	return 0;
}