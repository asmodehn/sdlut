#include "Video/Display.hh"
//#include "System/SDLEventManager.hh"

#include "SDLConfig.hh"


namespace RAGE
{
namespace SDL
{

bool Display::setResizable(bool val)
//TODO : not really useful here, transfer to screenbuffer with accessor
{
    return pvm_screen.setResizable(val);
}

bool Display::setFullscreen(bool val)
// TODO : not really useful here, transfer to screenbuffer with accessor
{
    return pvm_screen.setFullscreen(val);
}

bool Display::setNoFrame(bool val)
// TODO : not really useful here, transfer to screenbuffer with accessor
{
    return pvm_screen.setNoFrame(val);
}

#ifdef WK_OPENGL_FOUND
bool Display::setOpenGL(bool val)
// TODO : not really useful here, transfer to screenbuffer with accessor
{
    return pvm_screen.setOpenGL(val);
}
#endif

//to check the current properties of the display
bool Display::isFullscreen()
// TODO : not really useful here, transfer to screenbuffer with accessor
{
    return pvm_screen.isFullscreen();
}

bool Display::isResizable()
{
    return pvm_screen.isResizable();
}
bool Display::isOpenGL()
{
    return pvm_screen.isOpenGL();
}
bool Display::isNoFrame()
{
    return pvm_screen.isNoFrame();
}


Display::Display(std::string title, Manager * manager)
        :	m_initcb(NULL),m_resizecb(NULL), m_newframecb(NULL), m_rendercb(NULL),
        pvm_manager(manager),
        pvm_screen(ScreenBuffer(0,0,0, manager)),
        pvm_window(title),
        //myLoadingScreen(NULL),
        ShowingLoadingScreen(false),
        m_exitMainLoop(false)
{
}

Display::Display( const Display & d)
        :   m_initcb(d.m_initcb),m_resizecb(d.m_resizecb), m_newframecb(d.m_newframecb), m_rendercb(d.m_rendercb),
        pvm_manager(d.pvm_manager),
        pvm_screen(ScreenBuffer(0,0,0, d.pvm_manager)),
        pvm_window(d.pvm_window.getTitle()),
        //myLoadingScreen(NULL),
        ShowingLoadingScreen(false),
        m_exitMainLoop(false)
{
}

Display::~Display()
{
}

void Display::applyBGColor() const
{
    pvm_screen.applyBGColor();
}


bool Display::setDisplay (unsigned int width, unsigned int height, unsigned int bpp)
{
    pvm_screen.setWidth(width);

    pvm_screen.setHeight(height);

    pvm_screen.setBPP(bpp);

    return true; // for now always true.
    //TODO: Checks must be done to make sure the required resolution is supported
}

bool Display::show()
{
    bool res = pvm_screen.show();
    //calling user init callback if it exists
    if ( m_initcb ) res = res && m_initcb->call( pvm_screen.getWidth() , pvm_screen.getHeight() );
    return res;
}

bool Display::hide()
{
    return pvm_screen.hide();
}

bool Display::resizeDisplay (int width, int height)
{
    bool res = pvm_screen.resize(width,height);

    //calling user callback for resize if it exists
    if ( m_resizecb ) res = res && m_resizecb->call(width, height);
    return res;
}


/*		void Window::ShowLoadingScreen(
			const std::string& Loading_BG_Filename,
			const std::string& Loading_Global_Msg,
			#ifdef WK_SDLTTF_FOUND
				const Font& Loading_Global_Msg_Font,
			#endif
			const std::string& Loading_Specific_Msg,
			#ifdef WK_SDLTTF_FOUND
				const Font& Loading_Specific_Msg_Font,
			#endif
			const Rect& Progress_Bar_Infos )
        {
		try
        {
		#ifdef DEBUG
            Log << nl << "Window::ShowLoadingScreen() called ..." << std::endl;
		#endif
			ShowingLoadingScreen = true;

			//Screen->getVideoInfo()->getPixelFormat()->getBitsPerPixel();

			applyBGColor();

			if (myLoadingScreen != NULL)
				delete myLoadingScreen, myLoadingScreen = NULL;

			SurfaceLoader loader;
			std::auto_ptr<RGBSurface> surf_apt = loader.load(Loading_BG_Filename);
			myLoadingScreen = new LoadingScreen(surf_apt, Loading_Global_Msg, Loading_Global_Msg_Font, Loading_Specific_Msg, Loading_Specific_Msg_Font, Progress_Bar_Infos );

			myLoadingScreen->render(pvm_screen);

		#ifdef DEBUG
            Log << nl << "Window::ShowLoadingScreen() done." << std::endl;
		#endif

		}
		catch(std::exception & e)
        {
			Log << nl << "Exception caught in Window::ShowLoadingScreen() : " << e.what();
			throw std::logic_error( "Exception caught in Window::ShowLoadingScreen() : " + (std::string)e.what() );
		} catch (...) {
			Log << nl << "Unhandled Exception in Window::ShowLoadingScreen()";
			throw std::logic_error( "Unhandled Exception in Window::ShowLoadingScreen()" );
		}
		}

		void Window::UpdateLoadingScreen( const unsigned short& Progress_Percent, const std::string& Loading_Specific_Msg )
		{
		try
        {
			if (ShowingLoadingScreen && myLoadingScreen != NULL )
			{
				myLoadingScreen->Progress_Percent = std::min(100, std::max(0, (int)Progress_Percent)); //force the progression to be between 0 and 100
				myLoadingScreen->Loading_Specific_Msg = Loading_Specific_Msg;
				myLoadingScreen->render(pvm_screen);
			}
			else
			{
			#ifdef DEBUG
				throw std::logic_error( "Trying to update a loading screen that doesn't exists." );
			#endif
			}

		}
		catch(std::exception & e)
        {
			Log << nl << "Exception caught in Window::UpdateLoadingScreen() : " << e.what();
			throw std::logic_error( "Exception caught in Window::UpdateLoadingScreen() : " + (std::string)e.what() );
		} catch (...) {
			Log << nl << "Unhandled Exception in Window::UpdateLoadingScreen()";
			throw std::logic_error( "Unhandled Exception in Window::UpdateLoadingScreen()" );
		}
		}

		void Window::HideLoadingScreen()
		{
		try
        {
		#ifdef DEBUG
            Log << nl << "Window::HideLoadingScreen() called ..." << std::endl;
		#endif

			ShowingLoadingScreen = false;

			if (myLoadingScreen != NULL)
				delete myLoadingScreen, myLoadingScreen = NULL;

		#ifdef DEBUG
            Log << nl << "Window::HideLoadingScreen() done." << std::endl;
		#endif

		}
		catch(std::exception & e)
        {
			Log << nl << "Exception caught in Window::HideLoadingScreen() : " << e.what();
			throw std::logic_error( "Exception caught in Window::HideLoadingScreen() : " + (std::string)e.what() );
		} catch (...) {
			Log << nl << "Unhandled Exception in Window::HideLoadingScreen()";
			throw std::logic_error( "Unhandled Exception in Window::HideLoadingScreen()" );
		}
		}
*/

bool Display::mainLoop(unsigned int framerate, unsigned int eventrate)
{
    if (ShowingLoadingScreen)
    {
        framerate = 1, eventrate = 1;
    }
    assert(framerate > 0 && "framerate must be greater than 0 !");
    bool res = false;

    //if the videosurface is displayed ( ie the content of the window is shown )
    if (pvm_screen.show()) // is shown only ? can game not run hidden ??
        //TODO : separate event and render loop
    {
        unsigned long lastframe = SDL_GetTicks();
        unsigned long lastevent = SDL_GetTicks();
        //unsigned long newlastrender= SDL_GetTicks();
        //unsigned long lastrender= newlastrender;
        while (! m_exitMainLoop )
        {
            //handling all the events
            //
            if ( SDL_GetTicks() - lastevent >= 1000/eventrate)//wait if needed - IMPORTANT otherwise the next value is far too high (not 0)
            {
                pvm_eventmanager.handleAll();
                lastevent = SDL_GetTicks();
            }

            //Callback for preparing new frame
            if ( m_newframecb )
                m_newframecb->call( framerate, SDL_GetTicks() - lastframe );

            //applying the background
            //if (!ShowingLoadingScreen)
            applyBGColor();

            pvm_screen.renderpass(framerate, lastframe);

            //if (!ShowingLoadingScreen)
            if ( m_rendercb )
                m_rendercb->call( pvm_screen );

            pvm_screen.refresh(framerate, lastframe);

        }
        res = true;
    }
    else
    {
        Log << nl << "ERROR : Screen Buffer @ " << &pvm_screen << " can't be used !" << std::endl;
        Log  << nl <<" Ignoring mainLoop call." << std::endl;
    }

    if (!res)
    {
        Log  << nl << "An error occured when trying to launch the main loop, make sure you have initialized everything." << std::endl;
        Log  << nl <<" Ignoring mainLoop call." << std::endl;
    }
    return res;

}







}//SDL

}//RAGE

