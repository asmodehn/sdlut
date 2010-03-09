#ifndef SDLUT_CONSOLE_HH
#define SDLUT_CONSOLE_HH

#define CONS_ROW 24
#define CONS_COL 80

#include "Video/Image.hh"
#include "Video/SDLColor.hh"
#include "Font/SDLFont.hh"
#include "Video/ScreenBuffer.hh"

#include <vector>

namespace RAGE
{
    namespace SDL
    {

//Console is an Image with a default size, and default colors
class Console : public Image
{
	//if member embedded (object not reference), error when destructing Font...
	//to debug -> copy / deletion problem
	const Font m_font;

    Color m_color;
    Color m_bgcolor;

    std::vector<std::string> rowbuffer;
    std::string curline;

    //buffer to store previous lines
	std::vector<Image> rowimage;

public :
	Console(const Font & fnt = Font(),Color c = Color(255,255,255),Color bgc = Color(0,0,0,128));

	//WARNING : BUG here if trying to set to fullscreen using F6, then error, then trying to resize -> crash
	bool resize(int width, int height);

	void addchar(char newchar);
    void addline(std::string newtext);

	bool render(ScreenBuffer & screen) const;
};

    }
}

#endif // SDLUT_CONSOLE_HH

