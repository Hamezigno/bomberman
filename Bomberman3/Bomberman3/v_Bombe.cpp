#include "v_Bombe.h"

//Constructeur par défaut qui fixe le nombre de bombes disponible initialement à 1 et 
//la puissance de feu à 2 cases dans toutes les directions
v_Bombe::v_Bombe(): nb_bombes_max(1),puissance(2){}
	
void	v_Bombe::init_inventaire()
{
	//Adapte la taille du vecteur de bombes avec  celle du nombre maximal de bombes disponibles
	inventaire.resize(nb_bombes_max);

	//Charge l'image relative aux bombes et aux bombes
	SDL_Surface *Source=load_image("BOMBE.png");

	//Pour chaque bombe du vecteur
	for(int i(0);i<nb_bombes_max;i++)
	{
		//Fixe la source de chaque bombe avec l'image qui vient d'être chargée
		inventaire[i].set_source(Source);
	}
	explosion = Mix_LoadWAV("explosion.wav");
}


void v_Bombe::set_clip()
{

	//Défini le cadre de chaque rectangle d'image de bombe à afficher (BOMBER_WIDTH de 50 pixels qui est l'unité de mesure générale de ce programme)
	for(int i(0);i<4;i++)
	{

	//Fixe le niveau en abscisse et en ordonnée du coin en haut à gauche du rectangle
	b_clip[i].x = BOMBER_WIDTH*i;
	b_clip[i].y = 0;

	//Fixe la largeur et la hauteur du rectangle
	b_clip[i].w = BOMBER_WIDTH;
	b_clip[i].h = BOMBER_WIDTH;
	}

	//Aucun affichage
	b_clip[4].x = BOMBER_WIDTH*5;
	b_clip[4].y = 0;
	b_clip[4].w = BOMBER_WIDTH;
	b_clip[4].h = BOMBER_WIDTH;
	

//Images des flammes
	//Flamme horizontale
	b_clip[5].x = BOMBER_WIDTH;
	b_clip[5].y = 150;
	b_clip[5].w = BOMBER_WIDTH;
	b_clip[5].h = BOMBER_WIDTH;

	//Flamme verticale
	b_clip[6].x = BOMBER_WIDTH*2;
	b_clip[6].y = 100;
	b_clip[6].w = BOMBER_WIDTH;
	b_clip[6].h = BOMBER_WIDTH;
	
	// Case du milieu
	b_clip[7].x = BOMBER_WIDTH*2;
	b_clip[7].y = 150;
	b_clip[7].w = BOMBER_WIDTH;
	b_clip[7].h = BOMBER_WIDTH;
	
	//Bout de la flamme gauche
	b_clip[8].x = 0;
	b_clip[8].y = 150;
	b_clip[8].w = BOMBER_WIDTH;
	b_clip[8].h = BOMBER_WIDTH;
	
	// Bout flamme droite
	b_clip[9].x = BOMBER_WIDTH*4;
	b_clip[9].y = 150;
	b_clip[9].w = BOMBER_WIDTH;
	b_clip[9].h = BOMBER_WIDTH;

	//Bout flamme haut
	b_clip[10].x = BOMBER_WIDTH*2;
	b_clip[10].y = 50;
	b_clip[10].w = BOMBER_WIDTH;
	b_clip[10].h = BOMBER_WIDTH;

	//Bout flamme bas
	b_clip[11].x = BOMBER_WIDTH*4;
	b_clip[11].y = 50;
	b_clip[11].w = BOMBER_WIDTH;
	b_clip[11].h = BOMBER_WIDTH;
}


void v_Bombe::show(Terrain &terrain)
{
	//Pour chaque bombe du vecteur
	for(int i(0);i<nb_bombes_max;i++)
	{		
			//Si le statut de la bombe est nowhere
			if (inventaire[i].get_statut() == BOMBE_nowhere) 
			{
				//Ne rien afficher à l'emplacement de la bombe,
				inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety(),&b_clip[4]);
			}

			//Si la bombe a été posé
			else if (inventaire[i].get_statut() == BOMBE_put) 
			{
				//A chaque quart de seconde pendant les trois secondes avant l'explosion normale de la bombe
				for(int j(0);j<=2;j++)
				{
					//Si la bombe est dans le premier quart d'une seconde
					if(((inventaire[i].get_timer().get_ticks()-1000*j)>=0)&&(inventaire[i].get_timer().get_ticks()-1000*j)<250)
					{
						//Afficher la grosse bombe à l'emplacement de la bombe
						inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety(),&b_clip[0]);
					}

					//Si la bombe est dans le second quart d'une seconde
					else if(((inventaire[i].get_timer().get_ticks()-1000*j)>=250)&&((inventaire[i].get_timer().get_ticks()-1000*j)<500))
					{
						//Afficher la  bombe moyenne à l'emplacement de la bombe
						inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety(),&b_clip[1]);
					}

					//Si la bombe est dans le troisième quart d'une seconde
					else if (((inventaire[i].get_timer().get_ticks()-1000*j)>=500)&&((inventaire[i].get_timer().get_ticks()-1000*j)<750))
					{
						//Afficher la petite bombe à l'emplacement de la bombe
						inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety(),&b_clip[2]);
					}

					//Si la bombe est dans le dernier quart d'une seconde
					else if (((inventaire[i].get_timer().get_ticks()-1000*j)>=750)&&((inventaire[i].get_timer().get_ticks()-1000*j)<1000))
					{
						//Afficher la grosse bombe à l'emplacement de la bombe
						inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety(),&b_clip[3]);
					}
				}
			
			//Si la bombe a été placé depuis plus de 3 secondes ou explose en réaction d'une autre bombe
			if ((inventaire[i].chaîne(terrain)+inventaire[i].get_timer().get_ticks())>=3000)
			{

				// Quand la bombe explose on joue un effet sonore d'explosion
				Mix_PlayChannel( -1, explosion, 0 );
				//Si l'initialisation des flammes n'a pas encore été faite
				if(inventaire[i].get_f_flag()==0)
				{
					//Fixe le temps avant détonation de la bombe correspondant au nombre de secondes écoulées avant son explosion normale
					//Ce temps est 0 si la bombe explose bien au bout des 3 secondes
					inventaire[i].set_temps(inventaire[i].chaîne(terrain));

					//Initialise les vecteurs de flamme
					inventaire[i].set_all(terrain) ;

					//Met l'indicateur d'initialisation des flammes à 1
					inventaire[i].set_f_flag(1); 
				}
	
				//Affiche la flamme du milieu à l'emplacement de la bombe
				inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety(),&b_clip[7]);	
			
				// Affichage de la flamme de gauche
					//Si la taille du vecteur de flammes à gauche n'est pas nul
					if(inventaire[i].get_g()!=0)
					{
						//Si la taille de la flamme est égal à la puissance de la bombe
						if(inventaire[i].get_g()==puissance)
						{
							//Pour chacun des éléments constituant la flamme vers la gauche
							for (int j(1);j<=puissance;j++) 
							{
								//Si cet élément est le dernier du vecteur
								if(j==puissance)
								{
									//Affiche au bout de la flamme, le bout de la flamme de gauche
									inventaire[i].apply_surface(inventaire[i].getx()-puissance,inventaire[i].gety(),&b_clip[8]);
								}
								//Pour les autres éléments de la flamme
								else
								{
									//Affiche la flamme horizontale
									inventaire[i].apply_surface(inventaire[i].getx()-j,inventaire[i].gety(),&b_clip[5]);
								}
							}
						}
						//Si la flamme est plus petite que la puissance de la bombe dans cette direction
						else
						{
							//Pour tout les éléments du vecteur de flamme
							for (int j(1);j<=inventaire[i].get_g();j++)
							{
								//Affiche la flamme horizontale
								inventaire[i].apply_surface(inventaire[i].getx()-j,inventaire[i].gety(),&b_clip[5]);
							}
						}
					}

				// Affichage de la flamme de droite
					//Si la taille du vecteur de flammes à droite n'est pas nul
					if(inventaire[i].get_d()!=0)
					{
						//Si la taille de la flamme est égal à la puissance de la bombe
						if(inventaire[i].get_d()==puissance)
						{
							//Pour chacun des éléments constituant la flamme vers la droite
							for (int j(1);j<=puissance;j++) 
							{
								//Si cet élément est le dernier du vecteur
								if(j==puissance)
								{
									//Affiche au bout de la flamme, le bout de la flamme de droite
									inventaire[i].apply_surface(inventaire[i].getx()+puissance,inventaire[i].gety(),&b_clip[9]);
								}
								//Pour les autres éléments de la flamme
								else
								{
									//Affiche la flamme horizontale
									inventaire[i].apply_surface(inventaire[i].getx()+j,inventaire[i].gety(),&b_clip[5]);
								}
							}
						}
						//Si la flamme est plus petite que la puissance de la bombe dans cette direction
						else
						{
							//Pour tout les éléments du vecteur de flamme
							for (int j(1);j<=inventaire[i].get_d();j++)
							{
								//Affiche la flamme horizontale
								inventaire[i].apply_surface(inventaire[i].getx()+j,inventaire[i].gety(),&b_clip[5]);
							}
						}
					}
		
				// Affichage de la flamme du haut
					//Si la taille du vecteur de flammes vers le haut n'est pas nul
					if(inventaire[i].get_h()!=0)
					{
						//Si la taille de la flamme est égal à la puissance de la bombe
						if(inventaire[i].get_h()==puissance)
						{
							//Pour chacun des éléments constituant la flamme vers le haut
							for (int j(1);j<=puissance;j++)
							{
								//Si cet élément est le dernier du vecteur
								if(j==puissance)
								{
										//Affiche au bout de la flamme, le bout de la flamme du haut
										inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety()-puissance,&b_clip[10]);
								}
								//Pour les autres éléments de la flamme
								else
								{
									//Affiche la flamme verticale
									inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety()-j,&b_clip[6]);
								}
							}
						}
						//Si la flamme est plus petite que la puissance de la bombe dans cette direction
						else
						{	
							//Pour tout les éléments du vecteur de flamme
							for(int j(1);j<=inventaire[i].get_h();j++)
							{
								//Affiche la flamme verticale
								inventaire[i].apply_surface(inventaire[i].getx(), inventaire[i].gety()-j,&b_clip[6]);
							}
						}
					}


				// Affichage de la flamme du bas
					//Si la taille du vecteur de flammes vers le bas n'est pas nul
					if(inventaire[i].get_b()!=0)
					{
						//Si la taille de la flamme est égal à la puissance de la bombe
						if(inventaire[i].get_b()==puissance)
						{
							//Pour chacun des éléments constituant la flamme vers la bas
							for (int j(1);j<=puissance;j++)
							{
								//Si cet élément est le dernier du vecteur
								if(j==puissance)
								{
									//Affiche au bout de la flamme, le bout de la flamme du bas
									inventaire[i].apply_surface(inventaire[i].getx(),inventaire[i].gety()+puissance,&b_clip[11]);
								}
								//Pour les autres éléments de la flamme
								else
								{
									//Affiche la flamme verticale
									inventaire[i].apply_surface(inventaire[i].getx(), inventaire[i].gety()+j,&b_clip[6]);
								}
			
							}
						}
						//Si la flamme est plus petite que la puissance de la bombe dans cette direction
						else
						{
							//Pour tout les éléments du vecteur de flamme
							for(int j(1);j<=inventaire[i].get_b();j++)
							{
								//Affiche la flamme verticale
								inventaire[i].apply_surface(inventaire[i].getx(), inventaire[i].gety()+j,&b_clip[6]);
							}
						}
					}
			}
	
			//Si la bombe a explosé depuis plus de 600 millisecondes
			if((inventaire[i].get_timer().get_ticks())>=(3600-inventaire[i].get_temps()))
			{
				//Fixe le statut de la bombe en nowhere
				inventaire[i].set_statut(BOMBE_nowhere);

				//Remet l'indicateur d'initialisation des flammes à 0
				inventaire[i].set_f_flag(0);

				//Arrête le Timer de la bombe
				inventaire[i].get_timer().stop();

				//Met les points de vie de la bombe à 0
				inventaire[i].set_pv(0);

				//Retire le statut de feu des cases affectées par la bombe
				inventaire[i].clean_feu(terrain);

			}
		}
	}
}


int v_Bombe::bombe_dispo()
{
	//Le numéro du dernier élément du vecteur
	int i=nb_bombes_max-1;

	int j=0;

//On teste qu'au moins une bombe est disponible, si aucune ne l'est
//la somme des points de vie des bombes du vecteur sera égale au nombre maximum de bombes disponible

	//Pour chaque bombe du vecteur
	for(int u(0);u<nb_bombes_max-1;u++)
	{
		//Ajoute à la somme des points de vie ceux de la bombe numéro u
		j=j+inventaire[u].get_pv();
	}

	//Si la somme des points de vie est égale au nombre maximum de bombes disponible
	if (j==nb_bombes_max)
	{
		//Retourne -1 signifiant qu'aucune bombe est disponible
		return -1;
	}
	//Si cette somme est d'une autre valeur, au moins une bombe est disponible
	else
	{
		//Tant que la fin du vecteur n'a pas été atteinte et que 
		//la i ème bombe du vecteur est active sur le terrain
		while ((inventaire[i].get_pv()==1)&&(i>=0))
		{
			//Passe à la bombe précédente du vecteur
			i=i-1;
		}
		//Retourne la première bombe du vecteur disponible
		return i;
	}
}

void v_Bombe::clean_up()
{
		//Libère l'espace dédié pour le chargement de l'image des bombes et flammes
		inventaire[0].clean_up();
}


void v_Bombe::ajouter_bombe()
{
	//Augmente de 1 le nombre maximal de bombes disponibles
	nb_bombes_max+=1;

	//Créée un nouvel objet Bombe de la puissance du vecteur au bout du vecteur
	inventaire.push_back(Bombe(puissance));

	//Fixe la source de la bombe créée
	inventaire[nb_bombes_max-1].set_source(inventaire[0].get_source());
	
}

void v_Bombe::augmenter_puissance(int x)
{
	//Si la nouvelle puissance est au moins égale à 1
	if((puissance+x)>=2)
	{
		//Si la nouvelle puissance est supérieure à 8
		if((puissance+x)>8)
		{
			//Remet la puissance du vecteur à 8
			puissance=8;
		}

		//Si la nouvelle puissance est entre 1 et 8
		else
		{
			//Remplace la puissance du vecteur par la nouvelle
			puissance=puissance+x;
		}
	}

	//Pour chaque bombe du vecteur
	for (int i(0);i<nb_bombes_max;i++)
	{
		//Met à jour la puissance de la bombe
		inventaire[i].set_puissance(puissance);
	}
}

Bombe* v_Bombe::get_bombe(int i)
{
	//Retourne à la i ème bombe du vecteur
	return &inventaire[i];
}

int v_Bombe::get_puissance()
{
	//Retourne la puissance de la bombe
	return puissance;
}

int v_Bombe::get_nb_bombes_max()
{
	//Retourne le nombre maximum de bombes disponibles
	return nb_bombes_max;
}