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
void Window::getCaption(std::string & title, std::string & iconname) const
{
    char t[256]= {}; //size ??
    char i[256]= {}; //size ??
    SDL_WM_GetCaption((char**)&t,(char**)&i); // to test on gcc.. be careful about long strings...
    title=std::string(t);
    iconname=std::string(i);
}

std::string Window::getTitle() const
{
    char t[256]= {}; //size ??
    SDL_WM_GetCaption((char**)&t,NULL); // to test on gcc.. be careful about long strings...
    return std::string(t);

}
std::string Window::getIconName() const
{
    char i[256]= {}; //size ??
    SDL_WM_GetCaption(NULL,(char**)&i); // to test on gcc.. be careful about long strings...
    return std::string(i);
}


Window::Window(std::string title)
        :	_title(title),
        _icon(0)
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



}
}
