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

class MyLevel : public MxLib::MxMap
{
    public :

    MyLevel (MxLib::MxBitmap & bitmap, int tilesize, int Xsize, int Ysize )
    : MxMap(tilesize,Xsize,Ysize){
      //MAP
//    std::cout  << "map ok" << std::endl;
    int tileWaterTopLeft=loadnewSprite(bitmap, 231 , 231);
    int tileWaterTopRight=loadnewSprite(bitmap, 264 , 231);
    int tileWaterBottomRight=loadnewSprite(bitmap, 198 , 231);
    int tileWaterBottomLeft=loadnewSprite(bitmap, 165, 231);
    placeSprite(tileWaterTopLeft,0,0);
    placeSprite(tileWaterTopRight,19,0);
    placeSprite(tileWaterBottomRight,19,14);
    placeSprite(tileWaterBottomLeft,0,14);

    int tileWaterLeft=loadnewSprite(bitmap, 33 , 231);
    int tileWaterRight=loadnewSprite(bitmap, 66 , 231);
    int tileWaterTop=loadnewSprite(bitmap, 99 , 231);
    int tileWaterBottom=loadnewSprite(bitmap, 132, 231);
    placeSprite(tileWaterLeft,0,1);
    placeSprite(tileWaterLeft,0,2);
    placeSprite(tileWaterLeft,0,3);
    placeSprite(tileWaterLeft,0,4);
    placeSprite(tileWaterLeft,0,5);
    placeSprite(tileWaterLeft,0,6);
    placeSprite(tileWaterLeft,0,7);
    placeSprite(tileWaterLeft,0,8);
    placeSprite(tileWaterLeft,0,9);
    placeSprite(tileWaterLeft,0,10);
    placeSprite(tileWaterLeft,0,11);
    placeSprite(tileWaterLeft,0,12);
    placeSprite(tileWaterLeft,0,13);
    placeSprite(tileWaterRight,19,1);
    placeSprite(tileWaterRight,19,2);
    placeSprite(tileWaterRight,19,3);
    placeSprite(tileWaterRight,19,4);
    placeSprite(tileWaterRight,19,5);
    placeSprite(tileWaterRight,19,6);
    placeSprite(tileWaterRight,19,7);
    placeSprite(tileWaterRight,19,8);
    placeSprite(tileWaterRight,19,9);
    placeSprite(tileWaterRight,19,10);
    placeSprite(tileWaterRight,19,11);
    placeSprite(tileWaterRight,19,12);
    placeSprite(tileWaterRight,19,13);
    placeSprite(tileWaterTop,1,0);
    placeSprite(tileWaterTop,2,0);
    placeSprite(tileWaterTop,3,0);
    placeSprite(tileWaterTop,4,0);
    placeSprite(tileWaterTop,5,0);
    placeSprite(tileWaterTop,6,0);
    placeSprite(tileWaterTop,7,0);
    placeSprite(tileWaterTop,8,0);
    placeSprite(tileWaterTop,9,0);
    placeSprite(tileWaterTop,10,0);
    placeSprite(tileWaterTop,11,0);
    placeSprite(tileWaterTop,12,0);
    placeSprite(tileWaterTop,13,0);
    placeSprite(tileWaterTop,14,0);
    placeSprite(tileWaterTop,15,0);
    placeSprite(tileWaterTop,16,0);
    placeSprite(tileWaterTop,17,0);
    placeSprite(tileWaterTop,18,0);
    placeSprite(tileWaterBottom,1,14);
    placeSprite(tileWaterBottom,2,14);
    placeSprite(tileWaterBottom,3,14);
    placeSprite(tileWaterBottom,4,14);
    placeSprite(tileWaterBottom,5,14);
    placeSprite(tileWaterBottom,6,14);
    placeSprite(tileWaterBottom,7,14);
    placeSprite(tileWaterBottom,8,14);
    placeSprite(tileWaterBottom,9,14);
    placeSprite(tileWaterBottom,10,14);
    placeSprite(tileWaterBottom,11,14);
    placeSprite(tileWaterBottom,12,14);
    placeSprite(tileWaterBottom,13,14);
    placeSprite(tileWaterBottom,14,14);
    placeSprite(tileWaterBottom,15,14);
    placeSprite(tileWaterBottom,16,14);
    placeSprite(tileWaterBottom,17,14);
    placeSprite(tileWaterBottom,18,14);

    //fill inside
    int tileGrass=loadnewSprite(bitmap, 198, 132);

    for (int i=1; i < 19;i++)
        for (int j=1;j < 14;j++)
            placeSprite(tileGrass,i,j);

    //MAP DONE
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

MyLevel lvl(mainBitmap,32,20,15);


    MxSprite bluetank(mainBitmap,396,33,32);
//    std::cout  << "mxsprite ok" << std::endl;
    MyPlayerTank greentank(mainBitmap,363,33,32);
//    std::cout  << "myplayertank ok" << std::endl;

    input.setActive (&greentank);
//    std::cout  << "input setactive ok" << std::endl;


//std::cout  << "map define ok" << std::endl;
    scene.add(&lvl);
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


