#ifndef SDL_WINDOW_HH
#define SDL_WINDOW_HH

/**
 * \class Window
 *
 * \ingroup General
 *
 * \brief Class that handle the Application Window
 *
 *
 * \author Alex
 *
 * \date 2005/12/24
 *
 * Contact: asmodehn@gna.org
 *
 */


#include "Video/ScreenBuffer.hh"
#include "Video/SDLColor.hh"
#include "System/SDLEventManager.hh"
#ifdef HAVE_SDLTTF
#include "Font/SDLFont.hh"
#endif //HAVE_SDLTTF

#include <memory>

#define DEFAULT_WINDOW_TITLE "SDLut Window"
#define DEFAULT_ICON_TITLE "SDLut"

namespace RAGE
{
    namespace SDL
    {

        //further reference to break dependency cycles
        class EventManager;

        class Window
        {
            friend class App; //to access the constructor

			//and be able to exit mainloop

			bool m_exitMainLoop;


        protected:

            std::string _title, _iconname;

            Manager* pvm_manager; // here because the manager contains also the SDL specific settings that we need...

            //here because Event are initialised along with video...
            EventManager pvm_eventmanager;

            ScreenBuffer pvm_screen;

		std::auto_ptr<RGBSurface> _icon;

            Window(std::string title, Manager* manager); // TODO :: add the icon here

        public:

            ~Window();

            //sets Display size and BPP
            bool setDisplay( unsigned int width = 0, unsigned int height = 0, unsigned int bpp = 0 );
            bool show() { return pvm_screen.show(); }
            bool hide() { return pvm_screen.hide(); }

            //just resize the screen (without changing flags, or bpp)
			//returns NULL if no screen available
			// calls Engine->resize();
            bool resizeDisplay (int width, int height);

            VideoSurface & getDisplay( void )
            {
		    //if (!pvm_screen.get()) resetDisplay();
                return pvm_screen.getDisplay();
            }

			ScreenBuffer & getScreenBuffer( )
			{
				return pvm_screen;
			}


	    inline EventManager & getEventManager()
            {
                return pvm_eventmanager;
            }


            //preset or "dynamically change" properies of the display...
            bool setResizable(bool val);
            bool setFullscreen(bool val);
#ifdef HAVE_OPENGL

            inline GLManager & getGLManager() //TEMPORARY... should matter only to screenbuffer
            {
                return pvm_screen.getGLManager();
            }
            bool setOpenGL(bool val);
#endif
            bool setNoFrame(bool val);

			//to check the current properties of the display
			bool isFullscreen();
			bool isResizable();
			bool isOpenGL();
			bool isNoFrame();

            void setBGColor(const RGBColor & color)
			{
				pvm_screen.setBGColor(color);
			}

			//fill the VideoSurface with the BGColor
			void applyBGColor() const;

            RGBColor getBGColor ()
            {
                return pvm_screen.getBGColor();
            }

            //return true on success, false otherwise
            bool iconify(void);
            void grabInput(void);
            void releaseInput(void);
            bool isInputGrabbed(void);

        protected:

            void setCaption(std::string title = DEFAULT_WINDOW_TITLE, std::string iconname = DEFAULT_ICON_TITLE );
            //oldversion
            void getCaption(std::string & title, std::string & iconname);

        public :
            inline void setTitle(std::string title)
            {
                setCaption(title);
            }
            std::string getTitle();

            void setIcon(const RGBSurface & icon);
            std::string getIconName();

		private:
			bool ShowingLoadingScreen; //indicate if a Loading Screen is being shown
			/*
			class LoadingScreen
			{
				friend class Window;
				friend class App;

			private:
				LoadingScreen(){}

			protected:
				std::auto_ptr<RGBSurface> Loading_BG;
				#ifdef HAVE_SDLTTF
					Font Loading_Global_Msg_Font, Loading_Specific_Msg_Font; //ref
				#endif
				std::string Loading_Global_Msg, Loading_Specific_Msg;
				short Progress_Percent;
				Rect Progress_Bar_Infos;

				LoadingScreen(
					std::auto_ptr<RGBSurface> _Loading_BG,
					const std::string& _Loading_Global_Msg,
					#ifdef HAVE_SDLTTF
						const Font& _Loading_Global_Msg_Font,
					#endif
					const std::string& _Loading_Specific_Msg,
					#ifdef HAVE_SDLTTF
						const Font& _Loading_Specific_Msg_Font,
					#endif
					const Rect& Progress_Bar_Infos
					) :
						Loading_BG(_Loading_BG),
						Loading_Global_Msg(_Loading_Global_Msg),
						#ifdef HAVE_SDLTTF
							Loading_Global_Msg_Font(_Loading_Global_Msg_Font),
						#endif
						Loading_Specific_Msg(_Loading_Specific_Msg),
						#ifdef HAVE_SDLTTF
							Loading_Specific_Msg_Font(_Loading_Specific_Msg_Font),
						#endif
						Progress_Bar_Infos(Progress_Bar_Infos)
				{
					Progress_Percent = 0;
				}

				~LoadingScreen()
				{}

				*//**
				 * Blit bg than global msg than specific msg than progression bar on the screen then refresh it
				 *
				 * @Screen, the videosurface where everything is blitted
				 **//*
				void render(std::auto_ptr<VideoSurface>& Screen)
				{

					assert(Loading_BG.get());

					//get Screen usefull infos and use them to set positions
					int ls_x = ( Screen->getWidth() - Loading_BG->getWidth() ) / 2;
					int ls_y = ( Screen->getHeight() - Loading_BG->getHeight() ) / 2;
					int sbpp = Screen->getVideoInfo()->getPixelFormat()->getBitsPerPixel();

					//Blit BG
					Screen->blit(*Loading_BG, Point( ls_x, ls_y ) );

				#ifdef HAVE_SDLTTF
					//Blit Global Msg
					if (Loading_Global_Msg != "")
						Screen->blit(*(Loading_Global_Msg_Font.render(Loading_Global_Msg,RGBColor(0,0,0), Font::Blended )), Point( ls_x + Progress_Bar_Infos.getx(), std::max(ls_y, ls_y + Progress_Bar_Infos.gety() - 40) ) );

					//Blit Specific Msg
					if (Loading_Specific_Msg != "")
						Screen->blit(*(Loading_Specific_Msg_Font.render(Loading_Specific_Msg,RGBColor(0,0,0), Font::Blended )), Point(ls_x + Progress_Bar_Infos.getx(), ls_y + Progress_Bar_Infos.gety() + Progress_Bar_Infos.geth()*2 ) );
				#endif //HAVE_SDLTTF

					//progression bar
					RGBSurface progressbar( Progress_Percent*Progress_Bar_Infos.getw()/100, Progress_Bar_Infos.geth(), sbpp );
					progressbar.fill(RGBAColor(225,0,0,200));
					Screen->blit(progressbar, Point( ls_x + Progress_Bar_Infos.getx(), ls_y + Progress_Bar_Infos.gety() ) );

					//Force screen to refresh and display the loading screen
					Screen->refresh();
				}
			};
			LoadingScreen* myLoadingScreen;
*/
		public:
			/**
			 * Show a loading Screen: a static bg with a global msg and a specific msg.
			 * Also set ShowingLoadingScreen to true, forcing the eventual mainloop to run at 1 fps and 1eps.
			 *
			 * @Loading_BG_Filename, a string to the filename image to display in background
			 * @Loading_Global_Msg, a string to the global loading screen msg that wont change until loading screen hide
			 * @Loading_Global_Msg_Font, a Font ref to pointer used to display Loading_Global_Msg
			 * @Loading_Specific_Msg, a string to the scpecific loading screen msg that will be blit at the initial shown of the loading screen and then be updated
			 * @Loading_Specific_Msg_Font, a Font ref to pointer used to display Loading_Specific_Msg_Font
			 * @Progress_Bar_Infos, a Rect containing first the progress bar origin coordinates (also used for specific msg position) and then the width/height of the bar. Default an empty Rect.
			 **/
/*			void ShowLoadingScreen(
				const std::string& Loading_BG_Filename,
				const std::string& Loading_Global_Msg,
				#ifdef HAVE_SDLTTF
					const Font& Loading_Global_Msg_Font,
				#endif
				const std::string& Loading_Specific_Msg,
				#ifdef HAVE_SDLTTF
					const Font& Loading_Specific_Msg_Font,
				#endif
				const Rect& Progress_Bar_Infos = Rect()
				);
*/
			/**
			 * Show a loading Screen: a static bg with a global msg and a specific msg.
			 *
			 * @Progress_Percent, a value between 0 and 100 (forced) that represent the progression of the loading
			 * @Loading_Specific_Msg, a string to the scpecific msg that must reflect update
			 **/
/*			void UpdateLoadingScreen( const unsigned short& Progress_Percent, const std::string& Loading_Specific_Msg );
*/
			/**
			 * Simply set ShowingLoadingScreen to false and delete myLoadingScreen
			 **/
/*			void HideLoadingScreen();
*/
			//Handles the event, and Call engine->prerender, engine ->render() and engine->postrender()
            bool mainLoop(unsigned int framerate = 60,unsigned int eventrate = 60);

        };
    }
}
#endif
