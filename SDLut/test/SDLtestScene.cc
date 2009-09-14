#include "SDL.hh"

#include <cstdlib>
#include <ctime>

using namespace RAGE;
using namespace RAGE::SDL;

class Sprite
{
    //width and height by default same as image, but could be different ( used for collisions for example )
    int m_width;
    int m_height;

    int m_posx;
    int m_posy;

    const Image* pm_img;

public:


Sprite() : m_width(0), m_height(0), m_posx(0), m_posy(0), pm_img(NULL)
{
}

Sprite( const Sprite& s ) : m_width(s.m_width), m_height(s.m_height), m_posx(s.m_posx), m_posy(s.m_posy), pm_img(s.pm_img)
{
}

~Sprite()
{
}

bool setImage( const Image * img)
{
    //default useful values
    m_width = img->getWidth();
    m_height = img->getHeight();


    pm_img = img;
    return true;
}

bool hasImage()
    {
        return pm_img >0;
    }
    const Image & getImage()
    {
        return *pm_img;
    }

    bool move( int deltax, int deltay )
{
    m_posx += deltax;
    m_posy += deltay;

    return true; //todo
}

bool moveto( int posx, int posy)
{
    m_posx = posx;
    m_posy = posy;

    return true; //todo
}

    int posX()
    {
        return m_posx;
    }
    int posY()
    {
        return m_posy;
    }

};

//NB : For now size of world = size of display in pixel.
class Scene
{
    int m_width;
    int m_height;

    std::vector<Sprite*> m_spritelist;

public:


Scene(int width, int height) : m_width(width), m_height(height) {}
Scene( const Scene & s ) : m_width(s.m_width),m_height(s.m_height)
{
    //TODO : copy hte content of the vector
    //we probably also need to copy the sprites..
    // -> deep copy
}

~Scene()
{
    //we shall delete all sprites...
    for ( int i=0; i< m_spritelist.size(); i++ )
    {
        delete m_spritelist[i], m_spritelist[i]= NULL;
    }
    m_spritelist.clear();
}


bool setWidth(int width)
{
    m_width = width;
    return true;
}

bool setHeight(int height)
{
    m_height = height;
    return true;
}



bool add( std::auto_ptr<Sprite> s) // sink auto_ptr
{
    m_spritelist.push_back(s.release());
    return true; //todo
}

bool moveRandom()
{
        for ( unsigned int i=0; i<m_spritelist.size(); i++ )
        {
            int newx = rand() % m_width;
            int newy = rand() % m_height;
            m_spritelist[i]->moveto( newx, newy );
        }
}

//This return the list of sprite that need to be displayed, with the correct screen coordinates and dimensions
std::vector<Sprite*> getRenderList() const
{
    std::vector<Sprite*> res;

    for ( unsigned int i=0; i<m_spritelist.size(); i++)
    {

        int posx = m_spritelist[i]->posX();
        int posy = m_spritelist[i]->posY();
//#ifdef DEBUG
        //std::cout << "X = " << posx << " Y= " << posy;
//#endif
        if ( ( posx > 0 && posx < m_width ) //TODO : correct this
                && ( posy>0 && posy< m_height ) ) //TODO : and that
        {
            res.push_back(m_spritelist[i]);
        }
    }
    return res;
}

};


class MyEngine
{
    int m_width;
    int m_height;

    std::auto_ptr<Scene> pvm_scene;
    std::auto_ptr<Image> loadedimage;


public:

	MyEngine(int width,int height)
	{
	        //TODO : improve this section by improving ImageLoader...
    ImageLoader loader;
    loadedimage = loader.load("test/data/smiley.bmp") ;

    pvm_scene.reset( new Scene(width,height) );

	}

    virtual ~MyEngine(){}

    bool addSmiley()
    {

    std::auto_ptr<Sprite> sp1(new Sprite());
    sp1->setImage(loadedimage.get());

    return pvm_scene->add(sp1);

    }

	bool init(int width, int height)
	{
	    /* initialize random seed: */
        srand ( (unsigned)time(NULL) );


	    m_width = width;
	    m_height = height;

        pvm_scene->setWidth(width);
        pvm_scene->setHeight(height);



		return true;
	}

	bool resize(int width, int height)
	{

	    m_width = width;
	    m_height = height;

        pvm_scene->setWidth(width);
        pvm_scene->setHeight(height);

		return true;
	}

    bool newframe(unsigned long framerate, unsigned long elapsedticks )
    {
        pvm_scene->moveRandom();
        return true;
    }

	bool render(ScreenBuffer & screen) const
    {

    //the scene sould here decide which sprite get displayed or not
    //Maybe we ll do that in Screenbuffer later if small code enough...
    std::vector<Sprite*> rlist = pvm_scene->getRenderList();

    for ( unsigned int i = 0; i< rlist.size(); i++)
    {
        //TODO make sure the pointer is valid here
        assert ( rlist[i] && "ERROR : sprite has been deleted before render!!!" );

        if ( rlist[i]->hasImage() )
        {
            screen.blit(rlist[i]->getImage(),Point(rlist[i]->posX(), rlist[i]->posY()));
        }
    }

		return true;
    }

};


int main(int argc, char** argv)
{

	bool ogl = false;
	if (argc > 1 && std::string(argv[1]) == "opengl" ) ogl = true;

    //Starting with usual SDL window
    App::getInstance().initVideo(false,ogl,true,false);
	App::getInstance().setName ("RAGE::SDL test Scene and refresh strategy");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(800,600); // using autodetected bpp

	std::auto_ptr<MyEngine> engine(new MyEngine(800,600));

	App::getInstance().getDisplay().resetInitCallback(&*engine,&MyEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(&*engine,&MyEngine::resize);
	App::getInstance().getDisplay().resetNewFrameCallback(&*engine,&MyEngine::newframe);
	App::getInstance().getDisplay().resetRenderCallback(&*engine,&MyEngine::render);

    engine->addSmiley();
    engine->addSmiley();

    if(App::getInstance().getDisplay().show())
    {
       App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}



