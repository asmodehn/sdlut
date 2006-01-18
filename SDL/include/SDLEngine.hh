#ifndef SDL_ENGINE_HH
#define SDL_ENGINE_HH

/*******************************************************************************
 * Interface with other systems
 ******************************************************************************/

#include "SDLConfig.hh"
#include "SDLColor.hh"
#include "SDLRGBSurface.hh"

namespace RAGE
{
    namespace SDL
{



    class VideoSurface; //further reference to access the display surface to be able to blit on it

//2D Engine interface
    class Engine
    {

    protected:
        VideoSurface * _screen;

        //todo : make it an embedded object not a pointer... might need some improvements in BaseSurface for the creation/copy
        RGBSurface * _backupscreen;
        RGBSurface _defaultlogo;

        Color _background;

    public:
        Engine() throw (std::logic_error);
        virtual ~Engine();
        virtual std::string name() const { return "Engine"; }
        virtual bool render(void) const;
        virtual bool init(int width, int height);
        virtual bool resize(int width, int height);
        virtual bool setBGColor(const Color & color);
        virtual bool saveContent(void);
        virtual bool restoreContent(void);
    };

#ifdef HAVE_OPENGL
//Extension to 3D Engine interface
    class GLEngine : public Engine
    {

    public:
        GLEngine() throw (std::logic_error);
        virtual std::string  name() const { return "GLEngine"; }
        virtual bool render(void) const;
        virtual bool init(int width, int height);
        virtual bool resize(int width, int height);
        virtual bool setBGColor(const Color & color);
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
}
}

#endif //SDL_ENGINE_HH
