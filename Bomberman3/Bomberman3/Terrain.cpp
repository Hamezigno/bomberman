#include "Terrain.h"

//On inclue les bibliothèques relatives à la génération aléatoire de nombres
#include <stdio.h>
#include <stdlib.h> // pour srand, rand et RAND_MAX
#include <time.h> // pour time 



Terrain::Terrain()
{
	//Fixe la taille du terrain à 225 (15x15)
	taille_vecteur=225;
}

void Terrain::init_terrain()
{
	//Adapte la taille du vecteur à la taille du terrain
	terrain.resize(taille_vecteur);

	//Initialise l'aléatoire
	srand(time(NULL));

	//Initialise le nombre qui prendra la valeur aléatoire entre 0 et 1
	double test=0;

	//Charge les images relatives aux cases et aux bonus
	SDL_Surface *Source_case=load_image("brique_Sprite.png");
	SDL_Surface *Source_bonus=load_image("BONUS.png");


//On dispose sur le plateau les piliers dans un premier temps
	//Pour chaque case à l'intérieur du terrain (lignes 5 à 13 et colonnes 3 à 13)
	//dont le numéro de ligne et de colonne est impair
	for (int i(4);  i<=12;i+=2) 
	{
		for (int j(2);j<=12;j+=2)
		{	
			//Fixe les points de vie de la case de la i+1 ème ligne et j+1 ème colonne à 3
			terrain[15*i + j].set_pv(3);	
		}
	}
		
	//Pour chaque ligne du terrain
	for (int i(0);i<=14; i++)
	{
		//Si cette ligne est la 1,2,3 ou 15 ème ligne du terrain
		if((i<=2)||(i==14))
		{
			//Pour chaque colonne du terrain sur ces lignes
			for (int j(0);j<=14;j++) 
			{
				//Fixe les points de vie de la case de la i+1 ème ligne et j+1 ème colonne à 3
				terrain[15*i + j].set_pv(3);
					
			}	
		}

		else
		{
			//Pour toutes les autres lignes du terrain, la case à la 1ère et dernière colonne de cette ligne
			//reçoit 3 points de vie
			terrain[15*i].set_pv(3);
			terrain[15*i+14].set_pv(3); 	
		}
	}
		
		
//On fixe le statut des cases du terrain qui ne sont pas des piliers	
		for (int i(0);i<=14;i++)
		{
			for (int j(0);j<=14;j++)
			{
				//L'entier a donne le numéro de la case
				int a=15*i+j;

				//Fixe les coordonnées de la case a
				terrain[a].set_position(j,i);

				//Fixe la source de la case a avec l'image liée aux cases
				terrain[a].set_source(Source_case);

				//Test si la case a est nowhere et n'est pas l'une des cases laissées libre pour le premier mouvement de chaque joueur
				if((terrain[a].get_pv()==0)&&(a!=46)&&(a!=47)&&(a!=61)&&(a!=193)&&(a!=207)&&(a!=208)&&(a!=57)&&(a!=58)&&(a!=73)&&(a!=181)&&(a!=196)&&(a!=197))
				{
					//Donne un nombre aléatoire entre 0 et 1
					test=(double)rand()/((double)RAND_MAX+1);
					
					//Si ce nombre est inférieur à la probabilité définie comme celle d'avoir une brique
					if(test<=prob_brique)
					{	
						//Fixe les points de vie de la case à 1	
						terrain[a].set_pv(1);
						
						//Donne un nombre aléatoire entre 0 et 1
						test=(double)rand()/((double)RAND_MAX+1);

						//Si ce nombre est inférieur à la probabilité définie comme celle d'avoir un bonus
						if(test<=prob_bonus)
						{
							//Donne un nombre aléatoire entre 0 et 1 qui déterminera le type du bonus
							test=(double)rand()/((double)RAND_MAX+1);
							
							//Bonus de type bombe
							if(test<=prob_bonus_bombe)
							{
								//Fixe le statut du bonus de la case a comme étant une bombe
								terrain[a].getbonus()->set_bonus(BONUS_BOMBE);

								//Fixe les points de vie du bonus de la case a à 1
								terrain[a].getbonus()->set_pv(1);
							}

							//Bonus de type feu
							if((test>prob_bonus_bombe)&&(test<=prob_bonus_bombe+prob_bonus_feu))
							{
								//Fixe le statut du bonus de la case a comme étant un feu
								terrain[a].getbonus()->set_bonus(BONUS_FEU);
								//Fixe les points de vie du bonus de la case a à 1
								terrain[a].getbonus()->set_pv(1);
							}

							//Bonus de type feu or
							if((test>prob_bonus_bombe+prob_bonus_feu)&&(test<=prob_bonus_bombe+prob_bonus_feu+prob_bonus_feu_or))
							{
								//Fixe le statut du bonus de la case a comme étant un feu en or
								terrain[a].getbonus()->set_bonus(BONUS_FEU_OR);
								//Fixe les points de vie du bonus de la case a à 1
								terrain[a].getbonus()->set_pv(1);
							}

							//Bonus de type maladie
							if((test>prob_bonus_bombe+prob_bonus_feu+prob_bonus_feu_or)&&(test<=prob_bonus_bombe+prob_bonus_feu+prob_bonus_feu_or+prob_maladie))
							{
								//Fixe le statut du bonus de la case a comme étant une maladie
								terrain[a].getbonus()->set_bonus(BONUS_MALADIE);
								//Fixe les points de vie du bonus de la case a à 1
								terrain[a].getbonus()->set_pv(1);
							}

							//Bonus de type coup de pied
							if((test>prob_bonus_bombe+prob_bonus_feu+prob_bonus_feu_or+prob_maladie)&&(test<=prob_bonus_bombe+prob_bonus_feu+prob_bonus_feu_or+prob_maladie+prob_pied))
							{
								//Fixe le statut du bonus de la case a comme étant un coup de pied
								terrain[a].getbonus()->set_bonus(BONUS_PIED);
								//Fixe les points de vie du bonus de la case a à 1
								terrain[a].getbonus()->set_pv(1);
							}
							
							//On initialise les fonctions graphiques des cases qui ont un bonus
							if(terrain[a].getbonus()->get_type()!=0)
							{
							//Fixe la source du bonus de la case a avec l'image liée aux bonus
							terrain[a].getbonus()->set_source(Source_bonus);

							//Initialise les différents affichages liés au bonus de la case a
							terrain[a].getbonus()->set_clip();

							//Fixe les coordonnées du bonus de la case a
							terrain[a].getbonus()->set_position(j,i);
							}
						}

					}
				}
				
			}
		}

		//On met un bonus feu à la case 0 pour être sûr de connaître une case qui a un bonus
		//pour libérer l'espace dédié aux images des bonus
		terrain[1].getbonus()->set_bonus(BONUS_FEU);
		terrain[1].getbonus()->set_source(Source_bonus);
		terrain[1].getbonus()->set_clip();
		terrain[1].getbonus()->set_position(0,0);

		

}

Case& Terrain::get_terrain(int i)
{
	//Retourne la case de numéro i
	return terrain[i];
}


void Terrain::show()
{
	//Pour chaque case du terrain
	for(int i(0);i<=(taille_vecteur-1);i++)
	{	
		//Gestion du feu de la case
		terrain[i].test_case_feu();

		//Affichage de la case numéro i suivant son statut
		terrain[i].apply_surface(&t_clip[terrain[i].getStatut()]);

		//Si la case i n'a plus de point de vie
		if(terrain[i].get_pv()==0)
		{
			//Affichage de son bonus
			terrain[i].getbonus()->show();
		}

	}
}

void Terrain::set_clip()
{
	//Défini le cadre de chaque rectangle d'image à afficher (BOMBER_WIDTH de 50 pixels qui est l'unité de mesure générale de ce programme)
	for (int i(0);i<=3;i++)
	{
	//Fixe le niveau en abscisse et en ordonnée du coin en haut à gauche du rectangle
	t_clip[i].x = BOMBER_WIDTH*i;
	t_clip[i].y = 0;

	//Fixe la largeur et la hauteur du rectangle
	t_clip[i].w = BOMBER_WIDTH;
	t_clip[i].h = BOMBER_HEIGHT2;
	}
}

void Terrain::clean_up()
{
	//Libère l'espace dédié à l'image des cases et des bonus
	terrain[1].clean_up();
	terrain[1].getbonus()->clean_up();	
}


