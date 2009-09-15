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
SDLutFont::SDLutFont (const std::string& filename, int size, RAGE::SDL::Font::RenderMode renderMode, RAGE::SDL::Font::Style style)
{
    try
    {
        mRowSpacing = 0;
        mGlyphSpacing = 0;
        mRenderMode = renderMode;
        mStyle = style;
        mFilename = filename;
        mFont = NULL;

        mFont = new RAGE::SDL::Font(filename.c_str(), size);
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

    SDLut::RGBColor RGBCol;
    RGBCol.setB(col.b);
    RGBCol.setR(col.r);
    RGBCol.setG(col.g);

    std::auto_ptr<SDLut::RGBSurface> textSurface = mFont->render(text.c_str(), RGBCol, mRenderMode);

    SDLut::Rect dst, src;
    dst.setx( x );
    dst.sety( y + yoffset );
    src.setw( textSurface->getWidth() );
    src.seth( textSurface->getHeight() );
    src.setx( 0 );
    src.sety( 0 );

    sdlutGraphics->drawSDLutSurface(*textSurface, src, dst);

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

RAGE::SDL::Font::Style SDLutFont::getStyle()
{
    return mStyle;
}
void SDLutFont::setStyle(RAGE::SDL::Font::Style s)
{
    mFont->setStyle(s);
}
}

