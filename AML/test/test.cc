//test program
#include "AML.hh"

//tmp : logger is aimed only for internal use in AML
#include "Logger.hh"

//would be nice if we can put that in AML.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif

using namespace RAGE;
using namespace RAGE::AML;

class MySprite : public Sprite
{

    public:
    MySprite(std::string filename)
    : Sprite (filename)
    {

    }

bool render (SDL::VideoSurface *screen) const
{
    bool res = Sprite::render(screen);
    return res;
}


};

class MyKeyboard : public SDL::Keyboard
{
    Sprite * _activesprite;
    public:

    void setActive(Sprite * s)
    {
        _activesprite=s;
    }

    bool handleKeyEvent (SDL_keysym &keysym, bool pressed)
    {
    bool res = false;
            switch (keysym.sym)
            {
                case SDLK_ESCAPE:  if (pressed==false)
            {
#ifdef DEBUG
    Log << nl << "Quit requested !" << std::endl;
#endif
                _quitRequested=true;
                res=true;
            }
            break;
            case SDLK_UP : _activesprite->setPos(_activesprite->getPosX(),_activesprite->getPosY() -5); break;
            case SDLK_DOWN : _activesprite->setPos(_activesprite->getPosX(),_activesprite->getPosY() + 5 ); break;
            case SDLK_LEFT : _activesprite->setPos(_activesprite->getPosX() -5,_activesprite->getPosY());break;
            case SDLK_RIGHT : _activesprite->setPos(_activesprite->getPosX() +5,_activesprite->getPosY()); break;
                default : res = SDL::Keyboard::handleKeyEvent (keysym, pressed); break;
            }
            return res;
        }
};




int main ( int argc, char * argv [])
{
    Config c; //temporary just to get the log

    Logger testlog("AMLtest.log");

    //If using external resources :
    //testlog << nl << "Loading resources" << std::endl;
    //Resources.loadimage("");
    testlog << nl << "Loading sprite..." << std::endl;
    MySprite testbmp("data/AML_sprite.bmp");
    testbmp.setPos(320, 240);

    //If using specific input
    //testlog << nl << "Defining Input" << std::endl;
    MyKeyboard * mykeyb = new MyKeyboard();
    mykeyb->setActive(&testbmp);

    testlog << nl << "Creating the window..." << std::endl;
    Window mainWin("AML test", "data/AML_icon.bmp",640,480);


    SDL::App::getInstance().getWindow()->getEventManager()-> setKeyboard(mykeyb);

    testlog << nl << "Setting up the Scene..." << std::endl;
    mainWin.getScene()->put(&testbmp);

    testlog << nl << "Starting the main loop..." << std::endl;
    mainWin.loop();

    return 0;
}
