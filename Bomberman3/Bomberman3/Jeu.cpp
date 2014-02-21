#include "Jeu.h"

Jeu::Jeu()
{
	//Fixe le nombre de joueurs � haiteur du nombre mis en argument de la m�thode


	//Initialise le d�but de partie � 0
	start_game=0;
	menu_page =0 ;
	nb_joueurs = 2 ;

	//Tous les autres objets sont cr��s dynamiquement � partir de leur constructeur par d�faut
	test=new Graphics("Terrain.png");
	tps_partie=new Timer();
	terrain=new Terrain();
	inventaire1=new v_Bombe();
	inventaire2= new v_Bombe();
	inventaire3=new v_Bombe();
	inventaire4=new v_Bombe();
	rebours=new Timer(); 

	//Hormis les Bomber qui utilise leur constructeur surcharg� afin de fixer 
	//leur num�ro, leur position initiale et de leur attacher leur propre inventaire
	joueur1=new Bomber(1,1,3,inventaire1) ; 
	joueur2=new Bomber(2,13,13,inventaire2);
	joueur3=new Bomber(3,1,13,inventaire3);
	joueur4=new Bomber(4,13,3,inventaire4);

	menu_pcpal = new Menu("Menu1.png") ;
	menu_options = new Menu("Menu1.png");
	menu_options2  = new Menu("options.png");
	menu_options3 =new Menu("options2.png") ;
	choix_joueurs = new Menu("choix_joueurs.png");
	victoire = new Menu("victoire.png") ;
	egalite = new Menu("egalite.png"); 
	
}

void Jeu::set_nb_joueurs(int x) {
	nb_joueurs = x ;
}

void Jeu::set_menu() {
	//Fonction qui d�finit de mani�re d�terministe chaque page du menu (donc chaque objet de type Menu) 
	
	// Les polices, couleurs. Initialisation des sous syt�mes SDL qui g�rent le son et les polices
	TTF_Init();
	menu_pcpal->init();
	SDL_Color hoverColor = {26, 62, 137};
	SDL_Color normalColor = {150, 150, 150};

	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

	// Menu principal
	menu_pcpal->setFontStyle("ttf_pixel.ttf", 22);
	menu_pcpal->set_position(250, 140);
	menu_pcpal->setColor(normalColor, hoverColor);
	menu_pcpal->addRow("New Game");
	menu_pcpal->addRow("Options");
	menu_pcpal->addRow("Quitter");
	musique = Mix_LoadMUS( "musique.wav" );
	Mix_PlayMusic( musique,-1 );
	menu_pcpal->load_files() ;

	// page du choix du nombre de joueurs
	choix_joueurs->setFontStyle("ttf_pixel.ttf", 22);
	choix_joueurs->set_position(250, 140);
	choix_joueurs->setColor(normalColor, hoverColor);
	choix_joueurs->addRow("2");
	choix_joueurs->addRow("3");
	choix_joueurs->addRow("4");
	choix_joueurs->load_files() ;

	//options
	menu_options->setFontStyle("ttf_pixel.ttf", 22);
	menu_options->set_position(250, 140);
	menu_options->setColor(normalColor, hoverColor);
	menu_options->addRow("AZERY");
	menu_options->addRow("QWERTY");
	menu_options->addRow("Retour");
	menu_options->load_files() ;

	//options
	menu_options2->setFontStyle("ttf_pixel.ttf", 22);
	menu_options2->set_position(250, 275);
	menu_options2->setColor(normalColor, hoverColor);
	menu_options2->addRow("Retour");
	menu_options2->addRow("Menu principal");
	menu_options2->load_files() ;

	//options
	menu_options3->setFontStyle("ttf_pixel.ttf", 22);
	menu_options3->set_position(250, 275);
	menu_options3->setColor(normalColor, hoverColor);
	menu_options3->addRow("Retour");
	menu_options3->addRow("Menu principal");
	menu_options3->load_files() ;

	//Menu qui s'affiche en cas de victoire d'un joueur
	victoire->setFontStyle("ttf_pixel.ttf", 22);
	victoire->set_position(250, 275);
	victoire->setColor(normalColor, hoverColor);
	victoire->addRow("Quitter");
	victoire->load_files() ;

	//Menu qui s'affiche en cas de math nul (DRAW GAME).
	egalite->setFontStyle("ttf_pixel.ttf", 22);
	egalite->set_position(250, 275);
	egalite->setColor(normalColor, hoverColor);
	egalite->addRow("Quitter");
	egalite->load_files() ;

	// Cr�ation du r�pertoire � partir de chacune des pages
	this->menu_repertoire[0] = this->menu_pcpal ;
	this->menu_repertoire[1] = this->choix_joueurs ;
	this->menu_repertoire[2] = this->menu_options ;
	this->menu_repertoire[3] = this->menu_options2;
	this->menu_repertoire[4] = this->menu_options3 ;
	this->menu_repertoire[5] = this->victoire ; 
	this->menu_repertoire[6] = this->egalite ;



}

Jeu::~Jeu()
{
	//Supprime tout les objets cr��s dynamiquement dans le constructeur de la classe
	delete tps_partie;

	delete terrain;

	delete inventaire1;
	delete inventaire2;
	delete inventaire3;
	delete inventaire4;

	delete joueur1;
	delete joueur2;
	delete joueur3;
	delete joueur4;

	delete menu_pcpal;
	delete choix_joueurs; 
	delete menu_options ;
	delete menu_options2;
	delete menu_options3;
	delete victoire;
	delete egalite; 
}

void Jeu::init_jeu()
{
	//Initialisation des m�thodes SDL
	test->init();

	//Chargement du fond du terrain
	test->load_files();
	
	//Initialisation des cases du terrain
	terrain->init_terrain();

	//Initialisation des images du terrain � afficher
	terrain->set_clip();

	//Lancement du Timer g�n�ral de la partie
	tps_partie->start();


	//Pour chaque joueur, on initialise les fonctions graphiques de son inventaire et celles li�es � son affichage  propre

	//Joueur 1
	inventaire1->init_inventaire();
	inventaire1->set_clip();
	
	joueur1->load_files();
	joueur1->set_clip(); 

	//Joueur 2
	inventaire2->init_inventaire();
	inventaire2->set_clip();
	
	joueur2->load_files();
	joueur2->set_clip(); 

	//Joueur 3
	inventaire3->init_inventaire();
	inventaire3->set_clip();
		

	joueur3->load_files();
	joueur3->set_clip(); 
	
	//Joueur 4
	inventaire4->init_inventaire();
	inventaire4->set_clip();
	

	joueur4->load_files();
	joueur4->set_clip(); 
	
	// chargement des sons 

	bonus = Mix_LoadWAV( "bonus.wav" );
	timer_beep = Mix_LoadWAV( "timer.wav" );
	
}

bool Jeu::handle_events()
{
	//Initialisation d'un �l�ment des biblioth�ques SDL qui regroupe toutes les actions effectu�es au clavier ou avec la souris
	SDL_Event event;
	
	//Initialisation d'un bool�en qui sera retourn� � la fin de la m�thode
	bool test = false;

	//Tant qu'il y a une commande dans la liste des commandes du SDL_event
	while( SDL_PollEvent( &event ) )
        {
			//Initialisation d'un entier qui retourne pour chaque joueur le num�ro de sa 
			//premi�re bombe disponible dans son inventaire et -1 s'il n'en a aucune

			//Joueur 1
			int i=joueur1->get_inventaire()->bombe_dispo();

			//Joueur 2
			int j=joueur2->get_inventaire()->bombe_dispo();

			//Joueur 3
			int k=joueur3->get_inventaire()->bombe_dispo();

			//Joueur 4
			int l=joueur4->get_inventaire()->bombe_dispo();
			
		
       
			//Si on appuie sur une touche du clavier
			if( event.type == SDL_KEYDOWN )
			{

			switch( event.key.keysym.sym )
			
				// Avant le d�but du jeu les �v�nements ne g�rent QUE le d�placement entre les pages du menu_repertoire
			if (this->start_game==0) {
			
			// On active les fonctions de d�placement entre les liens
			case SDLK_UP: this->menu_repertoire[this->menu_page]->moveUp() ; break;
            case SDLK_DOWN: this->menu_repertoire[this->menu_page]->moveDown();  break ;
			
			// Ici on g�re la redirection des pages du menu en fonction du lien s�lectionn�
			case SDLK_RETURN : 
				if((this->menu_page ==0) && (menu_repertoire[0]->getCurrentIndex() ==2)) {
					SDL_Quit() ;
				}
				else if((this->menu_page ==0) && (menu_repertoire[0]->getCurrentIndex() ==1)) {
					retour = 0;
					this->menu_page=2 ;
				}
				else if((this->menu_page ==0) && (menu_repertoire[0]->getCurrentIndex() ==0)) {
					this->menu_page =1 ;
				}
				
				// une fois qu'on est � la page 1, on choisit les joueurs et la partie peut commencer (start_game ++)
				else if (this->menu_page ==1){

					// Le nombre de joueurs est la place du nombre dans le vecteur des liens + 2
					this->set_nb_joueurs(this->menu_repertoire[this->menu_page]->getCurrentIndex() +2) ;
					// Le jeu se lance
					start_game ++ ;
					// le chrono de dur�e de la partie se lance
					tps_partie->start();
					// le chrono du compte � rebours se lance
					rebours->start() ;
				}

				// Dans ces derni�res boucles on g�res les options et le fait d'appuyer sur "retour" ou "retour au menu principal" 
				 else if ((this->menu_page ==2)&&(this->menu_repertoire[this->menu_page]->getCurrentIndex() < 2)) {
					retour= this->menu_page;
					this->menu_page += (this->menu_repertoire[this->menu_page]->getCurrentIndex()+1) ; 
					
				}
				
				 else  if ((this->menu_page ==2)&&(this->menu_repertoire[this->menu_page]->getCurrentIndex() == 2)) {
					this->menu_page = 0 ;
				} 
				 
				  else  if( ((this->menu_page ==3)||(this->menu_page==4))&&(this->menu_repertoire[this->menu_page]->getCurrentIndex() == 0)) {
					this->menu_page = 2 ;
				  }
				  	else  if (((this->menu_page ==3)||(this->menu_page==4))&&(this->menu_repertoire[this->menu_page]->getCurrentIndex() == 1)) {
					this->menu_page = 0 ;
				  }

					// On peut aussi quitter le jeu en s�lectionnant "quitter" dans le menu principal
					else if ((this->menu_page==5)|| (this->menu_page==6)){
						SDL_Quit() ;
					}
					
					
					break; 
			}

			
				 //Suivant la touche appuy�e en clavier qwerty(touche correspondante en azerty en commentaire)
				 switch( event.key.keysym.sym )
				{
					
					//Commandes joueur 1

					//Fl�che directionnelle haut
					case SDLK_UP: 
						//Le joueur se d�place d'une case vers le haut
						joueur1->set_vitesse_y(-1) ;
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Fl�che directionnelle bas
					case SDLK_DOWN: 
						//Le joueur se d�place d'une case vers le bas
						joueur1->set_vitesse_y(1);
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Fl�che directionnelle gauche
					case SDLK_LEFT: 
						//Le joueur se d�place d'une case vers la gauche
						joueur1->set_vitesse_x(-1) ;
						//Fin des actions li�e � la pression sur cette touche
						break;


					//Fl�che directionnelle droite
					case SDLK_RIGHT: 
						//Le joueur se d�place d'une case vers la droite
						joueur1->set_vitesse_x(1) ; 
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche point d'exclamation (clavier azerty)
					case SDLK_SLASH :
						
					//Si le joueur a une bombe disponible et qu'il n'y a pas de bombe sur la case o� il se trouve
					// On ne peut poser une bombe que lorsque le GO s'affiche (4 secondes apr�s l'affichage) M�me chose pour les 3 autres joueurs
					if ((i!=-1)&&(terrain->get_terrain(joueur1->get_numcase()).getbombe()==0)&&(this->rebours->get_ticks()>=4000))
					{
						//Fixe les coordonn�es de la bombe du joueur disponible
						joueur1->get_inventaire()->get_bombe(i)->set_position(joueur1->getx(),joueur1->gety());

						//On joue un petit effet sonore lorsque le joueur pose une bombe
						Mix_PlayChannel( -1, bonus, 0 );

						//Met le statut BOMBE_put � cette bombe et la rend donc active
						joueur1->get_inventaire()->get_bombe(i)->set_statut(BOMBE_put);

						//Met 1 point de vie � cette bombe
						joueur1->get_inventaire()->get_bombe(i)->set_pv(1);

						//Indique que sur la case o� se trouve le joueur se trouve �galement une bombe d�sormais
						terrain->get_terrain(joueur1->get_numcase()).setbombe(1);
					}
					break;
					//Fin des actions li�e � la pression sur cette touche

					//Commandes joueur 2

					//Touche z
					case SDLK_w: 
						//Le joueur se d�place d'une case vers le haut
						joueur2->set_vitesse_y(-1) ;
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche s
					case SDLK_s: 
						//Le joueur se d�place d'une case vers le bas
						joueur2->set_vitesse_y(1);
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche q
					case SDLK_a: 
						//Le joueur se d�place d'une case vers la gauche
						joueur2->set_vitesse_x(-1) ; 
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche d
					case SDLK_d:
						//Le joueur se d�place d'une case vers la droite
						joueur2->set_vitesse_x(1) ; 
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche g
					case SDLK_g :
					//Si le joueur a une bombe disponible et qu'il n'y a pas de bombe sur la case o� il se trouve
					if ((j!=-1)&&(terrain->get_terrain(joueur2->get_numcase()).getbombe()==0)&&(this->rebours->get_ticks()>=4000))
					{
						//Fixe les coordonn�es de la bombe du joueur disponible
						joueur2->get_inventaire()->get_bombe(j)->set_position(joueur2->getx(),joueur2->gety());

						//Met le statut BOMBE_put � cette bombe et la rend donc active
						joueur2->get_inventaire()->get_bombe(j)->set_statut(BOMBE_put);

						//Met 1 point de vie � cette bombe
						joueur2->get_inventaire()->get_bombe(j)->set_pv(1);

						//Indique que sur la case o� se trouve le joueur se trouve �galement une bombe d�sormais
						terrain->get_terrain(joueur2->get_numcase()).setbombe(1);
					}
					//Fin des actions li�e � la pression sur cette touche
					break;

					//Commandes joueur 3
			
					//Touche i
					case SDLK_i: 
						//Le joueur se d�place d'une case vers le haut
						joueur3->set_vitesse_y(-1) ;
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche k
					case SDLK_k: 
						//Le joueur se d�place d'une case vers le bas
						joueur3->set_vitesse_y(1);
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche j
					case SDLK_j: 
						//Le joueur se d�place d'une case vers la gauche
						joueur3->set_vitesse_x(-1) ; 
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche l
					case SDLK_l:
						//Le joueur se d�place d'une case vers la droite
						joueur3->set_vitesse_x(1) ;  
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Touche p
					case SDLK_p :
					//Si le joueur a une bombe disponible et qu'il n'y a pas de bombe sur la case o� il se trouve
					if ((k!=-1)&&(terrain->get_terrain(joueur3->get_numcase()).getbombe()==0)&&(this->rebours->get_ticks()>=4000))
					{
						//Fixe les coordonn�es de la bombe du joueur disponible
						joueur3->get_inventaire()->get_bombe(k)->set_position(joueur3->getx(),joueur3->gety());

						//Met le statut BOMBE_put � cette bombe et la rend donc active
						joueur3->get_inventaire()->get_bombe(k)->set_statut(BOMBE_put);

						//Met 1 point de vie � cette bombe
						joueur3->get_inventaire()->get_bombe(k)->set_pv(1);

						//Indique que sur la case o� se trouve le joueur se trouve �galement une bombe d�sormais
						terrain->get_terrain(joueur3->get_numcase()).setbombe(1);
					}
					//Fin des actions li�e � la pression sur cette touche
					break;
			
					//Commandes joueur 4
					
					//Pav� num�rique 5
					case SDLK_KP5:
						//Le joueur se d�place d'une case vers le haut
						joueur4->set_vitesse_y(-1) ;
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Pav� num�rique 2
					case SDLK_KP2:
						//Le joueur se d�place d'une case vers le bas
						joueur4->set_vitesse_y(1); 
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Pav� num�rique 1
					case SDLK_KP1: 
						//Le joueur se d�place d'une case vers la gauche
						joueur4->set_vitesse_x(-1) ;
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Pav� num�rique 3
					case SDLK_KP3:
						//Le joueur se d�place d'une case vers la droite
						joueur4->set_vitesse_x(1) ;  
						//Fin des actions li�e � la pression sur cette touche
						break;

					//Pav� num�rique 0
					case SDLK_KP0 :
					//Si le joueur a une bombe disponible et qu'il n'y a pas de bombe sur la case o� il se trouve
					if ((l!=-1)&&(terrain->get_terrain(joueur4->get_numcase()).getbombe()==0)&&(this->rebours->get_ticks()>=4000))
					{
						//Fixe les coordonn�es de la bombe du joueur disponible
						joueur4->get_inventaire()->get_bombe(l)->set_position(joueur4->getx(),joueur4->gety());

						//Met le statut BOMBE_put � cette bombe et la rend donc active
						joueur4->get_inventaire()->get_bombe(l)->set_statut(BOMBE_put);

						//Met 1 point de vie � cette bombe
						joueur4->get_inventaire()->get_bombe(l)->set_pv(1);

						//Indique que sur la case o� se trouve le joueur se trouve �galement une bombe d�sormais
						terrain->get_terrain(joueur4->get_numcase()).setbombe(1);
					}
					//Fin des actions li�e � la pression sur cette touche
					break;
				
			
				}
				
			}

			//Si on rel�ve la pression sur une touche
			else if( event.type == SDL_KEYUP )
			{
				 //Suivant la touche du clavier relev�e en clavier qwerty(touche correspondante en azerty en commentaire)
				switch( event.key.keysym.sym )
				{
					//Commandes joueur 1

					//Fl�che directionnelle haut
					case SDLK_UP:
						//Stoppe le mouvement du joueur vers le haut
						joueur1->set_vitesse_y(1) ; 
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Fl�che directionnelle
					case SDLK_DOWN:
						//Stoppe le mouvement du joueur vers le bas
						joueur1->set_vitesse_y(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Fl�che directionnelle
					case SDLK_LEFT: 
						//Stoppe le mouvement du joueur vers la gauche
						joueur1->set_vitesse_x(1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Fl�che directionnelle
					case SDLK_RIGHT:
						//Stoppe le mouvement du joueur vers la droite
						joueur1->set_vitesse_x(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Commandes joueur 2

					//Touche z
					case SDLK_w:
						//Stoppe le mouvement du joueur vers le haut
						joueur2->set_vitesse_y(1) ; 
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Touche s
					case SDLK_s: 
						//Stoppe le mouvement du joueur vers le bas
						joueur2->set_vitesse_y(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Touche q
					case SDLK_a: 
						//Stoppe le mouvement du joueur vers la gauche
						joueur2->set_vitesse_x(1) ; 
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Touche d
            		case SDLK_d:
						//Stoppe le mouvement du joueur vers la droite
						joueur2->set_vitesse_x(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;
		
					//Commandes joueur 3
		
					//Touche i
					case SDLK_i: 
						//Stoppe le mouvement du joueur vers le haut
						joueur3->set_vitesse_y(1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Touche k
					case SDLK_k: 
						//Stoppe le mouvement du joueur vers le bas
						joueur3->set_vitesse_y(-1) ; 
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Touche j
					case SDLK_j: 
						//Stoppe le mouvement du joueur vers la gauche
						joueur3->set_vitesse_x(1) ; 
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Touche l
					case SDLK_l: 
						//Stoppe le mouvement du joueur vers la droite
						joueur3->set_vitesse_x(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;
			
					//Commandes joueur 4
					
					//Pav� num�rique 5
					case SDLK_KP5: 
						//Stoppe le mouvement du joueur vers le haut
						joueur4->set_vitesse_y(1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Pav� num�rique 2
					case SDLK_KP2:
						//Stoppe le mouvement du joueur vers le bas
						joueur4->set_vitesse_y(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Pav� num�rique 1
					case SDLK_KP1:
						//Stoppe le mouvement du joueur vers la gauche
						joueur4->set_vitesse_x(1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;

					//Pav� num�rique 3
					case SDLK_KP3:
						//Stoppe le mouvement du joueur vers la droite
						joueur4->set_vitesse_x(-1) ;
						//Fin des actions li�e � l'arr�t de la pression sur cette touche
						break;
			
				}
			}
			//Si le joueur clique sur la croix de fermeture de la fen�tre
			else if ( event.type == SDL_QUIT )
			{
				//Le bool�en retourn� � la fin de la m�thode devient vrai
				test = true;
			}
		}

	//Retourne le bool�en initialis� au d�but de la m�thode
	return test; 
}


int Jeu::update()
{       
	//Si le support n'a pas �t� correctement charg�
	if( SDL_Flip( test->get_screen() ) == -1 )            
    {
		//Retourne 1
		return 1;
    }
	//S'il a �t� correctement charg�
	else
	{
		//Retourne 0
		return 0;
	}	
}

// Fonction de compte � rebours lorsque le jeu se lance
void Jeu::compte_rebours() {

	// Chargement des polices n�cessaire et des sons
	compte_a_rebours = TTF_OpenFont( "ttf_pixel.ttf", 90);
	SDL_Color col = {26, 62, 137};

	// On change le texte affich� selon les secondes restantes le d�part
	// Avant la fin du d�compte (GO) on peut bouger mais on ne peut pas poser de bombes
	if (rebours->get_ticks()<=1000) {
		Mix_PlayChannel( -1, timer_beep, 0 );
		apply_surface2(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2,TTF_RenderText_Solid( compte_a_rebours, "3", col ) , NULL );
	}
	else if((rebours->get_ticks()>1000)&&(rebours->get_ticks()<=2000)) {
		Mix_PlayChannel( -1, timer_beep, 0 );
		apply_surface2(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2,TTF_RenderText_Solid( compte_a_rebours, "2", col ) , NULL );
	}
	else if((rebours->get_ticks()>2000)&&(rebours->get_ticks()<=3000)) {
		Mix_PlayChannel( -1, timer_beep, 0 );
		apply_surface2(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2, TTF_RenderText_Solid( compte_a_rebours, "1", col ), NULL );
	}
		else if((rebours->get_ticks()>3000)&&(rebours->get_ticks()<=4000)) {
		Mix_PlayChannel( -1, timer_beep, 0 );
		apply_surface2(SCREEN_WIDTH/2-100 , SCREEN_HEIGHT/2, TTF_RenderText_Solid( compte_a_rebours, "GO !", col ), NULL );
	}
		else if(rebours->get_ticks()>4000) {
			start_game++ ;
		}
	
}




	
// FOnction d'affichage du jeu 
void Jeu::show()
{

	// Quand le jeu n'a pas encore commenc� on ne fait qu'afficher les diff�rentes pages du menu_repertoire
	if (start_game ==0) {
		this->menu_repertoire[this->menu_page]->show() ;
	}


	
	else {

		//Si le jeu a commenc� on lance le timer et on l'affiche 
	std::stringstream time; 
	time << "Timer: " << 124000 - tps_partie->get_ticks() ;
	font_time = TTF_OpenFont( "ttf_pixel.ttf", 30 );
	timer_ticks = TTF_RenderText_Solid( font_time, time.str().c_str(), textColor );
		
		//Affichage du fond (les cases vertes du terrain)
	test->apply_surface(NULL);
	
	//Affichage des autres cases (qu'elles soient pilier ou briques)
	terrain->show();

	// Selon le temps depuis lequel est activ� le compte � rebours, on affiche ou on n'affiche pas la dur�e restant du jeu
	this->compte_rebours();
if (rebours->get_ticks()>= 4000) {
apply_surface2(0 , 0, timer_ticks, NULL );
}

	//Pour chaque joueur, gestion de son d�placement sur le m�me terrain que les autres joueurs
	//et affichage de ce joueur et de ses mouvements sur ce m�me terrain

	// On active/d�sactive les joueurs qui sont dans la partie/absents de la partie selon le nombre de joueurs 
	
	joueur1->set_joue(true) ;
	joueur2->set_joue(true) ;
	
	//Joueur 1
	
	//Mouvement
	joueur1->bomber_move(*terrain);
	//Affichage
	joueur1->bomber_show(*terrain);
	

	

	//Joueur2
	
	//Mouvement
	joueur2->bomber_move(*terrain);
	//Affichage
	joueur2->bomber_show(*terrain);

	joueur3->set_joue(false);
	joueur4->set_joue(false);
	

	//Joueur 3
	//Mouvement
	if (this->nb_joueurs >=3) {
	joueur3->set_joue(true);
	joueur3->bomber_move(*terrain);
	//Affichage
	joueur3->bomber_show(*terrain);
	}
	//Joueur 4
	//Mouvement
	if (this->nb_joueurs==4) {
	joueur4->set_joue(true);
	joueur4->bomber_move(*terrain);
	//Affichage
	joueur4->bomber_show(*terrain);
	}
	SDL_ShowCursor(0);
	}
}
void Jeu::clean()
{
	//Lib�re l'espace allou� en argument source de chacun des �l�ments de la classe Graphics ou qui en ont h�rit�e

	//L'�cran de fond
	test->clean_up();

	//Les diff�rentes cases
	terrain->clean_up();

	//Le Bomber num�ro 1
	joueur1->clean_up();
	//Ses bombes et ses flammes
	inventaire1->clean_up();

	//Le Bomber num�ro 2
	joueur2->clean_up();
	//Ses bombes et ses flammes
	inventaire2->clean_up();

	//Le Bomber num�ro 3
	joueur3->clean_up();
	//Ses bombes et ses flammes
	inventaire3->clean_up();

	//Le Bomber num�ro 4
	joueur4->clean_up();
	//Ses bombes et ses flammes
	inventaire4->clean_up();
	

	//Lib�re l'espace allou� pour le support d'affichage de toutes les �l�ments de la classe
	test->clean_up_screen();
}

// FOnction qui d�finit quand le jeu s'arr�te
void Jeu::set_fin_partie() 
{
	//Initialise un entier qui donnera le somme des points de vie des Bombers en jeu
	int pv_total;

	//Selon le nombre de joueurs s�lectionn� dans le menu on attribue une valeur � cette variable pv_total
	if(nb_joueurs==2)
	{
		pv_total = joueur1->get_pv() + joueur2->get_pv()  ;
	}
	else if(nb_joueurs==3)
	{
		pv_total = joueur1->get_pv() + joueur2->get_pv() +joueur3->get_pv();
	}
	else if (nb_joueurs==4) 
	{
		pv_total = joueur1->get_pv() + joueur2->get_pv() +joueur3->get_pv() +joueur4->get_pv() ;
	}

	//Si il ne reste qu'un seul Bomber vivant on affiche l'�cran de victoire avec le num�ro du joueur contr�lant ce bomber
	if (pv_total==1)
	{
		start_game=0 ;	
		victoire_font = TTF_OpenFont( "ttf_pixel.ttf", 25);
			SDL_Color col_victoire = {26, 62, 137};
		//R�initialise l'indicateur de d�but de partie
		this->menu_page = 5 ; 
		if (joueur1->get_pv() ==1) {
			apply_surface2(SCREEN_WIDTH/2-150 , SCREEN_HEIGHT/2, TTF_RenderText_Solid( victoire_font, "Bravo joueur 1 !", col_victoire ), NULL );
		}
		else if (joueur2->get_pv() ==1) {
			apply_surface2(SCREEN_WIDTH/2-150 , SCREEN_HEIGHT/2, TTF_RenderText_Solid( victoire_font, "Bravo joueur 2 !", col_victoire ), NULL );
		}
			else if (joueur3->get_pv() ==1) {
			apply_surface2(SCREEN_WIDTH/2-150 , SCREEN_HEIGHT/2, TTF_RenderText_Solid( victoire_font, "Bravo joueur 3 !", col_victoire ), NULL );
		}
			else if (joueur4->get_pv() ==1) {
			apply_surface2(SCREEN_WIDTH/2-150 , SCREEN_HEIGHT/2, TTF_RenderText_Solid( victoire_font, "Bravo joueur 4 !", col_victoire ), NULL );
		}


		//Arr�te le Timer g�n�ral de la partie
		tps_partie->stop();
	}

	// Un autre crit�re pour arr�ter la partie est que le temps �coul� ait d�pass� les 2 minutes (plus les 4 secondes du compte � rebours bien s�r)
	else if  (tps_partie->get_ticks() >= 124000) {
		this->start_game=0 ;
		this->menu_page = 6 ;
	}
}

Bomber* Jeu::get_joueur(int x)
{
	//Si on demande le joueur num�ro 1
	if(x==1)
	{
		//Retourne le joueur 1
		return joueur1;
	}

	//Si on demande le joueur num�ro 2
	else if(x==2)
	{
		//Retourne le joueur 2
		return joueur2;
	}

	//Si on demande le joueur num�ro 3
	else if(x==3)
	{
		//Retourne le joueur 3
		return joueur3;
	}

	//Si on demande le joueur num�ro 4
	else if(x==4)
	{
		//Retourne le joueur 4
		return joueur4;
	}
}


void Jeu::pousse_bombe()
{
	//Initialise un entier pour chaque joueur qui correspond au num�ro de la case o� il se trouve
	int a=get_joueur(1)->get_numcase();
	int b=get_joueur(2)->get_numcase();
	int c=get_joueur(3)->get_numcase();
	int d=get_joueur(4)->get_numcase();


	//Pour chaque joueur en jeu
	for (int i(1);i<=nb_joueurs;i++)
	{
		//S'il est en train de pousser une bombz
		if (get_joueur(i)->get_pousse() !=-1)
		{
			//Pour chaque joueur en jeu
			for (int k(1);k<=nb_joueurs;k++)
			{
				//Pour chaque bombe de ce joueur
				for(int l(0);l<get_joueur(k)->get_inventaire()->get_nb_bombes_max();l++)
				{
					//Si le num�ro de la case o� se trouve sa bombe est �gale au num�ro de la case de la bombe pouss�e
					if(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()==get_joueur(i)->get_pousse())
					{
						//R�initialise l'argument pousse du Bomber
						get_joueur(i)->set_pousse(-1);

						//Si le Bomber qui a pouss� la bombe est de profil vers la droite
						if(get_joueur(i)->get_staut()==BOMBER_RIGHT)
						{
							//Tant que la case de la m�me ligne mais de la colonne suivante d'o� se trouve la bombe pouss�e a pour statut nowhere et n'a pas de bombe dessus
							while((terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1).getStatut()==CASE_nowhere)&&(terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1).getbombe()==0)
								//et qu'aucun joueur ne se trouve sur cette case
								&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1)!=a)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1)!=b)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1)!=c)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1)!=d))
							{
								//Met le statut bombe � la case o� va se trouver la bombe pouss�e
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1).setbombe(1);

								//Avance la bombe pouss�e jusqu'� cette case
								get_joueur(k)->get_inventaire()->get_bombe(l)->set_position(get_joueur(k)->get_inventaire()->get_bombe(l)->getx()+1,get_joueur(k)->get_inventaire()->get_bombe(l)->gety());
								
								//Annule le statut bombe sur la case que la bombe pouss�e vient de traverser
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1).setbombe(0);
								
							}

						}
						
						if(get_joueur(i)->get_staut()==BOMBER_LEFT)
						{
							//Tant que la case de la m�me ligne mais de la colonne suivante d'o� se trouve la bombe pouss�e a pour statut nowhere et n'a pas de bombe dessus
							while((terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1).getStatut()==CASE_nowhere)&&(terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1).getbombe()==0)
								//et qu'aucun joueur ne se trouve sur cette case
								&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1)!=a)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1)!=b)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1)!=c)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1)!=d))
							{
								//Met le statut bombe � la case o� va se trouver la bombe pouss�e
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-1).setbombe(1);
								
								//Avance la bombe pouss�e jusqu'� cette case
								get_joueur(k)->get_inventaire()->get_bombe(l)->set_position(get_joueur(k)->get_inventaire()->get_bombe(l)->getx()-1,get_joueur(k)->get_inventaire()->get_bombe(l)->gety());
								
								//Annule le statut bombe sur la case que la bombe pouss�e vient de traverser
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+1).setbombe(0);
							}
						}

						
						if(get_joueur(i)->get_staut()==BOMBER_UP)
						{
							//Tant que la case de la m�me ligne mais de la colonne suivante d'o� se trouve la bombe pouss�e a pour statut nowhere et n'a pas de bombe dessus
							while((terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15).getStatut()==CASE_nowhere)&&(terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15).getbombe()==0)
								//et qu'aucun joueur ne se trouve sur cette case
								&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15)!=a)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15)!=b)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15)!=c)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15)!=d))
							{
								//Met le statut bombe � la case o� va se trouver la bombe pouss�e
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15).setbombe(1);
								
								//Avance la bombe pouss�e jusqu'� cette case
								get_joueur(k)->get_inventaire()->get_bombe(l)->set_position(get_joueur(k)->get_inventaire()->get_bombe(l)->getx(),get_joueur(k)->get_inventaire()->get_bombe(l)->gety()-1);
								
								//Annule le statut bombe sur la case que la bombe pouss�e vient de traverser
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15).setbombe(0);
							}
						}
						if(get_joueur(i)->get_staut()==BOMBER_DOWN)
						{
							//Tant que la case de la m�me ligne mais de la colonne suivante d'o� se trouve la bombe pouss�e a pour statut nowhere et n'a pas de bombe dessus
							while((terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15).getStatut()==CASE_nowhere)&&(terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15).getbombe()==0)
								//et qu'aucun joueur ne se trouve sur cette case
								&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15)!=a)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15)!=b)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15)!=c)&&((get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15)!=d))
							{
								//Met le statut bombe � la case o� va se trouver la bombe pouss�e
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()+15).setbombe(1);
								
								//Avance la bombe pouss�e jusqu'� cette case
								get_joueur(k)->get_inventaire()->get_bombe(l)->set_position(get_joueur(k)->get_inventaire()->get_bombe(l)->getx(),get_joueur(k)->get_inventaire()->get_bombe(l)->gety()+1);
								
								//Annule le statut bombe sur la case que la bombe pouss�e vient de traverser
								terrain->get_terrain(get_joueur(k)->get_inventaire()->get_bombe(l)->get_numcase()-15).setbombe(0);
							}
						}
						
					}

				}

			}
			

		}
	}

}
