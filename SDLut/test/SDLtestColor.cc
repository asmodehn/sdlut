#include "SDL.hh"
#include "Logger.hh"

using namespace RAGE;
using namespace RAGE::SDL;

#ifdef WIN32
	#include <windows.h>
#endif
#include <GL/gl.h>


Logger Log("Test Color");

	RGBSurface* red;
	RGBSurface* green;
	RGBSurface* blue;
	RGBSurface* alpha;

class MyEngine : public DefaultEngine
{
	
public:

	MyEngine() : DefaultEngine()
	{ 
	}

    virtual ~MyEngine(){}

	bool init(int width, int height)
	{
		red = new RGBSurface(width/4,height,32);
		red->fill(RGBColor(255,0,0));
		green = new RGBSurface(width/4,height,32);
		green->fill(RGBColor(0,255,0));
		blue = new RGBSurface(width/4,height,32);
		blue->fill(RGBColor(0,0,255));
		alpha = new RGBSurface(width/4,height,32);
		alpha->fill(RGBAColor(255,255,255,0));

		Log << nl << "Red Pixel : " << std::hex << red->getpixel(0,0);
		Log << nl << "Green Pixel : " << std::hex << green->getpixel(0,0);
		Log << nl << "Blue Pixel : " << std::hex << blue->getpixel(0,0);
		Log << nl << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0); //BUG HERE: alpha value is always gotten at FF

		return DefaultEngine::init(width,height);
	}

	bool resize(int width, int height)
	{
		 //BUG HERE: resize dimensions seems to be rounded to much on the right side ? (purple displayed on a tiny band)

		delete red; delete green; delete blue; delete alpha;
		red = new RGBSurface(width/4,height,32);
		red->fill(RGBColor(255,0,0));
		green = new RGBSurface(width/4,height,32);
		green->fill(RGBColor(0,255,0));
		blue = new RGBSurface(width/4,height,32);
		blue->fill(RGBColor(0,0,255));
		alpha = new RGBSurface(width/4,height,32);
		alpha->fill(RGBAColor(255,255,255,0)); 
		return DefaultEngine::resize(width,height);
		
	}

	void prerender(unsigned long deltaticks)
	{
		return DefaultEngine::prerender(deltaticks);
	}

	void render(VideoSurface & screen) const
    {
		screen.blit(*red,Point(0,0));
		screen.blit(*green,Point(0 + red->getWidth(),0));
		screen.blit(*blue,Point(0 + red->getWidth() + green->getWidth(), 0));
		screen.blit(*alpha,Point(0 + red->getWidth() + green->getWidth() + blue->getWidth(), 0));  //BUG HERE: no merge w the BGColor even if there is a alpha on this color
		return DefaultEngine::render(screen);
    }

	void postrender()
	{
		return DefaultEngine::postrender();
	}
};

//class MyGLEngine : public DefaultGLEngine
//{
//
//	unsigned int redtexture;
//	unsigned int greentexture;
//	unsigned int bluetexture;
//
//public:
//
//	MyGLEngine() : DefaultGLEngine(),redtexture(0),greentexture(0),bluetexture(0)
//	{}
//
//    virtual ~MyGLEngine()
//	{
//		if (redtexture!=0) glDeleteTextures(1, &redtexture);
//		if (greentexture!=0) glDeleteTextures(1, &greentexture);
//		if (bluetexture!=0) glDeleteTextures(1, &bluetexture);
//	}
//
//	bool init(int width, int height)
//	{
//		red = new RGBSurface(width/4,height,32);
//		red->fill(RGBColor(255,0,0));
//		green = new RGBSurface(width/4,height,32);
//		green->fill(RGBColor(0,255,0));
//		blue = new RGBSurface(width/4,height,32);
//		blue->fill(RGBColor(0,0,255));
//
//		Log << nl << "Red Pixel : " << std::hex << red->getpixel(0,0);
//		Log << nl << "Green Pixel : " << std::hex <<green->getpixel(0,0);
//		Log << nl << "Blue Pixel : " << std::hex <<blue->getpixel(0,0);
//
//			redtexture=red->generateTexture();
//			if (glIsTexture(redtexture) !=GL_TRUE)
//			{
//				Log << nl << "Unable to generate red texture" ;
//			}
//			greentexture=green->generateTexture();
//			if (glIsTexture(greentexture) !=GL_TRUE)
//			{
//				Log << nl << "Unable to generate red texture" ;
//			}
//
//			bluetexture=blue->generateTexture();
//			if (glIsTexture(bluetexture) !=GL_TRUE)
//			{
//				Log << nl << "Unable to generate red texture" ;
//			}
//
//		return DefaultGLEngine::init(width,height);
//	}
//
//	bool resize(int width, int height)
//	{
//		delete red; delete green; delete blue;
//
//		if (redtexture!=0) glDeleteTextures(1, &redtexture);
//		if (greentexture!=0) glDeleteTextures(1, &greentexture);
//		if (bluetexture!=0) glDeleteTextures(1, &bluetexture);
//
//		red = new RGBSurface(width/4,height,32);
//		red->fill(RGBColor(255,0,0));
//		green = new RGBSurface(width/4,height,32);
//		green->fill(RGBColor(0,255,0));
//		blue = new RGBSurface(width/4,height,32);
//		blue->fill(RGBColor(0,0,255));
//
//			std::cout << "Red : ";
//			redtexture=red->generateTexture();
//			if (glIsTexture(redtexture) !=GL_TRUE)
//			{
//				Log << nl << "Unable to generate red texture" ;
//			}
//			std::cout << "Green : ";
//			greentexture=green->generateTexture();
//			if (glIsTexture(greentexture) !=GL_TRUE)
//			{
//				Log << nl << "Unable to generate red texture" ;
//			}
//
//			std::cout << "Blue : ";
//			bluetexture=blue->generateTexture();
//			if (glIsTexture(bluetexture) !=GL_TRUE)
//			{
//				Log << nl << "Unable to generate red texture" ;
//			}
//
//		return DefaultGLEngine::resize(width,height);
//		
//	}
//
//	void prerender(unsigned long deltaticks)
//	{
//		return DefaultGLEngine::prerender(deltaticks);
//	}
//
//	void render(VideoSurface & screen) const
//    {
//
//			//2D Rendering
//
//			glDisable( GL_DEPTH_TEST ) ;
//			glMatrixMode( GL_PROJECTION ) ;
//			glLoadIdentity() ;
//
//			glOrtho( 0, screen.getWidth(), screen.getHeight(), 0, 0, 1 ) ;
//			glMatrixMode(GL_MODELVIEW);
//			glLoadIdentity();
//
//			//Enable texturing
//			glEnable(GL_TEXTURE_2D);	
//
//			//Load the texture
//			glBindTexture(GL_TEXTURE_2D, redtexture);
//
//			glBegin( GL_QUADS ) ;
//				glTexCoord2i( 0,0) ;
//				glVertex2i( 0 , 0 ) ;
//	
//				glTexCoord2i( 0, 1) ;
//				glVertex2i( 0 , screen.getHeight()) ;
//	
//				glTexCoord2i( 1, 1) ;
//				glVertex2i( red->getWidth() , screen.getHeight()) ;
//				
//				glTexCoord2i( 1, 0) ;
//				glVertex2i( red->getWidth(), 0) ;
//			glEnd() ;
//
//			//Load the texture
//			glBindTexture(GL_TEXTURE_2D, greentexture);
//
//			glBegin( GL_QUADS ) ;
//				glTexCoord2i( 0,0) ;
//				glVertex2i( red->getWidth() , 0 ) ;
//	
//				glTexCoord2i( 0, 1) ;
//				glVertex2i( red->getWidth() , screen.getHeight()) ;
//	
//				glTexCoord2i( 1, 1) ;
//				glVertex2i( red->getWidth() + green->getWidth() , screen.getHeight()) ;
//				
//				glTexCoord2i( 1, 0) ;
//				glVertex2i( red->getWidth()+ green->getWidth(), 0) ;
//			glEnd() ;
//
//						//Load the texture
//			glBindTexture(GL_TEXTURE_2D, bluetexture);
//
//			glBegin( GL_QUADS ) ;
//				glTexCoord2i( 0,0) ;
//				glVertex2i( red->getWidth() + green->getWidth() , 0 ) ;
//	
//				glTexCoord2i( 0, 1) ;
//				glVertex2i(  red->getWidth() + green->getWidth(), screen.getHeight()) ;
//	
//				glTexCoord2i( 1, 1) ;
//				glVertex2i(  red->getWidth() + green->getWidth()+ blue->getWidth() , screen.getHeight()) ;
//				
//				glTexCoord2i( 1, 0) ;
//				glVertex2i(  red->getWidth() + green->getWidth()+ blue->getWidth(), 0) ;
//			glEnd() ;
//
//			//Disable texturing
//			glDisable(GL_TEXTURE_2D);
//
//		screen.blit(*red,Point(0,0));
//		screen.blit(*green,Point(0+red->getWidth(),0));
//		screen.blit(*blue,Point(0+red->getWidth() + green->getWidth(), 0));
//		return DefaultGLEngine::render(screen);
//    }
//
//	void postrender()
//	{
//		return DefaultGLEngine::postrender();
//	}
//};

//Main Program
int main(int argc, char** argv)
{
    Logger testlog("Test Log");

	bool ogl = false;
	if (argc > 1 && std::string(argv[1]) == "opengl" ) ogl = true;

    //Starting with usual SDL window
    App::getInstance().initVideo(false,ogl,true,false);
	App::getInstance().setName ("RAGE::SDL test Color : Displayed Color order \"Red - Green - Blue - Purple if alpha is working else White\"");  //BUG HERE: Title never displayed ?!
	
    //Getting video informations
    testlog << nl << App::getInstance().getWindow().getVideoInfo() << std::endl; //BUG HERE: displayed infos are false like available memory @ 0 for example

	//Purple background color (useful to test alpha / color key)
	App::getInstance().getWindow().setBGColor(RGBColor (255,0,255));

	Engine* engine;
	//if ( ogl )
	//{
	//	engine = new MyGLEngine();
	//}
	//else
	//{
		engine = new MyEngine();
	//}
	App::getInstance().getWindow().setEngine(engine);

    if(App::getInstance().getWindow().resetDisplay(800,600))
    {
       App::getInstance().getWindow().mainLoop();
    }

	delete engine;
	delete red; delete green; delete blue; delete alpha;
    return 0;
}


