#include "constante.h"

#pragma once 

//On initialise la classe Timer qui g�rera toutes les m�thodes relatives au temps
class Timer
{
    private:
    //Le temps au moment du lancement du Timer
    int startTicks;

    //Le temps stock� o� le moment est mis en pause
    int pausedTicks;

    //Les diff�rents statuts du Timer
    bool paused;
    bool started;

    public:
    //Constructeur par d�faut du Timer
    Timer();

    //Les diff�rentes m�thodes pour modifier les statuts du Timer
    void start();
    void stop();
    void pause();
    void unpause();

    //Rend le nombre de secondes depuis le lancement du Timer
    int get_ticks();

    //M�thodes qui rendent les statuts du Timer
    bool is_started();
    bool is_paused();
	
};