#include "Console.hh"

namespace SDLut{


	Console::Console(const font::Font & fnt,video::Color c ,video::Color bgc)
	 : Image(CONS_COL * fnt.getHeight(), CONS_ROW * fnt.getHeight(),8,true, false, true),
	 m_font(fnt),m_color(c),m_bgcolor(bgc),curline("")
	{
		//init();
		//draw();
	}

	//WARNING : BUG here if trying to set to fullscreen using F6, then error, then trying to resize -> crash
	bool Console::resize(int width, int height)
	{
		bool res = Image::resize(width,height);
		res &= fill(m_bgcolor);
		return res;
	}

	void Console::addchar(char newchar)
	{
		if (newchar != '\0')
		{
		    if (newchar == '\n')
			{
			    addline(curline);
			    curline = "";
			    return;
			}
			else
			{
			    curline += newchar;
			}
		}
	}

    void Console::addline(std::string newtext)
    {
/*
        rowbuffer.push_back(newtext);
	    rowimage.push_back(m_font.render(newtext,m_color,Font::Solid));
*/
    }

	bool Console::render(video::ScreenBuffer & screen) const
    {
/*
        surf->fill(m_bgColor);
		int nb_line_toshow = (int)((getHeight()-linesize)/linesize);

        //displaying rowbuffer
        int first=rowbuffer.size() - nb_line_toshow;

        for ( int i = 0 ; i < nb_line_toshow; i++)
        {
            Rect textsurf_dest(0,i * m_font.getHeight(),rowimage[first]->getWidth(),rowimage[first]->getHeight());
            blit(rowimage[first],textsurf_dest);
        }

        //here there should be only one line left, for current line
        Image curimg = m_font.render(curline,m_color,Font::Solid);
        Rect curline_dest(0,nb_line_toshow * m_font.getHeight(),curimg->getHeight(), curimg->getWidth());
        blit(curimg,curline_dest);

        //final blitting all Image on screen
        Rect dst(0,0,screen.getHeight(),screen.getWidth())
        screen.blit(this,dst)
        return true;

*/
    return false;
    }


} //SDLut
