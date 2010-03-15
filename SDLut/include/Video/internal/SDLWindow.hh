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




#include "Video/Color.hh"
#include "Video/internal/SDLRGBSurface.hh"

#ifdef WK_SDLTTF_FOUND
#include "Font/SDLFont.hh"
#endif //WK_SDLTTF_FOUND

#include <memory>

#define DEFAULT_WINDOW_TITLE "SDLut Window"
#define DEFAULT_ICON_TITLE "SDLut"

namespace RAGE
{
namespace SDL
{


class Window
{

    friend class Display;//to be able to create the unique window

protected:

    std::string ptm_title, ptm_iconname;

    std::auto_ptr<RGBSurface> ptm_icon;

    Window(std::string title); // TODO :: add the icon here

public:

    ~Window();


    //return true on success, false otherwise
    bool iconify(void);
    void grabInput(void);
    void releaseInput(void);
    bool isInputGrabbed(void);

protected:

    void setCaption(std::string title = DEFAULT_WINDOW_TITLE, std::string iconname = DEFAULT_ICON_TITLE );
    //oldversion
    void getCaption(std::string & title, std::string & iconname) const;

public :
    inline void setTitle(std::string title)
    {
        setCaption(title,title);
    }

    inline void setTitle(std::string title, std::string icon_title)
    {
        setCaption(title,icon_title);
    }
    std::string getTitle() const;

    void setIcon(const RGBSurface & icon);
    std::string getIconName() const;


};
}
}
#endif
