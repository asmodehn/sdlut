#ifndef SDLut_Display_hh
#define SDLut_Display_hh

#include "SDLManager.hh"
#include "Video/ScreenBuffer.hh"
#include "Video/ScreenInfo.hh"
#include "Video/internal/SDLWindow.hh"
#include "System/SDLEventManager.hh"

#include "Video/internal/SDLEngine.hh"

//to access functors and callback features
#include "Core.hh"

namespace SDLut
{
class App;
namespace video
{

/**
 * \class Display
 * \ingroup SDLut_Video
 *
 * \brief This class handles the display part of the application
 *
 * This class hides the details of implementation of 2D display and contains a window and a Screenbuffer.
 * More specifically it manages different states of the screenbuffer, and handles changes between these states,
 * calling the appropriate callback.
 *
 * \author Alex
 *
 * \date 2009\07\24
 *
 * contact : asmodehn@gna.org
 */


class Display
{
    friend class SDLut::App; //to access the constructor

    //and be able to exit mainloop

    bool m_exitMainLoop;

protected:
    Manager* pvm_manager; // here because the manager contains also the SDL specific settings that we need...

    //here because Event are initialised along with video...
    system::EventManager pvm_eventmanager;

    internal::Window pvm_window; //delegating charge of the window frame and decorations only

    ///on Display instantiation : pvm_screen = 0 and pvm_scinf = best
    ///Then user modifies pvm_scinf
    ///on show() -> screenbuffer created and pvm_scinf = 0
    std::auto_ptr<ScreenBuffer> pvm_screen;



    /// storing best screeninfo upon initialization, then modified by user request to get requested screen parameters through request*() accessors
    std::auto_ptr<ScreenInfo> pvm_scinf;

public:

    ///these modify the screeninfo structure to store requested parameters
    /// WARNING : These are modifying existing screeninfo !

    ///these returns the bpp value suggested by SDL, or 0 if video mode not possible
    unsigned short requestSize(unsigned int width, unsigned int height );
    unsigned short requestBPP(unsigned short bpp);

    /// false is returned if the requested mode cannot be satisfied ( or if screen already created )
    bool requestOpenGL( bool value);
    bool requestResizable (bool value);
    bool requestNoFrame (bool value);
    //fullscreen automatically set noframe to true.
    bool requestFullscreen (bool value);

    unsigned int getRequestedWidth() const;
    unsigned int getRequestedHeight() const;
    unsigned short getRequestedBPP() const;

    //sets Display size and BPP
    bool setDisplay( unsigned int width = 0, unsigned int height = 0, unsigned int bpp = 0 );
    bool show();
    bool hide();

    //just resize the screen (without changing flags, or bpp)
    //returns NULL if no screen available
    // calls Engine->resize();
    bool resizeDisplay (int width, int height);

    internal::Window & getWindow()
    {
        return pvm_window;
    }

    ScreenBuffer & getScreenBuffer( )
    {
        if ( pvm_screen.get() != 0 )
        {
            return *pvm_screen;
        }
        else
        {
            throw std::logic_error("Screen Buffer not initialized. Display::show() must be called before accessing ScreenBuffer.");
        }
    }

    inline system::EventManager & getEventManager()
    {
        return pvm_eventmanager;
    }

    Display(std::string title, Manager * m);
    Display( const Display & d);
    ~Display();

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
    	#ifdef WK_SDLut_FOUND_SDLTTF
    		Font Loading_Global_Msg_Font, Loading_Specific_Msg_Font; //ref
    	#endif // WK_SDLut_FOUND_SDLTTF
    	std::string Loading_Global_Msg, Loading_Specific_Msg;
    	short Progress_Percent;
    	Rect Progress_Bar_Infos;

    	LoadingScreen(
    		std::auto_ptr<RGBSurface> _Loading_BG,
    		const std::string& _Loading_Global_Msg,
    		#ifdef WK_SDLut_FOUND_SDLTTF
    			const Font& _Loading_Global_Msg_Font,
    		#endif // WK_SDLut_FOUND_SDLTTF
    		const std::string& _Loading_Specific_Msg,
    		#ifdef WK_SDLut_FOUND_SDLTTF
    			const Font& _Loading_Specific_Msg_Font,
    		#endif // WK_SDLut_FOUND_SDLTTF
    		const Rect& Progress_Bar_Infos
    		) :
    			Loading_BG(_Loading_BG),
    			Loading_Global_Msg(_Loading_Global_Msg),
    			#ifdef WK_SDLut_FOUND_SDLTTF
    				Loading_Global_Msg_Font(_Loading_Global_Msg_Font),
    			#endif // WK_SDLut_FOUND_SDLTTF
    			Loading_Specific_Msg(_Loading_Specific_Msg),
    			#ifdef WK_SDLut_FOUND_SDLTTF
    				Loading_Specific_Msg_Font(_Loading_Specific_Msg_Font),
    			#endif // WK_SDLut_FOUND_SDLTTF
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

#ifdef WK_SDLut_FOUND_SDLTTF
//Blit Global Msg
if (Loading_Global_Msg != "")
Screen->blit(*(Loading_Global_Msg_Font.render(Loading_Global_Msg,RGBAColor(0,0,0), Font::Blended )), Point( ls_x + Progress_Bar_Infos.getx(), std::max(ls_y, ls_y + Progress_Bar_Infos.gety() - 40) ) );

//Blit Specific Msg
if (Loading_Specific_Msg != "")
Screen->blit(*(Loading_Specific_Msg_Font.render(Loading_Specific_Msg,RGBAColor(0,0,0), Font::Blended )), Point(ls_x + Progress_Bar_Infos.getx(), ls_y + Progress_Bar_Infos.gety() + Progress_Bar_Infos.geth()*2 ) );
#endif //WK_SDLut_FOUND_SDLTTF

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
    				#ifdef WK_SDLut_FOUND_SDLTTF
    					const Font& Loading_Global_Msg_Font,
    				#endif // WK_SDLut_FOUND_SDLTTF
    				const std::string& Loading_Specific_Msg,
    				#ifdef WK_SDLut_FOUND_SDLTTF
    					const Font& Loading_Specific_Msg_Font,
    				#endif // WK_SDLut_FOUND_SDLTTF
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
    //will return the number of errors detcted while using user's callback.
    int mainLoop(unsigned int framerate = 60,unsigned int eventrate = 60);
    bool exitMainLoop();

private:
    //AutoPtr to callbacks. plymorphism _must_ be used...
    std::auto_ptr<Core::Callback2Base<int,int,bool> > m_initcb;
    std::auto_ptr<Core::Callback2Base<int,int,bool> > m_resizecb;
    std::auto_ptr<Core::Callback2Base<unsigned long, unsigned long, bool> > m_newframecb;
    std::auto_ptr<Core::Callback1constBase<ScreenBuffer&,bool> > m_rendercb;

public:
    //this callback is run whenever at initialization (Display::show)
    template <class TaClass>
    void resetInitCallback(TaClass& instance, bool (TaClass::*func) ( int width, int height) )
    {
        //TODO : check if old callback is deleted by reset...
        m_initcb.reset(new Core::Callback2<TaClass,int,int,bool>(instance, func));
    }
    void resetInitCallback()
    {
        m_initcb.reset(0);
    }

    //this callback is run whenever a resize is needed.
    //parameter is the desired new size.
    template <class UaClass>
    void resetResizeCallback(UaClass& instance, bool (UaClass::*func) ( int width, int height) )
    {
        //TODO : check if old callback is deleted by reset...
        m_resizecb.reset(new Core::Callback2<UaClass,int,int,bool>(instance,func));
    }
    void resetResizeCallback()
    {
        m_resizecb.reset(0);
    }

    //this callback is run just before the render
    //deltaticks is the amount of ticks between the end of the last render and now.
    //framerate is in fps.
    template <class VaClass>
    void resetNewFrameCallback(VaClass& instance, bool (VaClass::*func) ( unsigned long framerate, unsigned long deltaticks) )
    {
        //TODO : check if old callback is deleted by reset...
        m_newframecb.reset(new Core::Callback2<VaClass,unsigned long, unsigned long, bool>(instance,func));
    }
    void resetNewFrameCallback()
    {
        m_resizecb.reset(0);
    }

    //this callback is run just for rendering purpose. therefore it s already too late to modify anything -> const
    //if there is anything you need to modify please use the newframe callback
    template <class WaClass>
    void resetRenderCallback(WaClass& instance, bool (WaClass::*func) (video::ScreenBuffer& ) const )
    {
        //TODO : check if old callback is deleted by reset...
        m_rendercb.reset(new Core::Callback1const<WaClass,video::ScreenBuffer&,bool>(instance,func));
    }
    void resetRenderCallback()
    {
        m_rendercb.reset(0);
    }

};


}// SDL

}// SDLut

#endif
