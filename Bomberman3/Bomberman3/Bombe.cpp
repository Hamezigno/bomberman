#include "Bombe.h"

//Par défaut, utilise le constructeur surchargé avec seulement le nom de l'image liée à la bombe, 
//fixe la puissance à 2, son statut à nowhere et tout les arguments relatifs à son feu nul
Bombe::Bombe() : Graphics("BOMBE.png"),b_statut(BOMBE_nowhere), b_puissance(2),f_haut(0),f_bas(0),f_gauche(0),f_droite(0),f_flag(0),temps_avant_detonation(0)  {}

//Initialise les arguments de la bombe de la même façon que le constructeur par défaut hormis pour celui de la puissance qui prend l'entier mis en argument
Bombe::Bombe(int x) : Graphics("BOMBE.png"),b_statut(BOMBE_nowhere),b_puissance(x),f_haut(0),f_bas(0),f_gauche(0),f_droite(0),f_flag(0),temps_avant_detonation(0)  {}


void Bombe::clean_feu(Terrain &terrain)
{
	//Retire le statut de feu sur la case où se trouvait la bombe sur l'élément de la classe Terrain placé en argument
	terrain.get_terrain(e_x + 15*(e_y)).set_feu(false);

	//Pour chaque élément de chacun des 4 vecteurs de feu de la bombe
	for(int i(0);i<b_puissance;i++)
	{
			//Si l'élément numéro i de chacun des 4 vecteurs est une case de type nowhere,
			//on retire le statut feu de cette case sur l'élément de la classe Terrain placé en argument
			if(v_haut[i]==3)
			{
			terrain.get_terrain(e_x + 15*(e_y - (i+1))).set_feu(false);
			}
			if(v_bas[i]==3)
			{
				terrain.get_terrain(e_x + 15*(e_y + (i+1))).set_feu(false);
			}
			if(v_gauche[i]==3)
			{
				terrain.get_terrain(e_x-(i+1) + 15*e_y ).set_feu(false);
			}
			if(v_droite[i]==3)
			{
				terrain.get_terrain(e_x+(i+1) + 15*e_y ).set_feu(false);
			}
	}
}


void Bombe::apply_surface(int x, int y , SDL_Rect* clip)
{
    //Initialise le rectangle de l'image en source
    SDL_Rect offset;

    //Fixe la taille du rectangle à afficher et où l'afficher
	//sur le screen suivant les coordonnées mis en argument
    offset.x = x*BOMBER_WIDTH; 
    offset.y = y*BOMBER_WIDTH;

    //Affiche le rectangle (clip) mis en argument de la source sur le screen, fixés comme argument de la classe
    SDL_BlitSurface( source, clip, screen, &offset );
}


int Bombe::chaîne(Terrain &terrain){

	//Si la case où se trouve la bombe a comme statut qu'il n'y a pas de bombe dessus
	if (terrain.get_terrain(e_x+15*e_y).getbombe()==0)
	{
		//Initialisation de l'entier égal au temps restant avant que la bombe explose normalement
		int a=3000-e_timer.get_ticks();
		
		//Si ce temps restant est positif
		if(a>0)
		{
			//Retourne ce temps restant
			return a;
		}
		else 
		{
			//Sinon retourne un temps égal à 0
			return 0;
		}
	}
	else
	{
		//Sinon retourne un temps égal à 0
		return 0;
	}
}

int Bombe::PlaceDansVecteur(int y, vector<int> W) 
{
	//Initialisation de l'entier qui correspondra à la place dans le vecteur mis en argument
	int integer =0;

	//Tant que l'entier à la place égale à l'entier integer est différent de celui placé en argument et que l'on a pas atteint le bout du vecteur
	while  ((y!=W[integer])&&(integer <= W.size()))
	{
		//On avance dans le vecteur
		integer ++ ;
	}
	

	return integer;
}


void Bombe::set_vecteurs(Terrain &terrain) {

	//Fixe le feu comme actif pour la case où se trouve la bombe au sein de l'entité Terrain mis en argument
	terrain.get_terrain(e_x + 15*(e_y)).set_feu(true);

	//Pour chaque élément de chacun des 4 vecteurs de flammes
	for (int i(0);i<b_puissance; i++)
	{
	//Pour le vecteur vers le haut
		//Si la case concernée n'est pas en dehors du cadre
		if((e_y-(i+1))>=0)
		{
			//L'élément numéro i du vecteur prend la valeur du statut de la case concernée
			v_haut[i] = terrain.get_terrain(e_x + 15*(e_y - (i+1))).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'élément numéro i du vecteur prend la valeur 4
			v_haut[i]=4;
		}

		//Si la case concernée est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la première brique ou pilier
		if((v_haut[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_haut),PlaceDansVecteur(CASE_pilier, v_haut))))
		{
			//La case associée devient en feu
			terrain.get_terrain(e_x + 15*(e_y - (i+1))).set_feu(true);
		}
	
	//Pour le vecteur vers le bas
		//Si la case concernée n'est pas en dehors du cadre
		if((e_y+(i+1))<15)
		{
			//L'élément numéro i du vecteur prend la valeur du statut de la case concernée
			v_bas[i] = terrain.get_terrain(e_x + 15*(e_y + (i+1))).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'élément numéro i du vecteur prend la valeur 4
			v_bas[i]=4;
		}
		//Si la case concernée est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la première brique ou pilier
		if((v_bas[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_bas),PlaceDansVecteur(CASE_pilier, v_bas))))
		{
			//La case associée devient en feu
			terrain.get_terrain(e_x + 15*(e_y + (i+1))).set_feu(true);
		}

	//Pour le vecteur vers la gauche
		//Si la case concernée n'est pas en dehors du cadre
		if((e_x-(i+1))>=0)
		{
			//L'élément numéro i du vecteur prend la valeur du statut de la case concernée
			v_gauche[i] = terrain.get_terrain(e_x-(i+1) + 15*e_y ).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'élément numéro i du vecteur prend la valeur 4
			v_gauche[i]=4;
		}
		//Si la case concernée est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la première brique ou pilier
		if((v_gauche[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_gauche),PlaceDansVecteur(CASE_pilier, v_gauche))))
		{
			//La case associée devient en feu
			terrain.get_terrain(e_x-(i+1) + 15*e_y ).set_feu(true);
		}

	//Pour le vecteur vers la droite
		//Si la case concernée n'est pas en dehors du cadre
		if((e_x+(i+1))<15)
		{
			//L'élément numéro i du vecteur prend la valeur du statut de la case concernée
			v_droite[i] = terrain.get_terrain(e_x+(i+1) + 15*e_y ).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'élément numéro i du vecteur prend la valeur 4
			v_droite[i]=4;
		}
		//Si la case concernée est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la première brique ou pilier
		if((v_droite[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_droite),PlaceDansVecteur(CASE_pilier, v_droite))))
		{
			//La case associée devient en feu
			terrain.get_terrain(e_x+(i+1) + 15*e_y ).set_feu(true);
		}
	}

	//Pour chacun des quatre vecteurs de flamme, si une brique se trouve avant un pilier dans le
	//vecteur de flamme, la case est se trouve la brique obtient le statut feu

	if ((PlaceDansVecteur(CASE_pilier, v_haut) ) > (PlaceDansVecteur(CASE_brique, v_haut) ))
	{
	terrain.get_terrain(e_x + 15*(e_y -1- PlaceDansVecteur(CASE_brique, v_haut))).set_feu(true);
	}
	if ((PlaceDansVecteur(CASE_pilier, v_bas) ) > (PlaceDansVecteur(CASE_brique, v_bas) ))
	{
	terrain.get_terrain(e_x + 15*(e_y +1+PlaceDansVecteur(CASE_brique, v_bas))).set_feu(true);
	}
	if ((PlaceDansVecteur(CASE_pilier, v_gauche) ) > (PlaceDansVecteur(CASE_brique, v_gauche) ))
	{
	terrain.get_terrain(e_x-1 - PlaceDansVecteur(CASE_brique, v_gauche)+15*e_y ).set_feu(true);
	}
	if ((PlaceDansVecteur(CASE_pilier, v_droite) ) > (PlaceDansVecteur(CASE_brique, v_droite) )) 
	{
	terrain.get_terrain(e_x+1 + PlaceDansVecteur(CASE_brique, v_droite)+ 15*e_y ).set_feu(true);
	}
}


void Bombe::set_longueur_feu() 
{	
	int a =0;

	//Pour chaque direction, on fixe la longueur du feu comme le minimum du premier pilier
	//et brique atteinte ou sa puissance initiale

	//Vers le haut
	a= min(PlaceDansVecteur(1, v_haut) , PlaceDansVecteur(0, v_haut));

	if(a<=b_puissance)
	{
		f_haut =a;
	}
	else
	{
		f_haut=b_puissance;
	}

	//Vers le bas
	a=min(PlaceDansVecteur(1, v_bas) , PlaceDansVecteur(0, v_bas));

	if(a<=b_puissance)
	{
		f_bas =a;
	}
	else
	{
		f_bas=b_puissance;
	}

	//Vers la gauche
	a=min(PlaceDansVecteur(1, v_gauche) , PlaceDansVecteur(0, v_gauche));

	if(a<=b_puissance)
	{
		f_gauche =a;
	}
	else
	{
		f_gauche=b_puissance;
	}

	//Vers la droite
	a = min(PlaceDansVecteur(1, v_droite) , PlaceDansVecteur(0, v_droite));

	if(a<=b_puissance)
	{
		f_droite =a;
	}
	else
	{
		f_droite=b_puissance;
	}
}

void Bombe::set_all(Terrain &terrain) 
{
	//Refixe la taille de chacun des 4 vecteurs de flamme
	v_haut.resize(b_puissance );
	v_bas.resize(b_puissance );
	v_gauche.resize(b_puissance);
	v_droite.resize(b_puissance );

	//Initialise les valeurs des 4 vecteurs de flamme
	set_vecteurs(terrain);

	//Fixe les longueurs des 4 flammes
	set_longueur_feu();
	
		
}

void Bombe::set_statut(int x) 
{
	//Remplace le statut de la bombe par celui mis en abscisse
	b_statut =x;

	//Si le nouveau statut est BOMBE_put
	if (x==BOMBE_put)
	{
		//Initialise le Timer de la bombe
		e_timer.start();
	}

}

void Bombe::set_puissance(int x)
{	
	//Change la puissance de la bombe par celle mise en argument
	b_puissance=x;
}

void Bombe::set_f_flag(int x)
{
	//Remplace l'indicateur flag par celui mis en abscisse
	f_flag=x;
}

void Bombe::set_temps(int x)
{
	//Remplace le temps avant détonation par celui mis en abscisse
	temps_avant_detonation=x;
}


int Bombe::get_statut()
{
	//Retourne le statut de la bombe
	return b_statut;
}

int Bombe::getPuissance()
{
	//Retourne la puissance de la bombe
	return b_puissance ;
}



int Bombe::get_b()
{
	//Retourne la taille du feu de la bombe vers le bas
	return f_bas;
}

int Bombe::get_d()
{
	//Retourne la taille du feu de la bombe vers la droite
	return f_droite;
}

int Bombe::get_g()
{
	//Retourne la taille du feu de la bombe vers la gauche
	return f_gauche;
}

int Bombe::get_h()
{
	//Retourne la taille du feu de la bombe vers le haut
	return f_haut;
}

int Bombe::get_f_flag()
{
	//Retourne l'indicateur flag de la bombe
	return f_flag;
}

int Bombe::get_temps()
{
	//Retourne le temps_avant_détonation de la bombe
	return temps_avant_detonation;
}




