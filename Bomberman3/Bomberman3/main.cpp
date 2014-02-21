#include"Jeu.h"


using namespace std;


int main( int argc, char* args[] )
{
	//Initialisation d'un bool�en indiquant si oui ou non le jeu continue � tourner ou pas
	bool quit=false;

	//Construction d'un �l�ment de la classe auquel on donne le nombre de personnes participant � la partie
	Jeu partie;

	//Pr�paration du menu 
	partie.set_menu() ;

	//Pr�paration de la partie
	partie.init_jeu();

	

	//Tant que le jeu est en cours
	while (quit==false)
	{
		//Indicateur de temps �coul� depuis la derni�re mise � jour de l'affichage
		unsigned int elapsed;

		//Temps au moment de la derni�re mise � jour de l'affichage
		unsigned int lasttime = SDL_GetTicks();	

		
		//G�re la gestion des touches et indique si la partie est toujours en cours ou non
		quit=partie.handle_events();

		//G�re l'affichage des diff�rentes instances de la classe jeu
		partie.show();

		//G�re la fin de la partie
		partie.set_fin_partie();

		//G�re la gestion des touches et indique si la partie est toujours en cours ou non
		//quit=partie.handle_events();

		partie.pousse_bombe();

		partie.update();

		//Met � jour le temps �coul� depuis la derni�re mise � jour de l'affichage 
		elapsed = SDL_GetTicks()-lasttime; 

		//Si ce temps est plus petit que 70 millisecondes
		if (elapsed<70)
		{	
			//Relance l'affichage
			SDL_Delay(70-elapsed);
		}
	}

	//Lib�re l'espace allou� pour le chargement des diff�rentes images utilis�es
	partie.clean();


	return 0;
}