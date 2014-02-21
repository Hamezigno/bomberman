#include "Graphics.h"

//Constructeur par d�faut 
Graphics::Graphics(){
source = NULL;
//D�fini le support d'affichage 
screen = SDL_SetVideoMode( 750, 750, 32, SDL_SWSURFACE );
e_pv =0;
e_x=0;
e_y=0;
dec_pixel = 0;
}

//Constructeur surcharg� avec pour argument le nom du fichier � charger
Graphics::Graphics( string nom_img)
{
filename=nom_img;

source = NULL;
screen = SDL_SetVideoMode( 750, 750, 32, SDL_SWSURFACE );
e_pv =0;
e_x=0;
e_y=0;
dec_pixel = 0;

}

//Constructeur surcharg� avec pour arguments le nom du fichier � charger et le nombre de points de vie de l'entit� � l'initialisation
Graphics::Graphics(string nom_img,int x)
{
filename=nom_img;
e_pv =x;


source = NULL;
screen = SDL_SetVideoMode( 750, 750, 32, SDL_SWSURFACE );
e_x=0;
e_y=0;
dec_pixel = 0;

}

//Constructeur surcharg� avec pour arguments le nom du fichier � charger, le nombre de points de vie et la position de l'entit� 
//� l'initialisation ainsi que le d�calage de pixel � utiliser
Graphics::Graphics(string nom_img,int x,int y,int pv,int pix)
{
filename=nom_img;
e_pv =pv;
e_x=x;
e_y=y;
dec_pixel = pix;

source = NULL;
screen = SDL_SetVideoMode( 750, 750, 32, SDL_SWSURFACE );
}

void Graphics::apply_surface( SDL_Rect* clip)
{
    //Initialise le rectangle de l'image en source
    SDL_Rect offset;

    //Fixe la taille du rectangle � afficher
    offset.x = e_x*BOMBER_WIDTH; 
    offset.y = (e_y)*BOMBER_WIDTH-dec_pixel;

    //Affiche le rectangle (clip) mis en argument de la source sur le screen, fix�s comme argument de la classe
    SDL_BlitSurface( source, clip, screen, &offset );
}

// Fonction apply_surface mais avec plus d'arguments : est l� pour g�rer les objets qui n'ont pas de "clips" mais qui ont un fond simple (comme le Menu)
void Graphics::apply_surface2(  int x, int y, SDL_Surface* source,  SDL_Rect* clip)
{

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;
   SDL_BlitSurface( source, clip, screen, &offset );
}

bool Graphics::init()
{
    //Test sur l'initialisation des syst�mes SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Test sur la mise en place du fond
    if( screen == NULL )
    {
        return false;
    }

    //Mise en place de la fen�tre de jeu et de son nom
    SDL_WM_SetCaption( "Bomberman", NULL );

    //Retourne vrai si tout a bien �t� initialis�
    return true;
}



bool Graphics::load_files()
{
    //Charge l'image dont le nom a �t� mis � la construction
   source = load_image( filename );
	


    //Test sur le bon chargement de cette image
   if( source == NULL )
    {
        return false;
    }

    //Retourne vrai si ce chargement est effectif
    return true;
}
void Graphics::clean_up()
{
    //Lib�re la surface charg�e en tant que source
    SDL_FreeSurface( source );
}

void Graphics::clean_up_screen()
{
    //Lib�re la surface charg�e en tant que screen
    SDL_FreeSurface( screen );
	
    //Mettre fin aux proc�dures SDL
    SDL_Quit();
}


SDL_Surface* Graphics::get_screen()
{	
	//Retourne la surface affect�e en screen
	return screen;
}

SDL_Surface* Graphics::get_source()
{
	//Retourne la surface affect�e en source
	return source;
}

int Graphics::getx()
{	
	//Retourne  la position en abscisse de l'entit�
	return e_x ;
}

int Graphics::gety()
{
	//Retourne  la position en ordonn�e de l'entit�
	return e_y ;
}

int Graphics::get_pv()
{
	//Retourne  le nombre de points de vie de l'entit�
	return e_pv;
}

Timer Graphics::get_timer()
{
	//Retourne le Timer affect� � l'entit�
	return e_timer;
}

int Graphics::get_numcase()
{
	//Retourne le num�ro de la case o� se trouve l'entit�
	return (15*e_y+e_x);
}

void Graphics::set_source(SDL_Surface* Source)
{
	//Remplace la surface en source par celle plac�e en argument
	source = Source;
}

void Graphics::set_position(int x, int y)
{
	//Change les coordonn�es de l'entit� par celle mises en argument
	e_x=x;
	e_y=y;
}

void Graphics::set_pv(int x){
	//Fixe les points de vie de l'entit� avec l'entier plac� en argument
	e_pv=x;
}


