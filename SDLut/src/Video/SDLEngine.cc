#include "Video/SDLEngine.hh"

#include "Video/SDLSurfaceLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
    namespace SDL
    {

		//loading the default RGBSurface from the Resources as logo
		SDLEngine::SDLEngine() : _logo(0)
	    {
			SurfaceLoader loader;
#ifdef HAVE_OPENGL
			loader.resetOpengl(true);
#endif
			try{
				RWOps _iconres( _defaultImage,sizeof(_defaultImage) );
				_logo = loader.load( _iconres );
			}
			catch(std::exception &)
			{
				Log << nl << " ERROR : Unable to load Default Logo ! ";
				//shouldnt happen. therefore no rethrow. ( assumed RAII )
				//if this occurs, behavior is totally unknown...
			}
	    }

		//this render function should not modify the engine
		bool SDLEngine::render(VideoSurface & screen) const
		{
			return screen.blit(*_logo,Point( screen.getWidth() - _logo->getWidth(), screen.getHeight() - _logo->getHeight()));
		}

			//to initialise the engine, just called once before any render
		bool SDLEngine::init(int width, int height)
		{
			return true;
		}

		//get called everytime the display is resized
		bool SDLEngine::resize(int width, int height)
		{
			return true;
		}

		SDLEngine::~SDLEngine()
		{
		}
	}
}

