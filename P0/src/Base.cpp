#include "Base.hh"

//Create surface from an image function and optimized image to the desired format with white color as transparent color
SDL_Surface *create_surface( std::string filename ) 
{
    //Temporary storage for the Surface that's loaded
    SDL_Surface* loadedSurface = NULL;
    
    //The optimized Surface that will be used
    SDL_Surface* optimizedSurface = NULL;
    
    //Load the image
    //loadedSurface = SDL_LoadBMP( filename.c_str() );
	loadedSurface = IMG_Load( filename.c_str() );
    
    //If nothing went wrong in loading the image
    if( loadedSurface != NULL )
    {
        //Create an optimized Surface
        optimizedSurface = SDL_DisplayFormat( loadedSurface );
        
        //Free the old image
        SDL_FreeSurface( loadedSurface );
		
		//If the image was optimized just fine
        if( optimizedSurface != NULL )
        {
            //Set all pixels of color 0xFFFFFF (white) to be transparent
            SDL_SetColorKey( optimizedSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, 0xFFFFFF );
        }
    }
    
    //Return the optimized image
    return optimizedSurface;
}

//Surface blitting function wich blit a piece of a surface or the whole surface if no Rect area is defined
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Make a temporary rect to hold the offsets
    SDL_Rect Offset;
    
    //Give the offsets to the rect
    Offset.x = x;
    Offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &Offset );
}

//To check colission (small beginning of a physical engine^^)
bool check_collision(SDL_Rect &A, SDL_Rect &B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
            
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
//random function between min and max
int random(int min, int max)
{
	//srand( (unsigned)time( NULL ) );
	return min + (rand()%(max+1-min));
}
