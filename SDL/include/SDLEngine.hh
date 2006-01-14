#ifndef SDL_ENGINE_HH
#define SDL_ENGINE_HH

/*******************************************************************************
 * Interface with other systems
 ******************************************************************************/

//Classes d'interface avec un moteur 3D...
// a voir si cette classe doit etre la scene, la camera ou les 2
//(cf UI interface)
#include "SDLConfig.hh"
#include "SDLColor.hh"
#include "SDLRGBSurface.hh"

namespace RAGE
{
    namespace SDL
{
#ifdef HAVE_OPENGL
    class GLEngine
    {
        float BGColorRed,BGColorGreen, BGColorBlue;

    public:
        GLEngine() :  BGColorRed(0.0f),BGColorGreen(0.0f), BGColorBlue(0.0f)
        {}
        virtual void render(void) const;
        virtual bool init(int width, int height);
        virtual bool resize(int width, int height);
        virtual bool setBGColor(float r, float g, float b);
        virtual bool saveContent(void)
        {
            return true;
        }
        virtual bool restoreContent(void)
        {
            return false;
        }
    };

#endif

    //Classes d'interface avec un moteur 2D
    //Meme probleme que precedemment

    class VideoSurface; //further reference to access the display surface to be able to blit on it

    class Engine
    {

    protected:
        VideoSurface * _screen;

        //todo : make it an embedded object not a pointer... might need some improvements in BaseSurface for the creation/copy
        RGBSurface * _backupscreen;
        RGBSurface _defaultlogo;

        Color _background;

    public:
        Engine();
        virtual ~Engine();
        virtual void render(void) const;
        virtual bool init(int width, int height);
        virtual bool resize(int width, int height);
        virtual bool setBGColor(const Color & color);
        virtual bool saveContent(void);
        virtual bool restoreContent(void);
    };
}
}

#endif //SDL_ENGINE_HH
