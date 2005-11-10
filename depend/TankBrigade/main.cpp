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

class MyResources
{
    MxLib::MxBitmap m_masterbmp;

public :
    MyResources( std::string masterbmp = "tankbrigade.bmp" )
            : m_masterbmp(masterbmp)
    {}

    MxLib::MxBitmap& getBitmap(void)
    {
        return m_masterbmp;
    }
};

//my game : the singleton...
class MyTankGame
{
private :

    MyResources resource;

    MyTankGame() : resource()
    {
        MxInit::init();
    }

    //to disable them
    MyTankGame(const MyTankGame&);
    MyTankGame& operator=(const MyTankGame&);
    ~MyTankGame()
    {}
    //

public:
    static MyTankGame& Instance()
    {
        static MyTankGame theInstance;
        return theInstance;
    }

    MyResources& getResources()
    {
        return resource;
    }

};


typedef enum
{
    up=0, down, left, right
}
Direction;


class MyBullet : public MxLib::MxAnimatedSprite
{
    typedef enum
    {
        alive =1 , exploding=0
    }
    State;

    State curstate;
    int speed;
    Direction dir;

    //0123 ->up,down,left,right 45 -> explode
    int frameset[6];

public:
    MyBullet( Direction initdir, int initspeed = 6)
            : MxLib::MxAnimatedSprite(MyTankGame::Instance().getResources().getBitmap() ,330, 33,32), speed(initspeed), dir(initdir)
    {
        frameset[0]=loadFrame(145,44,7,10);
        frameset[1]=loadFrame(244,44,7,10);
        frameset[2]=loadFrame(176,46,10,7);
        frameset[3]=loadFrame(209,46,10,7);
        frameset[4]=loadFrame(276,46,8,8);
        frameset[5]=loadFrame(308,44,11,11);

        curstate = alive;
        switch (dir)
        {
            case up :
            changeFrame(frameset[0]);
            break;

            case down :

            changeFrame(frameset[1]);
            break;

            case left :

            changeFrame(frameset[2]);
            break;

            case right :

            changeFrame(frameset[3]);
            break;

            default :
            std::cerr <<"shouldnt happen " << std::endl;
            break;
        }

    }



    void update(void)
    {
        if (curstate == alive)
            switch (dir)
            {
                case up :
                MxLib::MxAnimatedSprite::move ( 0,- speed);
                break;

                case down :

                MxLib::MxAnimatedSprite::move ( 0,speed);
                break;

                case left :

                MxLib::MxAnimatedSprite::move ( - speed,0);
                break;

                case right :

                MxLib::MxAnimatedSprite::move ( speed,0);
                break;

                default :
                std::cerr <<"shouldnt happen " << std::endl;
                break;
            }
        else
            changeFrame(5);
    }

    bool collide (const SDL::Rect & intersection)
    {
        //explode
        curstate = exploding;
        changeFrame(4);
    }
};


class MyTank : public MxLib::MxAnimatedSprite
{
    int speed;

public :

    Direction curdir;

    MyTank (MxLib::MxBitmap & bitmap , unsigned int coordOriX, unsigned int coordOriY, unsigned int size)
            : MxLib::MxAnimatedSprite(bitmap ,coordOriX, coordOriY,size)
    {
        speed = 3;
        curdir = up;
    }
    MyTank (MxLib::MxBitmap & bitmap , unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY)
            : MxLib::MxAnimatedSprite(bitmap ,coordOriX, coordOriY,sizeOriX, sizeOriY)
    {
        speed = 3;
        curdir = up;
    }

    bool move(Direction d)
    {
        switch (d)
        {
            case up :
            return MxLib::MxAnimatedSprite::move ( 0,- speed);
            break;

            case down :

            return MxLib::MxAnimatedSprite::move ( 0,speed);
            break;

            case left :

            return MxLib::MxAnimatedSprite::move ( - speed,0);
            break;

            case right :

            return MxLib::MxAnimatedSprite::move ( speed,0);
            break;

            default :
            std::cerr <<"shouldnt happen " << std::endl;
            break;
        }
    }
    void setspeed(int newspeed)
    {
        speed = newspeed;
    }
    int getspeed(void)
    {
        return speed;
    }


};

class MyPlayerTank : public MyTank
{
    typedef enum
    {
        exploding = -1, shooting = 0, alive = 1
    }
    State;
    State curstate;

    //index for frames... 012 ->shoot 3456789 -> move
    unsigned int upframe[10];
    unsigned int downframe[10];
    unsigned int leftframe[10];
    unsigned int rightframe[10];

public :


    MyPlayerTank ()
            : MyTank(MyTankGame::Instance().getResources().getBitmap(),495,33,32)
    {
        upframe[0] = loadFrame(495,33,32);
        upframe[1] = loadFrame(495,66,32);
        upframe[2] = loadFrame(495,99,32);
        upframe[9] = loadFrame(528,33,32);
        upframe[8] = loadFrame(561,33,32);
        upframe[7] = loadFrame(594,33,32);
        upframe[6] = loadFrame(627,33,32);
        upframe[5] = loadFrame(660,33,32);
        upframe[4] = loadFrame(693,33,32);
        upframe[3] = loadFrame(726,33,32);

        downframe[0] = loadFrame(495,198,32);
        downframe[1] = loadFrame(495,165,32);
        downframe[2] = loadFrame(495,132,32);
        downframe[9] = loadFrame(528,66,32);
        downframe[8] = loadFrame(561,66,32);
        downframe[7] = loadFrame(594,66,32);
        downframe[6] = loadFrame(627,66,32);
        downframe[5] = loadFrame(660,66,32);
        downframe[4] = loadFrame(693,66,32);
        downframe[3] = loadFrame(726,66,32);

        leftframe[0] = loadFrame(594,99,32);
        leftframe[1] = loadFrame(627,66,32);
        leftframe[2] = loadFrame(660,99,32);
        leftframe[9] = loadFrame(561,99,32);
        leftframe[8] = loadFrame(561,132,32);
        leftframe[7] = loadFrame(561,165,32);
        leftframe[6] = loadFrame(561,198,32);
        leftframe[5] = loadFrame(561,231,32);
        leftframe[4] = loadFrame(561,264,32);
        leftframe[3] = loadFrame(561,297,32);

        rightframe[0] = loadFrame(660,132,32);
        rightframe[1] = loadFrame(627,132,32);
        rightframe[2] = loadFrame(594,132,32);
        rightframe[9] = loadFrame(528,99,32);
        rightframe[8] = loadFrame(528,132,32);
        rightframe[7] = loadFrame(528,165,32);
        rightframe[6] = loadFrame(528,198,32);
        rightframe[5] = loadFrame(528,231,32);
        rightframe[4] = loadFrame(528,264,32);
        rightframe[3] = loadFrame(528,297,32);

        curstate = alive;
    }

    bool move(Direction d)
    {
        static unsigned int current = 0;
        switch (d)
        {
            case up :
            curdir = up;
            changeFrame(upframe[current++]);

            break;
            case down :
            curdir = down;
            changeFrame(downframe[current++]);


            break;
            case left :
            curdir = left;
            changeFrame(leftframe[current++]);

            break;
            case right :
            curdir = right;
            changeFrame(rightframe[current++]);
            break;
            default :
            std::cerr << "move nowhere shouldnt happen" << std::endl;
            break;
        }
        if  (current == 10)
            current = 0;
        if  (current == 1)
            current = 3;

        return MyTank::move(d);
    }

    inline bool shoot (void )
    {
        return shoot(curdir);
    }

    bool shoot (Direction d, int curframe = 0)
    {
        curstate = shooting;
        switch (d)
        {
            case up :
            std::cerr<< "shoot up" << std::endl;
            changeFrame(upframe[curframe++]);
            break;

            case down :
            std::cerr<< "shoot down" << std::endl;
            changeFrame(downframe[curframe++]);
            break;

            case left :
            std::cerr<< "shoot left" << std::endl;
            changeFrame(leftframe[curframe++]);
            break;

            case right :
            std::cerr<< "shoot right" << std::endl;
            changeFrame(rightframe[curframe++]);
            break;

            default :
            std::cerr << "shoot nowhere shouldnt happen" << std::endl;
            break;
        }
        if  (curframe == 3)
            curstate = alive;
        //timer with callback to launch...
        m_scene->spawn(m_sceneindex,new MyBullet(d));
    }


};

class MyEnnemyTank : public MyTank
{
public :
    MyEnnemyTank ()
            : MyTank(MyTankGame::Instance().getResources().getBitmap(),396,33,32)
    {}

}
;



class MyInput : public MxLib::MxInput
{
    MyPlayerTank * active;

    virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
    {
        if (pressed)
            switch( keysym.sym )
            {
                case SDLK_UP:
                active->move(up);
                break;
                case SDLK_DOWN:
                active->move(down);
                break;
                case SDLK_LEFT:
                active->move(left);
                break;
                case SDLK_RIGHT:
                active->move(right);
                break;
                case SDLK_SPACE:
                active->shoot();
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
            : MxMap(tilesize,Xsize,Ysize)
    {
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
    MyTankGame::Instance();

    MxScene scene(0,480,0,640);

    //    std::cout  << "mxscene ok" << std::endl;
    MyInput input;
    //    std::cout  << "input ok" << std::endl;
    //Fun but timer needed in SDLwrap...
    /*MxSprite splash(mainBitmap,33,430,360,240);

    scene.add(&splash,200,200);
    scene.display(25,2);
    */
    //scene.clear();

    MyLevel lvl(MyTankGame::Instance().getResources().getBitmap(),32,20,15);


    MyEnnemyTank bluetank;
    //    std::cout  << "mxsprite ok" << std::endl;
    MyPlayerTank greentank;
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



