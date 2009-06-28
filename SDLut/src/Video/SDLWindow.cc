#include "Video/SDLWindow.hh"
#include "System/SDLEventManager.hh"

#include "Video/SDLSurfaceLoader.hh"

#include "SDLConfig.hh"
#include "SDLResources.inc"

namespace RAGE
{
    namespace SDL
    {


        bool Window::iconify(void)
        {
            return ( SDL_WM_IconifyWindow() != 0 );
        }

        void Window::grabInput()
        {
            SDL_WM_GrabInput( SDL_GRAB_ON );
        }

        void Window::releaseInput()
        {
            SDL_WM_GrabInput( SDL_GRAB_OFF );
        }

        bool Window::isInputGrabbed()
        {
            return SDL_WM_GrabInput( SDL_GRAB_QUERY ) == SDL_GRAB_ON;
        }

        void Window::setCaption(std::string title, std::string iconname)
        {
            _title=title;
            _iconname=iconname;
            SDL_WM_SetCaption(_title.c_str(), _iconname.c_str());
            //seticon needed or ?
        }

        void Window::setIcon(const RGBSurface & icon)
        {
			_icon.reset(new RGBSurface( icon ) );
            SDL_WM_SetIcon( const_cast<SDL_Surface*>(&(_icon->get_rSDL())) , NULL);
        }

        //old version
        void Window::getCaption(std::string & title, std::string & iconname)
        {
            char t[256]= {}; //size ??
            char i[256]= {}; //size ??
            SDL_WM_GetCaption((char**)&t,(char**)&i); // to test on gcc.. be careful about long strings...
            title=std::string(t);
            iconname=std::string(i);
        }

        std::string Window::getTitle()
        {
            char t[256]= {}; //size ??
            SDL_WM_GetCaption((char**)&t,NULL); // to test on gcc.. be careful about long strings...
            return std::string(t);

        }
        std::string Window::getIconName()
        {
            char i[256]= {}; //size ??
            SDL_WM_GetCaption(NULL,(char**)&i); // to test on gcc.. be careful about long strings...
            return std::string(i);
        }

        bool Window::setResizable(bool val) //TODO : not really useful here, transfer to screenbuffer with accessor
        {
            return pvm_screen.setResizable(val);
        }

        bool Window::setFullscreen(bool val) // TODO : not really useful here, transfer to screenbuffer with accessor
        {
		return pvm_screen.setFullscreen(val);
        }

        bool Window::setNoFrame(bool val) // TODO : not really useful here, transfer to screenbuffer with accessor
        {
		return pvm_screen.setNoFrame(val);
        }

#ifdef HAVE_OPENGL
        bool Window::setOpenGL(bool val) // TODO : not really useful here, transfer to screenbuffer with accessor
        {
		return pvm_screen.setOpenGL(val);
        }
#endif

	//to check the current properties of the display
	bool Window::isFullscreen() // TODO : not really useful here, transfer to screenbuffer with accessor
	{
		return pvm_screen.isFullscreen();
	}

	bool Window::isResizable()
	{
		return pvm_screen.isResizable();
	}
	bool Window::isOpenGL()
	{
		return pvm_screen.isOpenGL();
	}
	bool Window::isNoFrame()
	{
		return pvm_screen.isNoFrame();
	}

        Window::Window(std::string title)
		 :	_title(title),
			pvm_screen(ScreenBuffer(0,0,0)),
			_icon(0),
			//myLoadingScreen(NULL),
			ShowingLoadingScreen(false),
			m_exitMainLoop(false)
        {
#ifdef DEBUG
            Log << nl << "Window::Window(" << title << ") called ..." ;
#endif

            try
            {
				SurfaceLoader loader;
				RWOps _iconres = RWOps( _defaultIcon, sizeof(_defaultIcon));  
				_icon = loader.load( _iconres );
				if ( ( _icon.get() == 0 ) || ( ! _icon->initialized() ) )
				{
					throw std::logic_error("Error initializing default Icon !");
				}
			
            }
            catch (std::exception &e)
            {
                Log << nl << e.what() << std::endl;
            }

			setCaption(_title );
			SDL_WM_SetIcon( const_cast<SDL_Surface*>(&_icon->get_rSDL()) , NULL);

#ifdef DEBUG

            Log << nl << "Window::Window(" << title << ") done @ "<< this ;
#endif

        }


        Window::~Window()
        {
#ifdef DEBUG
            Log << nl << "Window::~Window() called ..." << std::endl;
#endif			
			//transferred to ScreenBuffer
            //if (!_userengine) //if the user set his own engine , he is responsible for deleting it
            //    delete _engine, _engine = NULL;

			//if (myLoadingScreen != NULL)
			//	delete myLoadingScreen, myLoadingScreen = NULL;

#ifdef DEBUG

            Log << nl << "Window::~Window() done." << std::endl;
#endif

        }


        void Window::applyBGColor() const
            {
                pvm_screen.applyBGColor();
            }


        bool Window::resetDisplay (unsigned int width, unsigned int height, unsigned int bpp)
        {
			pvm_screen.hide();
			//for Backward compatibility mostly... should be done differently now
			ScreenBuffer newscreen(width, height, bpp);//to test thoroughly
			pvm_screen = newscreen;
			return pvm_screen.show();
        }
		
        bool Window::resizeDisplay (int width, int height)
        {
			return pvm_screen.resize(width,height);
        }


/*		void Window::ShowLoadingScreen(
			const std::string& Loading_BG_Filename,
			const std::string& Loading_Global_Msg,
			#ifdef HAVE_SDLTTF
				const Font& Loading_Global_Msg_Font,
			#endif
			const std::string& Loading_Specific_Msg,
			#ifdef HAVE_SDLTTF
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
		
        bool Window::mainLoop(unsigned int framerate, unsigned int eventrate)
        {
			if (ShowingLoadingScreen)
			{
				 framerate = 1, eventrate = 1;
			}
			assert(framerate > 0 && "framerate must be greater than 0 !");
			bool res = false;

#ifdef DEBUG
			assert (_engine);
#endif

			//if the videosurface is displayed ( ie the content of the window is shown )
            if (pvm_screen.show()) // is shown only ? can game not run hidden ??
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

					//TODO: make a similar eventhandlepass() method in event manager.
					
					//calling engine for prerender and render events
					//newlastrender = SDL_GetTicks();
					pvm_screen.renderpass(framerate, lastframe);
					//lastrender = newlastrender;

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




    }
}
