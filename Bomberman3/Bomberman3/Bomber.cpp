#include "Bomber.h" 

//Constructeur qui utilise le constructeur surchagé de Graphics en position (0,0) du terrain avec 1 point de vie et un décalage de pixel de 26,
//pour que l'affichage du Bomber dépasse la case mais pas sa position, le staut du Bomber est initialisé à de face et le fait qu'il joue comme vrai
Bomber::Bomber():Graphics("BOMBER_SPRITE.png",0,0,1,26), b_number(0), b_vitessex(0), b_vitessey(0),b_statut(BOMBER_DOWN),b_frame(0),
	inventaire(0),joue(true),coup_de_pied(false),pousse(-1){
son = Mix_LoadWAV("bonus.wav");
}

//Constructeur qui initialise le Bomber comme dans le constructeur par défaut mais initialise le 
//numéro du Bomber, sa position initiale et son vecteur de bombes suivant ceux mis en argument
Bomber::Bomber(int nb,int x,int y,v_Bombe* vect_bombe) : Graphics("BOMBER_SPRITE.png",x,y,1,26), b_number(nb), 
	b_vitessex(0), b_vitessey(0),b_statut(BOMBER_DOWN),b_frame(0),inventaire(0),joue(true),coup_de_pied(false),pousse(-1)
{
	inventaire=vect_bombe;
}


void Bomber::init_inventaire(){
	//Utilise la méthode pour de la classe Bombe pour charger l'image et 
	//fixer la source du vecteur de bombes du Bomber
	inventaire->init_inventaire();

	//Initialise les rectangles d'image liés aux bombes du Bomber
	inventaire->set_clip();
}

void Bomber::set_clip() { 

	//Images du déplacement vers la droite

	//Défini le cadre de chaque rectangle d'image à afficher (BOMBER_WIDTH de 50 pixels qui est l'unité de mesure générale de ce programme)
	
	//Fixe le niveau en abscisse et en ordonnée du coin en haut à gauche du rectangle
	b_Right[ 0 ].x = BOMBER_WIDTH*3;
    b_Right[ 0 ].y = BOMBER_HEIGHT*(b_number-1);

	//Fixe la largeur et la hauteur du rectangle
    b_Right[ 0 ].w = BOMBER_WIDTH;
    b_Right[ 0 ].h = BOMBER_HEIGHT;

    b_Right[ 1 ].x = BOMBER_WIDTH*4;
    b_Right[ 1 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Right[ 1 ].w = BOMBER_WIDTH;
    b_Right[ 1 ].h = BOMBER_HEIGHT;

    b_Right[ 2 ].x = BOMBER_WIDTH*5;
    b_Right[ 2 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Right[ 2 ].w = BOMBER_WIDTH;
    b_Right[ 2 ].h = BOMBER_HEIGHT;

	//Images du déplacement vers la gauche
    b_Left[ 0 ].x = BOMBER_WIDTH*9;
    b_Left[ 0 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Left[ 0 ].w = BOMBER_WIDTH;
    b_Left[ 0 ].h = BOMBER_HEIGHT;

    b_Left[ 1 ].x = BOMBER_WIDTH*10;
    b_Left[ 1 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Left[ 1 ].w = BOMBER_WIDTH;
    b_Left[ 1 ].h = BOMBER_HEIGHT;

    b_Left[ 2 ].x = BOMBER_WIDTH*11;
    b_Left[ 2 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Left[ 2 ].w = BOMBER_WIDTH;
    b_Left[ 2 ].h = BOMBER_HEIGHT;
	
	//Images du déplacement vers le haut
	b_Up[ 0 ].x =0;
    b_Up[ 0 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Up[ 0 ].w = BOMBER_WIDTH;
    b_Up[ 0 ].h = BOMBER_HEIGHT;

    b_Up[ 1 ].x = BOMBER_WIDTH;
    b_Up[ 1 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Up[ 1 ].w = BOMBER_WIDTH;
    b_Up[ 1 ].h = BOMBER_HEIGHT;

    b_Up[ 2 ].x = BOMBER_WIDTH*2;
    b_Up[ 2 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Up[ 2 ].w = BOMBER_WIDTH;
    b_Up[ 2 ].h = BOMBER_HEIGHT;

	//Images du déplacement vers le bas
	b_Down[ 0 ].x =BOMBER_WIDTH*6;
    b_Down[ 0 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Down[ 0 ].w = BOMBER_WIDTH;
    b_Down[ 0 ].h = BOMBER_HEIGHT;

    b_Down[ 1 ].x = BOMBER_WIDTH*7;
    b_Down[ 1 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Down[ 1 ].w = BOMBER_WIDTH;
    b_Down[ 1 ].h = BOMBER_HEIGHT;

    b_Down[ 2 ].x = BOMBER_WIDTH*8;
    b_Down[ 2 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Down[ 2 ].w = BOMBER_WIDTH;
    b_Down[ 2 ].h = BOMBER_HEIGHT;

	//Images de la mort du Bomber
	b_Death[ 0 ].x =BOMBER_WIDTH*12;
    b_Death[ 0 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Death[ 0 ].w = BOMBER_WIDTH;
    b_Death[ 0 ].h = BOMBER_HEIGHT;

    b_Death[ 1 ].x = BOMBER_WIDTH*13;
    b_Death[ 1 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Death[ 1 ].w = BOMBER_WIDTH;
    b_Death[ 1 ].h = BOMBER_HEIGHT;

    b_Death[ 2 ].x = BOMBER_WIDTH*14;
    b_Death[ 2 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Death[ 2 ].w = BOMBER_WIDTH;
    b_Death[ 2 ].h = BOMBER_HEIGHT;

	b_Death[ 3 ].x = BOMBER_WIDTH*15;
    b_Death[ 3 ].y = BOMBER_HEIGHT*(b_number-1);
    b_Death[ 3 ].w = BOMBER_WIDTH;
    b_Death[ 3 ].h = BOMBER_HEIGHT;
		
	}


void Bomber::Bonus_activ(Terrain& terrain)
{
	//Initialise un pointeur sur unobjet Bonus qui pointe sur le bonus de la case où se trouve le Bomber
	Bonus* Case=terrain.get_terrain(get_numcase()).getbonus();

	//Si ce bonus existe et n'a pas encore été activé
	if(Case->get_pv()==1)
	{
		//Fixe les points de vie du bonus à 0, signifiant que l'effet du bonus a été utilisé
		Case->set_pv(0);
		Mix_PlayChannel( -1, son, 0 );



		//Initialise un entier qui correspond au type du bonus
		int type=Case->get_type();

		//Bonus de type bombe
		if(type==BONUS_BOMBE)
		{
			
			//Ajoute une bombe à l'inventaire du Bomber
			inventaire->ajouter_bombe();
		}

		//Bonus de type feu
		if(type==BONUS_FEU)
		{
			
			//Augmente la puissance de feu des bombes du Bomber de 1
			inventaire->augmenter_puissance(1);
		}

		//Bonus de type feu or
		if(type==BONUS_FEU_OR)
		{
			
			//Augmente la puissance de feu des bombes du Bomber de 6
			inventaire->augmenter_puissance(6);
		}

		//Bonus de type maladie
		if(type==BONUS_MALADIE)
		{
			
			//Diminue la puissance de feu des bombes du Bomber de 1
			inventaire->augmenter_puissance(-1);
		}

		//Bonus de type coup de pied
		if(type==BONUS_PIED)
		{
			
			//Rend le pouvoir coup de pied du Bomber effectif
			coup_de_pied=true;
		}
	}
}

void Bomber::Feu_activ(Terrain &terrain)
{
	//Initialise un booléen qui indique la case où se trouve le Bomber
	//sur l'objet de type Terrain mis en argument est en feu ou non
	bool feu=terrain.get_terrain(get_numcase()).get_feu();

	//Si cette case est en feu
	if (feu==true)
	{
		//Fixe les points de vie du Bomber à 0
		e_pv=0;
	}
}




void Bomber::bomber_move(Terrain& terrain)
{
	//Si le Bomber n'est pas mort et que le Bomber est dans la partie
	if ((mort() ==false)&&(joue==true)){


	//Mouvement horizontal
		//Ajoute à la position en abscisse du Bomber sa vitesse
		e_x += b_vitessex; 
	
    
		//Si la case où sera le Bomber après son mouvement a une bombe, est un pilier, une brique ou est en feu
		if( (terrain.get_terrain((get_numcase())).getStatut()<=1)||(terrain.get_terrain((get_numcase())).getbombe()==1))
		{
			//Si la case où sera le Bomber après son mouvement a une bombe, que le pouvoir coup de pied du Bomber est actif et qu'il n'est pas statique
		if((terrain.get_terrain((get_numcase())).getbombe()==1)&&(coup_de_pied==true)&&(b_vitessex !=0))
		{
			//Le numéro de la case de la bombe poussée est celui du Bomber
			pousse=get_numcase();
		}
			//Retire de la position en abscisse du Bomber sa vitesse et annule par conséquent son mouvement
			e_x -= b_vitessex;
		}
	
//Mouvement vertical
		//Ajoute à la position en ordonnée du Bomber sa vitesse
		e_y += b_vitessey; 

		
		//Si la case où sera le Bomber après son mouvement a une bombe, est un pilier, une brique ou est en feu
		if( (terrain.get_terrain((get_numcase())).getStatut()<=1)||(terrain.get_terrain((get_numcase())).getbombe()==1))
		{
			//Si la case où sera le Bomber après son mouvement a une bombe, que le pouvoir coup de pied du Bomber est actif et qu'il n'est pas statique
			if((terrain.get_terrain((get_numcase())).getbombe()==1)&&(coup_de_pied==true)&&(b_vitessey !=0))
			{
				//Le numéro de la case de la bombe poussée est celui du Bomber
				pousse=get_numcase();
			}
			//Retire de la position en abscisse du Bomber sa vitesse et annule par conséquent son mouvement
			e_y -= b_vitessey;
		}
	}

	//Gère les intéractions du Bomber avec les bonus
	Bonus_activ(terrain);

	//Gère les intéractions du Bomber avec le feu
	Feu_activ(terrain);
}

    




void Bomber::bomber_show(Terrain &terrain)
{
	//Si le Bomber participe à la partie
	if(joue==true)
	{
		//Si le Bomber n'est pas mort
		if (mort() ==false) 
		{

			//Si le Bomber se déplace sur la gauche
			if( b_vitessex < 0 )
			{
				//Fixe le statut du Bomber comme étant de profil vers la gauche
				 b_statut = BOMBER_LEFT;

				 //Passer à l'image suivante de l'animation
				 b_frame++;
			}

			//Si le Bomber se déplace sur la droite
			else if( b_vitessex > 0 )
			{
				//Fixe le statut du Bomber comme étant de profil vers la droite
				 b_statut = BOMBER_RIGHT;

				//Passer à l'image suivante de l'animation
				 b_frame++;
			 }

			//Si le Bomber se déplace vers le haut
			else if( b_vitessey < 0 )
			{
				//Fixe le statut du Bomber comme étant de dos
				b_statut = BOMBER_UP;

				//Passer à l'image suivante de l'animation
				b_frame++;

			}

			//Si le Bomber se déplace vers le bas
			else if( b_vitessey > 0 )
			{
				 //Fixe le statut du Bomber comme étant de face
				 b_statut = BOMBER_DOWN;

				//Passer à l'image suivante de l'animation
				b_frame++;
			}

			//Si le Bomber est statique
			else
			{
				//Remet l'animation du mouvement au début et laisse le Bomber dans sa position
				b_frame = 0;
			}

			 //Si l'animation est arrivée à la fin
			 if( b_frame >= 3 )
			{
				//Remet l'animation du mouvement au début
				 b_frame = 0;
			}


			//Affiche le Bomber suivant son statut

			//S'il est de profil vers la droite
			if( b_statut == BOMBER_RIGHT )
			{
				//Affiche à la position du Bomber, l'image de numéro b_frame du
				//vecteur d'images lié à l'animation du mouvement sur la droite
				 apply_surface(&b_Right[ b_frame ] );
			}

			//S'il est de profil vers la gauche
			else if( b_statut == BOMBER_LEFT )
			{
				//Affiche à la position du Bomber, l'image de numéro b_frame du
				//vecteur d'images lié à l'animation du mouvement sur la gauche
				apply_surface(  &b_Left[ b_frame ] );
			}

			//S'il est de dos
			else if( b_statut == BOMBER_UP )
			{
				//Affiche à la position du Bomber, l'image de numéro b_frame du
				//vecteur d'images lié à l'animation du mouvement vers le haut
				apply_surface( &b_Up[ b_frame ] );
			}

			//S'il est de face
			else if( b_statut == BOMBER_DOWN )
			{
				//Affiche à la position du Bomber, l'image de numéro b_frame du
				//vecteur d'images lié à l'animation du mouvement vers le bas
				apply_surface( &b_Down[ b_frame ] );
			}
		}

		//Si le Bomber est mort
		else 
		{
			//Affiche à la position du Bomber, l'image liée à la mort du Bomber
			apply_surface(&b_Death[0]);
		}

		//Affiche les bombes du vecteur de bombes lié au Bomber
		inventaire->show(terrain);
	}
}

void Bomber::set_vitesse_x(int x)
{
	//Augmente la vitesse en abscisse du Bomber du nombre mis en argument de la méthode
	b_vitessex +=x;
}

void Bomber::set_vitesse_y(int x)
{
	//Augmente la vitesse en ordonnée du Bomber du nombre mis en argument de la méthode
	b_vitessey +=x;
}

void Bomber::set_joue(bool v)
{
	//Remplace le statut joue du Bomber par celui mis en argument
	joue=v;
}

v_Bombe* Bomber::get_inventaire()
{
	//Retourne l'inventaire du Bomber
	return inventaire;
}

bool Bomber::mort()
{
	//Si le Bomber n'a plus de point de vie
	if(e_pv==0)
	{
		//Retourne que le Bomber est mort
		return true;
	}
	else
	{
		//Sinon, retourne que le Bomber est en vie
		return false;
	}
}


int Bomber::get_pousse()
{
	//Retourne le numéro de la case de la bombe poussée
	return pousse;
}

int Bomber::get_staut()
{
	//Retourne le statut du joueur
	return b_statut;
}

void Bomber::set_pousse(int x)
{
	//Remplace la valeur de pousse du Bomber par l'entier mis en argument
	pousse=x;
}

