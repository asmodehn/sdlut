#if !defined(MX_SDL_H_)
#define MX_SDL_H_

#include "SDLwrap.hh"

#if !defined(MxUnused)
#define MxUnused(a)
#endif

#include <iostream>
#include <string>

namespace MxLib
{
//
//    //singleton to do again properly
//    class MxInit
//    {
//    private :
//
//        static MxInit * _instance;
//
//    protected :
//
//        MxInit(int width = 640, int height = 480) throw (std::logic_error);
//
//    public :
//
//        static MxInit * init(int width = 640, int height = 480);
//
//        static SDL::DisplaySurface * getDisplay(void);
//
//
//    };

//    class MxBitmap
//    {
//    private :
//        SDL::Surface * sm_factory;
//        unsigned int m_surfindex;
//
//    public :
//        MxBitmap(std::string filename);
//        MxBitmap(std::string filename, const SDL::Color & colorKey);
//
//        void optimize();
//
//        SDL::RGBSurface * getRawSurface();
//
//        bool render (int pixX = 0, int pixY = 0);
//
//    };

}

#endif
