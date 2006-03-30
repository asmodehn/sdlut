#include "BattleField.hh"

BattleField_Sprite::BattleField_Sprite()
{
	X = 0;
	Y = 0;

	//Default terrain type (grass FOR THE MOMENT)
	Terrain_Type = 01;

	//Default Clip, the Grass Clip
	BG_Clip.setx(198);
	BG_Clip.sety(132);
	BG_Clip.setw(32);
	BG_Clip.seth(32);
}
BattleField_Sprite::BattleField_Sprite(int x, int y, int terrain_type, Rect bg_clip)
{
	X = x;
	Y = x;
	Terrain_Type = terrain_type;
	BG_Clip = bg_clip;
}
BattleField_Sprite::~BattleField_Sprite()
{
}
//BattleField Constructor
BattleField::BattleField()
{
	//Create rgbsurface that will be the BG with white color as transparent
	Background = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));
	P0_Logger << " Background Global Surface Creation : OK " << std::endl;

	//Grass Clip
	BattleField_Grass_Clip.setx(198);
	BattleField_Grass_Clip.sety(132);
	BattleField_Grass_Clip.setw(32);
	BattleField_Grass_Clip.seth(32);

	//The default clip is the grass clip
	BattleField_Clip = BattleField_Grass_Clip;
}
//BattleField Destructor
BattleField::~BattleField()
{
}
//BattleField interpretation from the file
std::vector<BattleField_Sprite*> BattleField::BattleField_Vector()
{

	//The tile offset
    int x=0, y=0;

	//The type of terrain that must be generated, by default grass type (!! FOR THE MOMENT!!)
	int Current_Terrain_Type = 01;
    
    //Open the map
    std::ifstream map("data/BattleField_Map.txt");

	//check if map has been loaded succesfully
    if(! map )
    {
		P0_Logger << " Can't open BattleField_Map.map " << std::endl;
		//exit(0);
    }

	/*char ch;
	
	while( map.get(ch) )
		P0_Logger << ch;

	while(!map.eof())
    {*/
    for( int i = 0; i < LEVEL_WIDTH/32; i++ )
	{
        //Determines what kind of tile will be made
        int Current_Terrain_Type = 01;

		//Read terrain type from map file
		map >> Current_Terrain_Type;

		//if the map file has a bug in it
		if( map.fail() == true )
		{
			P0_Logger << " BattleField_Map.txt corrupted " << std::endl;
			//exit(0);
		}

		if( Current_Terrain_Type == 01 )
		{
			BattleField_Clip = BattleField_Grass_Clip;
		}
		else // not listed type (??)
		{
			P0_Logger << " Terrain type present inside BattleField_Map.txt not recognized " << std::endl;
			BattleField_Clip = BattleField_Grass_Clip; //WILL BE SPACE HERE WHEN SPACE CLIP WILL BE AVAILABLE
		}

		//Create Monster & initialized it
		BattleField_Sprite* TheBattleField_Sprite = new BattleField_Sprite(x, y, Current_Terrain_Type, BattleField_Clip);

		//store the monster at the end of the vector
		BattleField_Sprite_Vector.push_back(TheBattleField_Sprite);

		//Move to next position
        x += 32;
        
        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;
            
            //Move to the next line
            y += 32;    
        }
	}

	//Close the battlefield map file
	map.close();

	return(BattleField_Sprite_Vector);
}
//Battlefield interpretation only inside range of the camera
bool BattleField::BattleField_Camera_Vector(Rect Camera)
{
}
//BattleField Render
bool BattleField::Render(VideoSurface & Screen)
{
	int x=0, y=0;

	//By default the clip is the grass clip (!! FOR THE MOMENT!!, next it will be the space clip)
	BattleField_Clip = BattleField_Grass_Clip;

	while (x<(SCREEN_WIDTH/32))
	{
		while (y<(SCREEN_HEIGHT/32 - 1)) //the -1 is here in order to not apply bg on the last line of the screen: the status bar
		{
			if (! Screen.blit(Background, Point::Point(x*32, y*32), BattleField_Clip) )
			{
				P0_Logger << " Background Generation Failed " << GetError() << std::endl;
			}
			y++;
		}
		x++;
		y=0;
	}

	//P0_Logger << " Background Generation : OK " << std::endl;
	return true;
}
