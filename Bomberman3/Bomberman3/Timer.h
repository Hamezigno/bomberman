#include "constante.h"

#pragma once 

//On initialise la classe Timer qui gèrera toutes les méthodes relatives au temps
class Timer
{
    private:
    //Le temps au moment du lancement du Timer
    int startTicks;

    //Le temps stocké où le moment est mis en pause
    int pausedTicks;

    //Les différents statuts du Timer
    bool paused;
    bool started;

    public:
    //Constructeur par défaut du Timer
    Timer();

    //Les différentes méthodes pour modifier les statuts du Timer
    void start();
    void stop();
    void pause();
    void unpause();

    //Rend le nombre de secondes depuis le lancement du Timer
    int get_ticks();

    //Méthodes qui rendent les statuts du Timer
    bool is_started();
    bool is_paused();
	
};