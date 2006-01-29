#include <iostream>
#include "AML.hh"

using namespace RAGE;
using namespace RAGE::AML;

class TankSprite : public Sprite
{
    public:
    TankSprite ( const Image & img)
    : Sprite (img,SDL::Rect(594, 165,32,32))
    {
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

    bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
        switch (s.getKey())
        {
            case KEscape:
            if (pressed==false)
            {
#ifdef DEBUG
                Log << nl << "Quit requested !" << std::endl;
#endif

                _quitRequested=true;
                res=true;
            }
            break;
            case KUp :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx(),_activesprite->getPos().gety() -5);
                res = true;
            }
            break;
            case KDown :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx(),_activesprite->getPos().gety() + 5 );
                res = true;
            }
            break;
            case KLeft :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx() -5,_activesprite->getPos().gety());
                res = true;
            }
            break;
            case KRight :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx() +5,_activesprite->getPos().gety());
                res = true;
            }
            break;
            default :
            break;
        }
        return res;
    }
};


int main()
{

    Config c; //temporary just to get the log

    Logger testlog("TankBrigade.log");

    testlog << nl << "Loading data..." << std::endl;
    Image img("spritelib_gpl/maze/tankbrigade.bmp",SDL::Color(0,0,0));

    TankSprite tank(img);
    MyKeyboard * mykeyb = new MyKeyboard();
    mykeyb->setActive(&tank);



    testlog << nl << "Creating the window..." << std::endl;
    Window mainWin("AML test", "data/AML_icon.bmp",640,480);

    SDL::App::getInstance().getWindow()->setBGColor(SDL::Color(128,0,0)); //doesnt work ??!!??
    SDL::App::getInstance().getWindow()->getEventManager()-> setKeyboard(mykeyb);

    testlog << nl << "Setting up the Scene..." << std::endl;
    mainWin.getScene()->put(&tank);

    testlog << nl << "Starting the main loop..." << std::endl;
    mainWin.loop();

    return 0;
}
