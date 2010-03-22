/*
Made by XorfacX
*/

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/sdlut/sdlutfont.hpp"

#include "guichan/exception.hpp"
#include "guichan/image.hpp"

#include <guichan/sdlut/sdlutgraphics.hpp>


namespace gcn
{
SDLutFont::SDLutFont (const std::string& filename, int size, font::Font::RenderMode renderMode /*= font::Font::Blended*/, font::Font::Style style /*= font::Font::Normal*/)
{
    try
    {
        mRowSpacing = 0;
        mGlyphSpacing = 0;
        mRenderMode = renderMode;
        mStyle = style;
        mFilename = filename;
        mFont = NULL;

        mFont = new font::Font(filename.c_str(), size);
        mFont->setStyle(mStyle);

    }
    catch (std::exception &exc)
    {
        Clean_SDLutFont();
        throw GCN_EXCEPTION("Error In SDLutFont Constructor: " + (std::string)exc.what());
    }
    catch (...)
    {
        Clean_SDLutFont();
        throw GCN_EXCEPTION("Unhandled Error In SDLutFont Constructor");
    }
}

SDLutFont::~SDLutFont()
{
    Clean_SDLutFont();
}

void SDLutFont::Clean_SDLutFont()
{
    delete mFont, mFont = NULL;
}

int SDLutFont::getWidth(const std::string& text) const
{
    return mFont->getSize(text).getw();
    /*int w, h;
    TTF_SizeText(mFont, text.c_str(), &w, &h);

    return w;*/
}

int SDLutFont::getHeight() const
{
    return mFont->getHeight() + mRowSpacing;
    //return TTF_FontHeight(mFont) + mRowSpacing;
}

void SDLutFont::drawString(Graphics* graphics, const std::string& text, const int x, const int y)
{
    //this test is used to circumvenient font bug when trying to display an empty string
    if (text == "")
    {
        return;
    }


    SDLutGraphics *sdlutGraphics = dynamic_cast<SDLutGraphics *>(graphics);

    if (sdlutGraphics == NULL)
    {
        throw GCN_EXCEPTION("SDLTrueTypeFont::drawString. Graphics object not an SDL graphics object!");
        return;
    }

    // This is needed for drawing the Glyph in the middle if we have spacing
    int yoffset = getRowSpacing() / 2;

    Color col = sdlutGraphics->getColor();

    video::Color RGBACol (  static_cast<unsigned char>( col.r ),
                            static_cast<unsigned char>( col.g ),
                            static_cast<unsigned char>( col.b ),
                            static_cast<unsigned char>( col.a )
                         );


    font::Text textsurf(text, *mFont, RGBACol);
    textsurf.changeRendermode(mRenderMode);

    //Rect dst(x, y + yoffset, 0, 0);
    //Rect src(0, 0, textsurf.getWidth(), textsurf.getHeight());
    video::Rect dst(x, y + yoffset, textsurf.getWidth(), textsurf.getHeight());
    video::Rect src(0, 0, textsurf.getWidth(), textsurf.getHeight());

    /*
    dst.resetx( x );
    dst.resety( y + yoffset );
    src.resetw( textSurface->getWidth() );
    src.reseth( textSurface->getHeight() );
    src.resetx( 0 );
    src.resety( 0 );
    */

    sdlutGraphics->drawSDLutSurface(textsurf, src, dst);

}

void SDLutFont::setRowSpacing(int spacing)
{
    mRowSpacing = spacing;
}

int SDLutFont::getRowSpacing()
{
    return mRowSpacing;
}

void SDLutFont::setGlyphSpacing(int spacing)
{
    mGlyphSpacing = spacing;
}

int SDLutFont::getGlyphSpacing()
{
    return mGlyphSpacing;
}

font::Font::Style SDLutFont::getStyle()
{
    return mStyle;
}
void SDLutFont::setStyle(font::Font::Style s)
{
    mFont->setStyle(s);
}
}

