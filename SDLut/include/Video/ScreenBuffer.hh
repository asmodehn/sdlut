#ifndef SDLut_ScreenBuffer_hh
#define SDLut_ScreenBuffer_hh

/**
 * \class ScreenBuffer
 * \ingroup Video
 * 
 * \brief This class handles the displayed zone stored on memory...
 *
 * This class hides the details of implementation of 2D display and
 * the details of refreshing only the parts of the screen needed...
 *
 * \author Alex
 *
 * \date 2009\06\24
 * 
 * contact : asmodehn@gna.org
 */

#include "Video/SDLVideoInfo.hh"
#include "Video/SDLVideoSurface.hh"
#include "Video/SDLVideoGLSurface.hh"
#ifdef HAVE_OPENGL
 #include "Video/SDLGLManager.hh"
#endif //HAVE_OPENGL
#include "Video/SDLEngine.hh"


//Default Setup
#define DEFAULT_DISPLAY_WIDTH 640 // TODO not needed , can default to 4/3 mode or advised mode or desktop if nothing given...
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode

namespace RAGE
{
	namespace SDL
	{

		class ScreenBuffer
		{
			int m_width;
			int m_height;
			int m_bpp;
			
		 protected:
            VideoInfo m_videoinfo;
			std::auto_ptr<VideoSurface> m_screen;
#ifdef HAVE_OPENGL
            GLManager m_glmanager;
#endif
			RGBColor m_background;
            std::auto_ptr<Engine> m_engine;

		 public:
			ScreenBuffer(int width = 0, int height = 0, int bpp = 0) throw (std::logic_error);
			ScreenBuffer( const ScreenBuffer & );//behavior ? not sure yet...
			~ScreenBuffer();

			//preset or "dynamically change" properties of the display...
            bool setResizable(bool val);
            bool setFullscreen(bool val);
#ifdef HAVE_OPENGL

            inline GLManager & getGLManager()
            {
                return m_glmanager;
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
				m_background = color;
			}
			RGBColor getBGColor() { return m_background;}

			//fill the VideoSurface with the BGColor
			void applyBGColor() const;

			void resetEngine(std::auto_ptr<Engine> pt_engine);
					
            VideoSurface & getDisplay( void )
            {
		    //if (!pvm_screen.get()) resetDisplay();
                return *m_screen;
            }

			inline VideoInfo & getVideoInfo( void )
            {
                return m_videoinfo;
            }
				
			bool resize(int width, int height);
			bool show(); // return true if the screenbuffer is displayed. creates the Videosurface if needed.
			bool hide();
			//LATER
			// addImage(x, y, z, "key", Image); //add an image to the list of displayed image
			// getImage("key"); //returns a sprite = position + image... -> client can translate or mirror it.. somehow...
			//LATER
			bool renderpass(unsigned long framerate, unsigned long& lastframe);
			bool refresh();
				
		};

	} // SDL

} // RAGE

#endif // SDLut_ScreenBuffer_hh
