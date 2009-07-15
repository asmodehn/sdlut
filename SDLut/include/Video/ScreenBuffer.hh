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
#include "Functor.hh" //for callbacks storage...

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

            SDLEngine m_engine; // for now only one engine... later multiple engine will be possible

		 public:
			ScreenBuffer(int width = 0, int height = 0, int bpp = 0) throw (std::logic_error);
			ScreenBuffer( const ScreenBuffer & );
			~ScreenBuffer();

//warning no protection offered here in case of wrong / unsupported size ( TODO )
            void setWidth(int width) { m_width = width;}
            void setHeight(int height) { m_height = height;}
            void setBPP(int bpp) { m_bpp = bpp; }

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

private:
            template <class TClass>
            class InitCB : public TSpecificFunctor2<TClass, bool, int, int>
			{
				public:
					InitCB(TClass* ptobj, bool (TClass::*ptfunc) (int width, int height))
					: TSpecificFunctor2<TClass,bool,int,int>(ptobj,ptfunc)
					{
					}

			};

            //normal pointer because we need the polymorphism here
            TFunctor2<bool,int,int>* m_initcb;

			template <class UClass>
            class ResizeCB : public TSpecificFunctor2<UClass, bool, int, int>
			{
				public:
					ResizeCB(UClass* ptobj, bool (UClass::*ptfunc) (int width, int height))
					: TSpecificFunctor2<UClass,bool,int,int>(ptobj,ptfunc)
					{
					}

			};

            //normal pointer because we need the polymorphism here
            TFunctor2<bool,int,int> * m_resizecb;


			template <class VClass>
            class NewFrameCB : public TSpecificFunctor2<VClass, bool, unsigned long, unsigned long >
			{
				public:
					NewFrameCB(VClass* ptobj, bool (VClass::*ptfunc) (unsigned long, unsigned long))
					: TSpecificFunctor2<VClass,bool,unsigned long,unsigned long>(ptobj,ptfunc)
					{
					}

			};

            //normal pointer because we need the polymorphism here
			TFunctor2<bool,unsigned long, unsigned long> * m_newframecb;


			template <class WClass>
            class RenderCB : public TSpecificConstFunctor1<WClass, bool, VideoSurface& >
			{
				public:
					RenderCB(WClass* ptobj, bool (WClass::*ptfunc) (VideoSurface& screen) const ) // render function should be const
					: TSpecificConstFunctor1<WClass,bool,VideoSurface& >(ptobj,ptfunc)
					{
					}

			};

            //normal pointer because we need the polymorphism here
			TFunctor1<bool,VideoSurface&> * m_rendercb;

public:

			template <class TClass>
			void resetInitCallback(TClass* instance, bool (TClass::*func) ( int width, int height) )
			{
			    if ( m_initcb ) delete m_initcb, m_initcb = NULL;
			    m_initcb = new InitCB<TClass>(instance,func);
			}

            //this callback is run whenever a resize is needed.
            //parameter is the desired new size.
			template <class UClass>
			void resetResizeCallback(UClass* instance, bool (UClass::*func) ( int width, int height) )
			{
			    if ( m_resizecb ) delete m_resizecb, m_resizecb= NULL;
			    m_resizecb = new ResizeCB<UClass>(instance,func);
            }

			//this callback is run just before the render
			//deltaticks is the amount of ticks between the end of the last render and now.
			//framerate is in fps.
			template <class VClass>
			void resetNewFrameCallback(VClass* instance, bool (VClass::*func) ( unsigned long framerate, unsigned long deltaticks) )
			{
			    if ( m_newframecb ) delete m_newframecb, m_newframecb = NULL;
			    m_newframecb = new NewFrameCB<VClass>(instance,func);
            }

            //this callback is run just for rendering purpose. therefore it s already too late to modify anything -> const
            //if there is anything you need to modify please use the newframe callback
			template <class WClass>
			void resetRenderCallback(WClass* instance, bool (WClass::*func) (RAGE::SDL::VideoSurface& ) const )
			{
			    if ( m_rendercb ) delete m_rendercb, m_rendercb = NULL;
			    m_rendercb = new RenderCB<WClass>(instance,func);
            }



		};

	} // SDL

} // RAGE

#endif // SDLut_ScreenBuffer_hh
