/*
Made by XorfacX
*/

#ifndef GCN_SDLutFONT_HPP
#define GCN_SDLutFONT_HPP

#include <map>
#include <string>

#include "sdlutdepends.hpp"

#include "guichan/font.hpp"
#include "guichan/graphics.hpp"
#include "guichan/image.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
/**
 * SDL True Type Font implementation of Font. It uses the SDL_ttf library
 * to display True Type Fonts with SDL.
 *
 * NOTE: You must initialize the SDL_ttf library before using this
 *       class. Also, remember to call the SDL_ttf libraries quit
 *       function.
 *
 * @author Walluce Pinkham
 * @author Olof Naessén
 */
class GCN_EXTENSION_DECLSPEC SDLutFont: public Font
{
private:
    /**
     * Clean the class
     */
    void Clean_SDLutFont();

public:

    /**
     * Constructor.
     *
     * @param filename: the filename of the Font.
     * @param size: the size the font should be in.
     * @param AntiAliasing: set AntiAliasing ON/OFF
     */
    SDLutFont (const std::string& filename, int size, SDLut::Font::RenderMode renderMode = SDLut::Font::Blended, SDLut::Font::Style style = SDLut::Font::Normal);

    /**
    * Destructor.
    */
    virtual ~SDLutFont();

    /**
    * Sets the spacing between rows in pixels. Default is 0 pixels.
    * The spacing can be negative.
    *
    * @param spacing the spacing in pixels.
    */
    virtual void setRowSpacing (int spacing);

    /**
    * Gets the spacing between rows in pixels.
    *
    * @return the spacing.
    */
    virtual int getRowSpacing();

    /**
    * Sets the spacing between letters in pixels. Default is 0 pixels.
    * The spacing can be negative.
    *
    * @param spacing the spacing in pixels.
    */
    virtual void setGlyphSpacing(int spacing);

    /**
    * Gets the spacing between letters in pixels.
    *
    * @return the spacing.
    */
    virtual int getGlyphSpacing();

    // Inherited from Font

    virtual int getWidth(const std::string& text) const;

    virtual int getHeight() const;

    virtual void drawString(Graphics* graphics, const std::string& text, int x, int y);

    /**
    * Gets the Font Style.
    *
    * @return the Style.
    */
    SDLut::Font::Style getStyle();

    /**
    * Sets the Font Style.
    *
    * @param s, the Font Style.
    */
    void setStyle(SDLut::Font::Style s);

protected:
    SDLut::Font *mFont;
    SDLut::Font::RenderMode mRenderMode;
    SDLut::Font::Style mStyle;

    int mHeight;
    int mGlyphSpacing;
    int mRowSpacing;

    std::string mFilename;
};
}

#endif // end GCN_SDLutFONT_HPP

