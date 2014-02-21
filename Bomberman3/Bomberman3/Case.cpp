#include "Case.h"


//Par d�faut, utilise le constructeur surcharg� avec seulement le nom de l'image, fixe le feu et la bombe comme absents � l'initialisation
Case::Case () : Graphics("brique_Sprite.png") , c_bombe (0),feu(false){}
	


void Case::test_case_feu()
{	//Teste si la case est une brique et si elle est en feu
	if((e_pv==1)&&(feu==true))
	{
		//Lance le Timer de la case
		e_timer.start();

		//Fixe les points de vie de la case � 2(BOMBE_FEU)
		e_pv=2;
	}

	//Test sur le temps �coul� depuis que la case est en feu (sup�rieur � 600 ms)
	if(e_timer.get_ticks()>=600)
	{
		//Arr�te le Timer
		e_timer.stop();

		//Enl�ve le feu de la case
		feu=false;

		//Fixe les points de vie de la case � 0 (CASE_nowhere)
		e_pv=0;
	}

	//Teste si la case est en feu et en statut CASE_nowhere
	if((e_pv==0)&&(feu==true))
	{
		//Annule le statut de bombe pos�e sur la case
		c_bombe=0;

		//Met les points de vie du bonus de la case � 0 et le d�truit par la m�me occasion
		bonus.set_pv(0);
	}

}

void Case::setbombe(int x)
{
	//Fixe le statut c_bombe au niveau du nombre mis en argument
	c_bombe=x;
}
void Case::set_feu(bool x)
{
	//Remplace le statut feu de la case par celui mis en argument
	feu=x;
}

int Case::getStatut() 
{	
	//Si la case a plus de 2 points de vie
	if(e_pv>2) 
	{
		//Retourne le statut pilier
		return CASE_pilier; 
	}

	//Si la case a 1 point de vie
	else if (e_pv ==1) 
	{
		//Retourne le statut brique
		return CASE_brique;
	}

	//Si la case a  2 points de vie
	else if(e_pv==2)
	{
		//Retourne le statut brique en feu
		return CASE_feu;
	}

	//Retourne le statut rien � la case
	else return CASE_nowhere; 
}

int Case::getbombe()
{
	//Retourne le fait que la case ait une bombe ou non
	return c_bombe;
}

bool Case::get_feu()
{
	//Retourne le fait que la case soit en feu ou non
	return feu;
}

Bonus* Case::getbonus()
{
	//Retourne le bonus attach� � la case
	return &bonus;
}




