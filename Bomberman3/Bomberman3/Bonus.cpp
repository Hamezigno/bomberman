#include "Bonus.h"

//Par d�faut, utilise le constructeur surcharg� avec seulement le nom de l'image et fixe le type du bonus � 0 (aucun bonus)
Bonus::Bonus() :Graphics("BONUS.png"),type_bonus(0){}

void Bonus::set_clip()
{	
	//D�fini le cadre de chaque rectangle d'image � afficher (BOMBER_WIDTH de 50 pixels qui est l'unit� de mesure g�n�rale de ce programme)
	for(int i(0);i<8;i++)
	{
	//Fixe le niveau en abscisse et en ordonn�e du coin en haut � gauche du rectangle
	bo_clip[i].x = BOMBER_WIDTH*i;
	bo_clip[i].y = 0;

	//Fixe la largeur et la hauteur du rectangle
	bo_clip[i].w = BOMBER_WIDTH;
	bo_clip[i].h = BOMBER_WIDTH;
	}
}

void Bonus::set_bonus(int x)
{
	//Remplace le statut du bonus par celui mis en abscisse
	type_bonus=x;
}

int Bonus::get_type()
{
	//Retourne le type du bonus
	return type_bonus;
}

void Bonus::show()
{
	//Test sur le nombre de points de vie du bonus
	if (e_pv==1)
	{
		//Affiche le rectangle correspondant au type du bonus
		apply_surface(&bo_clip[type_bonus-1]);
	}
	
}
