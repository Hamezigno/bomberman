#include "Timer.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std; 


Timer::Timer()
{
    //Initialisation des variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Lancement du Timer
    started = true;

    //Enlève le statut de pause du Timer
    paused = false;

    //Récupération de l'heure actuelle
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Arrêt du Timer
    started = false;

    //Arrêt de la pause
    paused = false;
}

void Timer::pause()
{
    //Si le Timer a été initialisé et n'est pas en pause
    if( ( started == true ) && ( paused == false ) )
    {
        //Mettre le Timer en pause
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //Indicatrice de statut de pause du Timer
    if( paused == true )
    {
        //Enlève la pause du Timer
        paused = false;

        //Relance le décompte du temps
        startTicks = SDL_GetTicks() - pausedTicks;

        //Réinitialise le temps du Timer en pause
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //Indicatrice sur le statut de lancement
    if( started == true )
    {
        //Indicatrice de statut de pause du Timer
        if( paused == true )
        {
            //Rend le temps passé par le Timer en pause
            return pausedTicks;
        }
        else
        {
            //Retourne le temps écoulé jusqu'à présent depuis le moment où le Timer a été initialisé
            return SDL_GetTicks() - startTicks;
        }
    }

    //Retourne le Timer n'a pas encore été initialisé
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}