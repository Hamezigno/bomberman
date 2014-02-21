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

    //Enl�ve le statut de pause du Timer
    paused = false;

    //R�cup�ration de l'heure actuelle
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Arr�t du Timer
    started = false;

    //Arr�t de la pause
    paused = false;
}

void Timer::pause()
{
    //Si le Timer a �t� initialis� et n'est pas en pause
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
        //Enl�ve la pause du Timer
        paused = false;

        //Relance le d�compte du temps
        startTicks = SDL_GetTicks() - pausedTicks;

        //R�initialise le temps du Timer en pause
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
            //Rend le temps pass� par le Timer en pause
            return pausedTicks;
        }
        else
        {
            //Retourne le temps �coul� jusqu'� pr�sent depuis le moment o� le Timer a �t� initialis�
            return SDL_GetTicks() - startTicks;
        }
    }

    //Retourne le Timer n'a pas encore �t� initialis�
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