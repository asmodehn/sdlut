#include <iostream>
#include "AML.hh"

using namespace RAGE;
using namespace RAGE::AML;

class TankSprite : public Sprite
{
    public:
    TankSprite ( const Image & img, std::string str)
    : Sprite (img,str)//,SDL::Rect(594, 165,32,32))
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

    Logger testlog("TankBrigade");

    testlog << nl << "Loading data..." << std::endl;
    Image img("spritelib_gpl/maze/tankbrigade.bmp",SDL::Color(0,0,128)); //transparency ??
    //describing the image content
    //from trunk/depend/tankbrigade rev 129
    img.setComponent(SDL::Rect(495,33,32,32), "GreenTank", 0, 0);
    img.setComponent(SDL::Rect(495,66,32,32), "GreenTank", 0, 1);
    img.setComponent(SDL::Rect(495,99,32,32), "GreenTank", 0, 2);
    img.setComponent(SDL::Rect(528,33,32,32), "GreenTank", 0, 9);
    img.setComponent(SDL::Rect(561,33,32,32), "GreenTank", 0, 8);
    img.setComponent(SDL::Rect(594,33,32,32), "GreenTank", 0, 7);
    img.setComponent(SDL::Rect(627,33,32,32), "GreenTank", 0, 6);
    img.setComponent(SDL::Rect(660,33,32,32), "GreenTank", 0, 5);
    img.setComponent(SDL::Rect(693,33,32,32), "GreenTank", 0, 4);
    img.setComponent(SDL::Rect(726,33,32,32), "GreenTank", 0, 3);

    img.setComponent(SDL::Rect(495,198,32,32), "GreenTank", 1, 0);
    img.setComponent(SDL::Rect(495,165,32,32), "GreenTank", 1, 1);
    img.setComponent(SDL::Rect(495,132,32,32), "GreenTank", 1, 2);
    img.setComponent(SDL::Rect(528,66,32,32), "GreenTank", 1, 9);
    img.setComponent(SDL::Rect(561,66,32,32), "GreenTank", 1, 8);
    img.setComponent(SDL::Rect(594,66,32,32), "GreenTank", 1, 7);
    img.setComponent(SDL::Rect(627,66,32,32), "GreenTank", 1, 6);
    img.setComponent(SDL::Rect(660,66,32,32), "GreenTank", 1, 5);
    img.setComponent(SDL::Rect(693,66,32,32), "GreenTank", 1, 4);
    img.setComponent(SDL::Rect(726,66,32,32), "GreenTank", 1, 3);


    img.setComponent(SDL::Rect(594,99,32,32), "GreenTank", 2, 0);
    img.setComponent(SDL::Rect(627,66,32,32), "GreenTank", 2, 1);
    img.setComponent(SDL::Rect(660,99,32,32), "GreenTank", 2, 2);
    img.setComponent(SDL::Rect(561,99,32,32), "GreenTank", 2, 9);
    img.setComponent(SDL::Rect(561,132,32,32), "GreenTank", 2, 8);
    img.setComponent(SDL::Rect(561,165,32,32), "GreenTank", 2, 7);
    img.setComponent(SDL::Rect(561,198,32,32), "GreenTank", 2, 6);
    img.setComponent(SDL::Rect(561,231,32,32), "GreenTank", 2, 5);
    img.setComponent(SDL::Rect(561,264,32,32), "GreenTank", 2, 4);
    img.setComponent(SDL::Rect(561,297,32,32), "GreenTank", 2, 3);

    img.setComponent(SDL::Rect(660,132,32,32), "GreenTank", 3, 0);
    img.setComponent(SDL::Rect(627,132,32,32), "GreenTank", 3, 1);
    img.setComponent(SDL::Rect(594,132,32,32), "GreenTank", 3, 2);
    img.setComponent(SDL::Rect(528,99,32,32), "GreenTank", 3, 9);
    img.setComponent(SDL::Rect(528,132,32,32), "GreenTank", 3, 8);
    img.setComponent(SDL::Rect(528,165,32,32), "GreenTank", 3, 7);
    img.setComponent(SDL::Rect(528,198,32,32), "GreenTank", 3, 6);
    img.setComponent(SDL::Rect(528,231,32,32), "GreenTank", 3, 5);
    img.setComponent(SDL::Rect(528,264,32,32), "GreenTank", 3, 4);
    img.setComponent(SDL::Rect(528,297,32,32), "GreenTank", 3, 3);


    TankSprite tank(img,"GreenTank");
    MyKeyboard * mykeyb = new MyKeyboard();
    mykeyb->setActive(&tank);



    testlog << nl << "Creating the window..." << std::endl;
    Window mainWin("AML test", "data/AML_icon.bmp",640,480);

    SDL::App::getInstance().getWindow()->setBGColor(SDL::Color(50,50,50));
    SDL::App::getInstance().getWindow()->getEventManager()-> setKeyboard(mykeyb);

    testlog << nl << "Setting up the Scene..." << std::endl;
    mainWin.getScene()->put(&tank);

    testlog << nl << "Starting the main loop..." << std::endl;
    mainWin.loop();

    return 0;
}
