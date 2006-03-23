#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;

#include <sys/stat.h>


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");
    App::getInstance().setName ("SDLtest");
    App::getInstance().initVideo(false,false,true,false);

	RWOps iconfile("data/SDL_icon.bmp","rb");

	iconfile.dumpCode("SDL_icon.c","_defaultIcon");

  
  /*Tests form Tutorial about RWOps...*/
  
 // FILE *file;
 // SDL_Surface *screen;
 // SDL_Surface *one;
 // SDL_Rect rect;

 // /* This is the RWops structure we'll be using */
 // SDL_RWops *rw;

 // SDL_Init(SDL_INIT_VIDEO);

 // atexit(SDL_Quit);

 // screen = SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF);

 // /* Here we get a file pointer to a bitmap */
 // file = fopen("data/SDL_icon.bmp", "r");
 // if(!file) {
 //   printf("Couldn't load data/SDL_icon.bmp\n");
 //   exit(1);
 // }

 // //getting the size of the file
 // struct stat statbuf;
 // fstat(fileno(file),&statbuf);

 // unsigned char * buffer = new unsigned char[statbuf.st_size];
 //   fread(buffer,sizeof(unsigned char),statbuf.st_size,file);

	//rw = SDL_RWFromMem(buffer, statbuf.st_size);
 // /* This is where we actually create our RWops structure.  Here we're
 //    instructing SDL to get it from the file pointer we just opened */
 // //rw = SDL_RWFromFile("data/SDL_logo.bmp", "rb");

 // /* SDL_LoadBMP_RW is the RWops version of the old standby,
 //    SDL_LoadBMP.  This will get the image from the RWops you passed
 //    in; in this case the file you've opened */
 // one = SDL_LoadBMP_RW(rw, 0);

 // /* Clean up after ourselves */
 // SDL_FreeRW(rw);
 // fclose(file);

 // /* Haphazard way of getting stuff to the screen */
 // rect.x = rect.y = 20;
 // rect.w = one -> w;
 // rect.y = one -> h;
 // SDL_BlitSurface(one, NULL, screen, &rect);

 // SDL_Flip(screen);

 // SDL_Delay(3000);

    return 0;
}


