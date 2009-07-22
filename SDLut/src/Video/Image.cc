#include "Video/Image.hh"
#include "SDLConfig.hh"

#include "SDLApp.hh"
//here just to be able to access the Manager without explicitly showing it in the interface
//as the interface might be used directly by the client...
//TODO : Have a Singleton containing the settings of the Application, available everywhere through SDLConfig.hh

namespace RAGE
{
    namespace SDL {


	///Conversion Constructor
    	Image::Image(RGBSurface * s) throw (std::logic_error)
    	: m_img(s)
    	{
    	    if ( m_img == NULL ) throw std::logic_error("Error in image Constructor!!!");
    	}

	///Conversion Constructor with explicit ownership transfert
    	Image::Image(std::auto_ptr<RGBSurface> s) throw (std::logic_error)
    	: m_img(NULL)
    	{
    	    m_img=s.release();
    	    if ( m_img == NULL ) throw std::logic_error("Error in image Constructor!!!");
    	}

  	//Constructor
	//BPP should NEVER be == 0 !!!!
	Image::Image( int width, int height, int bpp,
				bool alpha,
				bool colorkey,
				bool hardware
				) throw (std::logic_error)

    {
        if ( App::getInstance().getManager().isOpenGLEnabled() )
        {
            m_img = new GLSurface(width, height, bpp, alpha, colorkey, hardware);
        }
        else
        {
            m_img = new RGBSurface(width, height, bpp, alpha, colorkey, hardware);
        }
    }


	Image::Image( void * pixeldata, int depth, int pitch, int width, int height
				) throw (std::logic_error)
    {

        if ( App::getInstance().getManager().isOpenGLEnabled() )
        {
            m_img = new GLSurface(pixeldata, depth, pitch, width, height);
        }
        else
        {
            m_img = new RGBSurface(pixeldata, depth, pitch, width, height);
        }
    }


    Image::~Image()
    {
        delete m_img, m_img=NULL;
    }

    bool Image::fill (const RGBAColor& color, const Rect& dest_rect)
    {
        m_img->fill(color,dest_rect);
    }

    bool Image::blit (const Image& src, Rect& dest_rect, const Rect& src_rect)
    {
        m_img->blit( *(src.m_img), dest_rect, src_rect );
    }


    } //SDL

} // RAGE


