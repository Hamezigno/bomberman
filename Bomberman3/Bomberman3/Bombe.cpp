#include "Bombe.h"

//Par d�faut, utilise le constructeur surcharg� avec seulement le nom de l'image li�e � la bombe, 
//fixe la puissance � 2, son statut � nowhere et tout les arguments relatifs � son feu nul
Bombe::Bombe() : Graphics("BOMBE.png"),b_statut(BOMBE_nowhere), b_puissance(2),f_haut(0),f_bas(0),f_gauche(0),f_droite(0),f_flag(0),temps_avant_detonation(0)  {}

//Initialise les arguments de la bombe de la m�me fa�on que le constructeur par d�faut hormis pour celui de la puissance qui prend l'entier mis en argument
Bombe::Bombe(int x) : Graphics("BOMBE.png"),b_statut(BOMBE_nowhere),b_puissance(x),f_haut(0),f_bas(0),f_gauche(0),f_droite(0),f_flag(0),temps_avant_detonation(0)  {}


void Bombe::clean_feu(Terrain &terrain)
{
	//Retire le statut de feu sur la case o� se trouvait la bombe sur l'�l�ment de la classe Terrain plac� en argument
	terrain.get_terrain(e_x + 15*(e_y)).set_feu(false);

	//Pour chaque �l�ment de chacun des 4 vecteurs de feu de la bombe
	for(int i(0);i<b_puissance;i++)
	{
			//Si l'�l�ment num�ro i de chacun des 4 vecteurs est une case de type nowhere,
			//on retire le statut feu de cette case sur l'�l�ment de la classe Terrain plac� en argument
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

    //Fixe la taille du rectangle � afficher et o� l'afficher
	//sur le screen suivant les coordonn�es mis en argument
    offset.x = x*BOMBER_WIDTH; 
    offset.y = y*BOMBER_WIDTH;

    //Affiche le rectangle (clip) mis en argument de la source sur le screen, fix�s comme argument de la classe
    SDL_BlitSurface( source, clip, screen, &offset );
}


int Bombe::cha�ne(Terrain &terrain){

	//Si la case o� se trouve la bombe a comme statut qu'il n'y a pas de bombe dessus
	if (terrain.get_terrain(e_x+15*e_y).getbombe()==0)
	{
		//Initialisation de l'entier �gal au temps restant avant que la bombe explose normalement
		int a=3000-e_timer.get_ticks();
		
		//Si ce temps restant est positif
		if(a>0)
		{
			//Retourne ce temps restant
			return a;
		}
		else 
		{
			//Sinon retourne un temps �gal � 0
			return 0;
		}
	}
	else
	{
		//Sinon retourne un temps �gal � 0
		return 0;
	}
}

int Bombe::PlaceDansVecteur(int y, vector<int> W) 
{
	//Initialisation de l'entier qui correspondra � la place dans le vecteur mis en argument
	int integer =0;

	//Tant que l'entier � la place �gale � l'entier integer est diff�rent de celui plac� en argument et que l'on a pas atteint le bout du vecteur
	while  ((y!=W[integer])&&(integer <= W.size()))
	{
		//On avance dans le vecteur
		integer ++ ;
	}
	

	return integer;
}


void Bombe::set_vecteurs(Terrain &terrain) {

	//Fixe le feu comme actif pour la case o� se trouve la bombe au sein de l'entit� Terrain mis en argument
	terrain.get_terrain(e_x + 15*(e_y)).set_feu(true);

	//Pour chaque �l�ment de chacun des 4 vecteurs de flammes
	for (int i(0);i<b_puissance; i++)
	{
	//Pour le vecteur vers le haut
		//Si la case concern�e n'est pas en dehors du cadre
		if((e_y-(i+1))>=0)
		{
			//L'�l�ment num�ro i du vecteur prend la valeur du statut de la case concern�e
			v_haut[i] = terrain.get_terrain(e_x + 15*(e_y - (i+1))).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'�l�ment num�ro i du vecteur prend la valeur 4
			v_haut[i]=4;
		}

		//Si la case concern�e est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la premi�re brique ou pilier
		if((v_haut[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_haut),PlaceDansVecteur(CASE_pilier, v_haut))))
		{
			//La case associ�e devient en feu
			terrain.get_terrain(e_x + 15*(e_y - (i+1))).set_feu(true);
		}
	
	//Pour le vecteur vers le bas
		//Si la case concern�e n'est pas en dehors du cadre
		if((e_y+(i+1))<15)
		{
			//L'�l�ment num�ro i du vecteur prend la valeur du statut de la case concern�e
			v_bas[i] = terrain.get_terrain(e_x + 15*(e_y + (i+1))).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'�l�ment num�ro i du vecteur prend la valeur 4
			v_bas[i]=4;
		}
		//Si la case concern�e est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la premi�re brique ou pilier
		if((v_bas[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_bas),PlaceDansVecteur(CASE_pilier, v_bas))))
		{
			//La case associ�e devient en feu
			terrain.get_terrain(e_x + 15*(e_y + (i+1))).set_feu(true);
		}

	//Pour le vecteur vers la gauche
		//Si la case concern�e n'est pas en dehors du cadre
		if((e_x-(i+1))>=0)
		{
			//L'�l�ment num�ro i du vecteur prend la valeur du statut de la case concern�e
			v_gauche[i] = terrain.get_terrain(e_x-(i+1) + 15*e_y ).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'�l�ment num�ro i du vecteur prend la valeur 4
			v_gauche[i]=4;
		}
		//Si la case concern�e est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la premi�re brique ou pilier
		if((v_gauche[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_gauche),PlaceDansVecteur(CASE_pilier, v_gauche))))
		{
			//La case associ�e devient en feu
			terrain.get_terrain(e_x-(i+1) + 15*e_y ).set_feu(true);
		}

	//Pour le vecteur vers la droite
		//Si la case concern�e n'est pas en dehors du cadre
		if((e_x+(i+1))<15)
		{
			//L'�l�ment num�ro i du vecteur prend la valeur du statut de la case concern�e
			v_droite[i] = terrain.get_terrain(e_x+(i+1) + 15*e_y ).getStatut();
		}
		else
		{
			//Si la case est en-dehors du cadre, l'�l�ment num�ro i du vecteur prend la valeur 4
			v_droite[i]=4;
		}
		//Si la case concern�e est de type nowhere et que sa place dans 
		//le vecteur de flamme est avant la premi�re brique ou pilier
		if((v_droite[i]==3)&&(i<=min(PlaceDansVecteur(CASE_brique, v_droite),PlaceDansVecteur(CASE_pilier, v_droite))))
		{
			//La case associ�e devient en feu
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
	//Remplace le temps avant d�tonation par celui mis en abscisse
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
	//Retourne le temps_avant_d�tonation de la bombe
	return temps_avant_detonation;
}




