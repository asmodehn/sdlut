#include "Video/SDLEngine.hh"

#include "Video/SDLSurfaceLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
    namespace SDL
    {

		//loading the default RGBSurface from the Resources as logo
		DefaultEngine::DefaultEngine() : _logo(0)
	    {
			SurfaceLoader loader;
#ifdef HAVE_OPENGL
			loader.resetOpengl(true);
#endif
			try{
				_logo = loader.load( RWOps( _defaultImage,sizeof(_defaultImage) ) );
			}
			catch(std::exception &)
			{
				Log << nl << " ERROR : Unable to load Default Logo ! ";
				//shouldnt happen. therefore no rethrow. ( assumed RAII )
				//if this occurs, behavior is totally unknown...
			}
	    }
	    
		//this render function should not modify the engine
		void DefaultEngine::render(VideoSurface & screen) const
		{
			screen.blit(*_logo,Point( screen.getWidth() - _logo->getWidth(), screen.getHeight() - _logo->getHeight()));
		}

			//to initialise the engine, just called once before any render
		bool DefaultEngine::init(int width, int height)
		{
			return true;
		}

		//get called everytime the display is resized
		bool DefaultEngine::resize(int width, int height)
		{
			return true;
		}
		
		DefaultEngine::~DefaultEngine()
		{
		}
	}
}

