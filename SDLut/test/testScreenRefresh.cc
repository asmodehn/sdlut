#include "TestCommon.hh" //to get argparser

using namespace SDLut;

Logger testlog("ScreenRefresh");

class Assert : public AssertEngine
{
    std::vector<video::Rect> assertedrectlist; //list of different rects x num of colors ( multiple frame )
    std::vector<video::Color> colorlist; // list of different colors ( one frame )
public:
    Assert(Logger& l, ArgParser& ap,std::vector<video::Rect> assertrectlist, std::vector<video::Color> clist)
            : AssertEngine(l,ap), assertedrectlist(assertrectlist), colorlist(clist)
    {
        if ( ! testlog.isFileLogEnabled() ) testlog.enableFileLog("TestScreenRefresh.log");
    }

    bool assertresize(int width, int height)
    {
        std::vector<video::Rect>::iterator assertedrect = assertedrectlist.begin();
        //checking all rects are in screen zone
        while ( assertedrect != assertedrectlist.end() )
        {
            if (assertedrect->getx() < 0) assertedrect->resetx(0);
            if (assertedrect->gety() < 0) assertedrect->resety(0);
            if ( (int)(assertedrect->getx() + assertedrect->getw() ) > width ) assertedrect->resetx( width - assertedrect->getw() );
            if ( (int)(assertedrect->gety() + assertedrect->geth() ) > height ) assertedrect->resety( height - assertedrect->geth() );
            assertedrect++;
        }
        return true;
    }
    bool assertrender(video::ScreenBuffer& sb) const
    {
        static unsigned int frame_num = 0;

        bool res = true;

        //getting to proper frame rects
        std::vector<video::Rect>::const_iterator assertedrect = assertedrectlist.begin() + (frame_num * colorlist.size()) % assertedrectlist.size();
        std::vector<video::Color>::const_iterator color = colorlist.begin();
        while ( color != colorlist.end() )
        {
        for ( unsigned int y = 0; y < assertedrect->geth(); y++)
        {
            for ( unsigned int x = 0; x < assertedrect->getw(); x ++)
            {
                video::Color gotclr = sb.getColorAt(x + assertedrect->getx(),y + assertedrect->gety());
                res = res && ( gotclr == *color);
            }
        }
        assertedrect++;
        color++;
        }

        if ( ! res ) logError("Error : Wrong color detected");

        frame_num ++;
        return res ;
    }
};

class Test : public TestEngine
{
    std::vector<video::Rect> testedrectlist;
    std::vector<video::Color> colorlist;
    std::vector<video::Image> imglist;
public:

    Test(Logger& l, Assert & a, std::vector<video::Rect> testrectlist, std::vector<video::Color> clist)
            : TestEngine(l,a), testedrectlist(testrectlist),colorlist(clist)
    {
    }

    bool resize(int width, int height)
    {
        bool res = true;

        std::vector<video::Rect>::iterator testedrect = testedrectlist.begin();
        while ( testedrect != testedrectlist.end() )
        {

        std::vector<video::Color>::iterator color = colorlist.begin();
        while ( color != colorlist.end() )
        {
            //check rect size
        if (testedrect->getx() < 0) testedrect->resetx(0);
        if (testedrect->gety() < 0) testedrect->resety(0);
        if ( (int)(testedrect->getx() + testedrect->getw()) > width ) testedrect->resetx( width - testedrect->getw() );
        if ( (int)(testedrect->gety() + testedrect->geth()) > height ) testedrect->resety( height - testedrect->geth() );

            //preparing images
            video::Image img;
            res = img.resize(testedrect->getw(),testedrect->geth());
            res = res && img.fill(*color);

            //Note : This implies Image copy works as for any POD type.
            imglist.push_back(img);

            color ++;
            testedrect++;
        }


        }

        //img.saveBMP("beforetest.bmp");
        return res;
    }

    bool newframe(unsigned long framerate, unsigned long deltaticks) // not mandatory
    {
        //static int cnt=0;
        //std::stringstream fname;
        //fname << "render_" << cnt++ << ".bmp";
        //testlog << nl << "DEBUG : " << fname.str() << " created";
        //img.saveBMP(fname.str());
        return true;
    }

    bool render(video::ScreenBuffer& sb) const
    {
        static unsigned int frame_num = 0;

        bool res = true;

        //getting to proper frame rects
        //in case we are not in auto and looping , we get modulo size
        std::vector<video::Rect>::const_iterator testedrect = testedrectlist.begin() + (frame_num * colorlist.size() ) % testedrectlist.size();
        std::vector<video::Image>::const_iterator img = imglist.begin() +  + (frame_num * colorlist.size() ) % imglist.size();

        std::vector<video::Color>::const_iterator color = colorlist.begin();

        while ( color != colorlist.end() )
        {

        //work around for constness of render
        video::Rect dst = *testedrect;

        //BUG WORKAROUND !!!
        //refresh doesnt seem to work properly here...
        // TOFIX !!!
        //sb.requestFullRefresh();


        res = res && sb.blit(*img, dst);

        color++;
        testedrect++;
        img++;
        }

        frame_num++;

        return res;



    }
};

std::vector<video::Rect> generate_rect(int number, int screenwidth, int screenheight)
{
    std::vector<video::Rect> result;
    while (number > 0)
    {

    video::Rect rct(Randomizer<unsigned int>::get(0,screenwidth),Randomizer<unsigned int>::get(0,screenheight - 64 )); //keeping some space for logos...
    rct.resetw(Randomizer<unsigned int>::get(1,screenwidth - rct.getx()));
    rct.reseth(Randomizer<unsigned int>::get(1,screenheight-64 - rct.gety()));
    //quick check
    if (rct.getw() < 1) rct.resetw();
    if (rct.geth() < 1) rct.reseth();

    result.push_back(rct);

    number--;
    }
return result;
}

std::vector<video::Color> generate_color(int number)
{
    std::vector<video::Color> result;
    while (number > 0)
    {

        ///generating color and rect test set
    video::Color color(Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get());

    result.push_back(color);

    number--;
    }
return result;
}

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video Screen Blitting test ");

    //Setting Display size and BPP
    App::getInstance().getDisplay().requestSize(300,240); // using autodetected bpp
    App::getInstance().getDisplay().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    //between 0 and 10 colors in one frame
    int num_colors = Randomizer<unsigned char>::get(0,10);
    //between 0 and 255 frames in total
    int num_frames = Randomizer<unsigned char>::get();

    std::vector<video::Color> clist = generate_color(num_colors);
    std::vector<video::Rect> rlist = generate_rect(num_colors * num_frames, 300, 240);

    Assert asrt(testlog,args,rlist,clist);
    Test engine(testlog,asrt,rlist,clist);

    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}



