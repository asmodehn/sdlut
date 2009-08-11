//Classe abstraite pour gerer les membres de classe devant etre executés en thread
#ifndef SDLTHREADEDOBJECT_HH
#define SDLTHREADEDOBJECT_HH

/*******************************************************************************
 * Abstract Class to manage threads.
 ******************************************************************************/

#define SDLTHREADEDOBJECT_DEBUG

#include <SDL.h>
#include <SDL_thread.h>

class SDLThreadedObject
{
private:
    //ID du thread associe a l'instance de la classe
    SDL_Thread* _thread;

    //arguments a passer a la fonction
    void* _args;

    //Valeur de retour du thread
    int _status;

protected:

    //Constructeur et Destructeur
    SDLThreadedObject();
    virtual ~SDLThreadedObject();

    //lance l'execution en thread
    int run(void * arg);

    //Pointeur vers la fonction a executer
    static int entryPoint(void*);

    //Fonctions a surcharger pour effectuer le traitement approprié
    virtual void setup();
    virtual int execute(void*);

    //Accesseurs aux arguments
    inline void * args() const
    {
        return _args;
    };
    inline void args(void* a)
    {
        _args = a;
    };

public:
    //Creation du thread et lancement
    void launch (void* arg);
    inline void launch (void)
    {
        launch(NULL);
    };
    //Attente de fin du thread
    int wait();
};
#endif
