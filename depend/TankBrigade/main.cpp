#include <iostream>

#include "MxSDL.h"
#include "MxScene.h"
#include "MxInput.h"

using namespace MxLib;

#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif


class MyPlayerTank : public MxLib::MxAnimatedSprite
{
    int speed;

public :
    MyPlayerTank (MxLib::MxBitmap & bitmap , unsigned int coordOriX, unsigned int coordOriY, unsigned int size)
            : MxLib::MxAnimatedSprite(bitmap ,coordOriX, coordOriY,size)
    {speed = 1;}
    MyPlayerTank (MxLib::MxBitmap & bitmap , unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY)
            : MxLib::MxAnimatedSprite(bitmap ,coordOriX, coordOriY,sizeOriX, sizeOriY)
    {speed = 1;}

    bool moveUp()
    {
        return move ( 0,- speed);
    }
    bool moveDown()
    {
        return move ( 0,speed);
    }
    bool moveLeft()
    {
        return move ( - speed,0);
    }
    bool moveRight()
    {
        return move ( speed,0);
    }

  void setspeed(int newspeed) { speed = newspeed; }
  int getspeed(void) {return speed;}


};

class MyInput : public MxLib::MxInput
{
    MyPlayerTank * active;

    virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
    {
        if (pressed)
        switch( keysym.sym )
        {
            case SDLK_UP:
            active->moveUp();
            break;
            case SDLK_DOWN:
            active->moveDown();
            break;
            case SDLK_LEFT:
            active->moveLeft();
            break;
            case SDLK_RIGHT:
            active->moveRight();
            break;
            default:
            break;
        }
        return MxLib::MxInput::handleKeyboardEvent(keysym,pressed);
    }
public :
    void setActive (MyPlayerTank * player)
    {
        active = player;
    }
};

int main()
{
    MxInit::init();
//std::cout  << "init ok" << std::endl;
    MxBitmap mainBitmap("tankbrigade.bmp"/*,SDL::Color(0,0,0)*/);
//std::cout  << "mxbitmap ok" << std::endl;
    MxScene scene;

//    std::cout  << "mxscene ok" << std::endl;
    MyInput input;
//    std::cout  << "input ok" << std::endl;
    //Fun but timer needed in SDLwrap...
    /*MxSprite splash(mainBitmap,33,430,360,240);

    scene.add(&splash,200,200);
    scene.display(25,2);
    */
    //scene.clear();

    MxSprite bluetank(mainBitmap,396,33,32);
//    std::cout  << "mxsprite ok" << std::endl;
    MyPlayerTank greentank(mainBitmap,363,33,32);
//    std::cout  << "myplayertank ok" << std::endl;

    input.setActive (&greentank);
//    std::cout  << "input setactive ok" << std::endl;

    //MAP
    MxMap map(32,20,15);
//    std::cout  << "map ok" << std::endl;
    int tileWaterTopLeft=map.loadnewSprite(mainBitmap, 231 , 231);
    int tileWaterTopRight=map.loadnewSprite(mainBitmap, 264 , 231);
    int tileWaterBottomRight=map.loadnewSprite(mainBitmap, 198 , 231);
    int tileWaterBottomLeft=map.loadnewSprite(mainBitmap, 165, 231);
    map.placeSprite(tileWaterTopLeft,0,0);
    map.placeSprite(tileWaterTopRight,19,0);
    map.placeSprite(tileWaterBottomRight,19,14);
    map.placeSprite(tileWaterBottomLeft,0,14);

    int tileWaterLeft=map.loadnewSprite(mainBitmap, 33 , 231);
    int tileWaterRight=map.loadnewSprite(mainBitmap, 66 , 231);
    int tileWaterTop=map.loadnewSprite(mainBitmap, 99 , 231);
    int tileWaterBottom=map.loadnewSprite(mainBitmap, 132, 231);
    map.placeSprite(tileWaterLeft,0,1);
    map.placeSprite(tileWaterLeft,0,2);
    map.placeSprite(tileWaterLeft,0,3);
    map.placeSprite(tileWaterLeft,0,4);
    map.placeSprite(tileWaterLeft,0,5);
    map.placeSprite(tileWaterLeft,0,6);
    map.placeSprite(tileWaterLeft,0,7);
    map.placeSprite(tileWaterLeft,0,8);
    map.placeSprite(tileWaterLeft,0,9);
    map.placeSprite(tileWaterLeft,0,10);
    map.placeSprite(tileWaterLeft,0,11);
    map.placeSprite(tileWaterLeft,0,12);
    map.placeSprite(tileWaterLeft,0,13);
    map.placeSprite(tileWaterRight,19,1);
    map.placeSprite(tileWaterRight,19,2);
    map.placeSprite(tileWaterRight,19,3);
    map.placeSprite(tileWaterRight,19,4);
    map.placeSprite(tileWaterRight,19,5);
    map.placeSprite(tileWaterRight,19,6);
    map.placeSprite(tileWaterRight,19,7);
    map.placeSprite(tileWaterRight,19,8);
    map.placeSprite(tileWaterRight,19,9);
    map.placeSprite(tileWaterRight,19,10);
    map.placeSprite(tileWaterRight,19,11);
    map.placeSprite(tileWaterRight,19,12);
    map.placeSprite(tileWaterRight,19,13);
    map.placeSprite(tileWaterTop,1,0);
    map.placeSprite(tileWaterTop,2,0);
    map.placeSprite(tileWaterTop,3,0);
    map.placeSprite(tileWaterTop,4,0);
    map.placeSprite(tileWaterTop,5,0);
    map.placeSprite(tileWaterTop,6,0);
    map.placeSprite(tileWaterTop,7,0);
    map.placeSprite(tileWaterTop,8,0);
    map.placeSprite(tileWaterTop,9,0);
    map.placeSprite(tileWaterTop,10,0);
    map.placeSprite(tileWaterTop,11,0);
    map.placeSprite(tileWaterTop,12,0);
    map.placeSprite(tileWaterTop,13,0);
    map.placeSprite(tileWaterTop,14,0);
    map.placeSprite(tileWaterTop,15,0);
    map.placeSprite(tileWaterTop,16,0);
    map.placeSprite(tileWaterTop,17,0);
    map.placeSprite(tileWaterTop,18,0);
    map.placeSprite(tileWaterBottom,1,14);
    map.placeSprite(tileWaterBottom,2,14);
    map.placeSprite(tileWaterBottom,3,14);
    map.placeSprite(tileWaterBottom,4,14);
    map.placeSprite(tileWaterBottom,5,14);
    map.placeSprite(tileWaterBottom,6,14);
    map.placeSprite(tileWaterBottom,7,14);
    map.placeSprite(tileWaterBottom,8,14);
    map.placeSprite(tileWaterBottom,9,14);
    map.placeSprite(tileWaterBottom,10,14);
    map.placeSprite(tileWaterBottom,11,14);
    map.placeSprite(tileWaterBottom,12,14);
    map.placeSprite(tileWaterBottom,13,14);
    map.placeSprite(tileWaterBottom,14,14);
    map.placeSprite(tileWaterBottom,15,14);
    map.placeSprite(tileWaterBottom,16,14);
    map.placeSprite(tileWaterBottom,17,14);
    map.placeSprite(tileWaterBottom,18,14);

    //fill inside
    int tileGrass=map.loadnewSprite(mainBitmap, 198, 132);

    for (int i=1; i < 19;i++)
        for (int j=1;j < 14;j++)
            map.placeSprite(tileGrass,i,j);

    //MAP DONE
//std::cout  << "map define ok" << std::endl;
    scene.add(&map);
//std::cout  << "scene add map ok" << std::endl;
    scene.add(&bluetank, 200,100);
//    std::cout  << "scene add sprite ok" << std::endl;
    scene.add(&greentank, 100, 100);
//    std::cout  << "scene add tanklpayer ok" << std::endl;


    while (!input.closed())
    {
        SDL::Event::handleEvents(input);
        scene.update();
        scene.display(25);
    }

}


