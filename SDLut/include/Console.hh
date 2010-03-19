#ifndef SDLUT_CONSOLE_HH
#define SDLUT_CONSOLE_HH

#define CONS_ROW 24
#define CONS_COL 80

#include "Video/Image.hh"
#include "Video/Color.hh"
#include "Font/SDLFont.hh"
#include "Video/ScreenBuffer.hh"

#include <vector>

/**
 * \class Console
 *
 * \ingroup SDLut
 *
 * \brief Implementation fo a Console over SDL
 *
 * \author Alex
 *
 * \date 2010/03/19
 *
 * Contact: asmodehn@gna.org
 *
 */




namespace SDLut
{




//Console is an Image with a default size, and default colors
class Console : public video::Image
{
	//if member embedded (object not reference), error when destructing Font...
	//to debug -> copy / deletion problem
	const font::Font m_font;

    video::Color m_color;
    video::Color m_bgcolor;

    std::vector<std::string> rowbuffer;
    std::string curline;

    //buffer to store previous lines
	std::vector<Image> rowimage;

public :
	Console(const font::Font & fnt = font::Font(),video::Color c = video::Color(255,255,255),video::Color bgc = video::Color(0,0,0,128));

	//WARNING : BUG here if trying to set to fullscreen using F6, then error, then trying to resize -> crash
	bool resize(int width, int height);

	void addchar(char newchar);
    void addline(std::string newtext);

	bool render(video::ScreenBuffer & screen) const;
};


}

#endif // SDLUT_CONSOLE_HH

