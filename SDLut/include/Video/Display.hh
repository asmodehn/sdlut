#ifndef SDLut_Display_hh
#define SDLut_Display_hh

/**
 * \class Display
 * \ingroup Video
 *
 * \brief This class handles the display part of the application
 *
 * This class hides the details of implementation of 2D display and contains a window and a Screenbuffer.
 *
 * \author Alex
 *
 * \date 2009\07\24
 *
 * contact : asmodehn@gna.org
 */

#include "SDLManager.hh"
#include "Video/ScreenBuffer.hh"
#include "Video/SDLWindow.hh"
#include "System/SDLEventManager.hh"

#ifdef WK_OPENGL_FOUND
#include "Video/SDLGLManager.hh"
#endif //WK_OPENGL_FOUND
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

//further reference to break dependency cycles
//class EventManager;
//Not needed anymore ??

class Display
{
    friend class App; //to access the constructor

    //and be able to exit mainloop

    bool m_exitMainLoop;

protected:
    Manager* pvm_manager; // here because the manager contains also the SDL specific settings that we need...

    //here because Event are initialised along with video...
    EventManager pvm_eventmanager;

    Window pvm_window; //delegating charge of the window frame and decorations only
    ScreenBuffer pvm_screen;

    Scene pvm_scene;

public:
    //sets Display size and BPP
    bool setDisplay( unsigned int width = 0, unsigned int height = 0, unsigned int bpp = 0 );
    bool show();
    bool hide();

    //just resize the screen (without changing flags, or bpp)
    //returns NULL if no screen available
    // calls Engine->resize();
    bool resizeDisplay (int width, int height);


    //VideoSurface & getDisplay( void )
    //{
    ////if (!pvm_screen.get()) resetDisplay();
    //    return pvm_screen.getDisplay();
    //}

    ScreenBuffer & getScreenBuffer( )
    {
        return pvm_screen;
    }

    Scene & getScene()
    {
        return pvm_scene;
    }

    inline EventManager & getEventManager()
    {
        return pvm_eventmanager;
    }

    Display(std::string title, Manager * m);
    Display( const Display & d);
    ~Display();

    //preset or "dynamically change" properies of the display...
    bool setResizable(bool val);
    bool setFullscreen(bool val);
#ifdef WK_OPENGL_FOUND

    inline GLManager & getGLManager() //TEMPORARY... should matter only to screenbuffer
    {
        return pvm_screen.getGLManager();
    }
    bool setOpenGL(bool val);
#endif // WK_OPENGL_FOUND
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

private:
    ////// WARNING : class Window has been changed to class Display and ScreenBuffer is new//////
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
    	#ifdef WK_SDLTTF_FOUND
    		Font Loading_Global_Msg_Font, Loading_Specific_Msg_Font; //ref
    	#endif // WK_SDLTTF_FOUND
    	std::string Loading_Global_Msg, Loading_Specific_Msg;
    	short Progress_Percent;
    	Rect Progress_Bar_Infos;

    	LoadingScreen(
    		std::auto_ptr<RGBSurface> _Loading_BG,
    		const std::string& _Loading_Global_Msg,
    		#ifdef WK_SDLTTF_FOUND
    			const Font& _Loading_Global_Msg_Font,
    		#endif // WK_SDLTTF_FOUND
    		const std::string& _Loading_Specific_Msg,
    		#ifdef WK_SDLTTF_FOUND
    			const Font& _Loading_Specific_Msg_Font,
    		#endif // WK_SDLTTF_FOUND
    		const Rect& Progress_Bar_Infos
    		) :
    			Loading_BG(_Loading_BG),
    			Loading_Global_Msg(_Loading_Global_Msg),
    			#ifdef WK_SDLTTF_FOUND
    				Loading_Global_Msg_Font(_Loading_Global_Msg_Font),
    			#endif // WK_SDLTTF_FOUND
    			Loading_Specific_Msg(_Loading_Specific_Msg),
    			#ifdef WK_SDLTTF_FOUND
    				Loading_Specific_Msg_Font(_Loading_Specific_Msg_Font),
    			#endif // WK_SDLTTF_FOUND
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

#ifdef WK_SDLTTF_FOUND
//Blit Global Msg
if (Loading_Global_Msg != "")
Screen->blit(*(Loading_Global_Msg_Font.render(Loading_Global_Msg,RGBColor(0,0,0), Font::Blended )), Point( ls_x + Progress_Bar_Infos.getx(), std::max(ls_y, ls_y + Progress_Bar_Infos.gety() - 40) ) );

//Blit Specific Msg
if (Loading_Specific_Msg != "")
Screen->blit(*(Loading_Specific_Msg_Font.render(Loading_Specific_Msg,RGBColor(0,0,0), Font::Blended )), Point(ls_x + Progress_Bar_Infos.getx(), ls_y + Progress_Bar_Infos.gety() + Progress_Bar_Infos.geth()*2 ) );
#endif //WK_SDLTTF_FOUND

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
    				#ifdef WK_SDLTTF_FOUND
    					const Font& Loading_Global_Msg_Font,
    				#endif // WK_SDLTTF_FOUND
    				const std::string& Loading_Specific_Msg,
    				#ifdef WK_SDLTTF_FOUND
    					const Font& Loading_Specific_Msg_Font,
    				#endif // WK_SDLTTF_FOUND
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
    class RenderCB : public TSpecificConstFunctor1<WClass, bool, ScreenBuffer& >
    {
    public:
        RenderCB(WClass* ptobj, bool (WClass::*ptfunc) (ScreenBuffer& screen) const ) // render function should be const
                : TSpecificConstFunctor1<WClass,bool,ScreenBuffer& >(ptobj,ptfunc)
        {
        }

    };

    //normal pointer because we need the polymorphism here
    TFunctor1<bool,ScreenBuffer&> * m_rendercb;

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
    void resetRenderCallback(WClass* instance, bool (WClass::*func) (RAGE::SDL::ScreenBuffer& ) const )
    {
        if ( m_rendercb ) delete m_rendercb, m_rendercb = NULL;
        m_rendercb = new RenderCB<WClass>(instance,func);
    }



};


}// SDL

}// RAGE

#endif
