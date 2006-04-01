#include "BattleField.hh"

BattleField_Sprite::BattleField_Sprite()
{
	X = 0;
	Y = 0;

	//Default Ground type
	Ground_Type = EMPTY_GROUND;

	//Default Clip, the empty Clip
	BG_Clip.setx(198);
	BG_Clip.sety(165);
	BG_Clip.setw(32);
	BG_Clip.seth(32);
}
BattleField_Sprite::BattleField_Sprite(int x, int y, int ground_type, Rect bg_clip)
{
	X = x;
	Y = y;
	Ground_Type = ground_type;
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

	//Empty Clip
	BattleField_Empty_Clip.setx(198);
	BattleField_Empty_Clip.sety(165);
	BattleField_Empty_Clip.setw(32);
	BattleField_Empty_Clip.seth(32);

	//Grass Clip
	BattleField_Grass_Clip.setx(198);
	BattleField_Grass_Clip.sety(132);
	BattleField_Grass_Clip.setw(32);
	BattleField_Grass_Clip.seth(32);

	//Sand clip
	BattleField_Sand_Clip.setx(165);
	BattleField_Sand_Clip.sety(132);
	BattleField_Sand_Clip.setw(32);
	BattleField_Sand_Clip.seth(32);

	//River clip
	BattleField_River_Clip.setx(231);
	BattleField_River_Clip.sety(132);
	BattleField_River_Clip.setw(32);
	BattleField_River_Clip.seth(32);

	//The default clip is the empty clip
	BattleField_Clip = BattleField_Empty_Clip;
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

	//The type of Ground that must be generated, by default empty
	int Current_Ground_Type = EMPTY_GROUND;
    
    //Open the map
    std::ifstream BattleField_Map("data/BattleField_Map.txt");

	//check if map has been loaded succesfully
    if(! BattleField_Map )
    {
		P0_Logger << " Can't open BattleField_Map.map " << std::endl;
		//exit(0);
    }

	while(!BattleField_Map.eof())
	{
		//Read Ground type from map file
		BattleField_Map >> Current_Ground_Type;

		//if the map file has a bug in it
		if( BattleField_Map.fail() == true )
		{
			P0_Logger << " BattleField_Map.txt corrupted " << std::endl;
			break;
			//exit(0);
		}

		//assign the good clip relative to the type read from the map file
		if( Current_Ground_Type == EMPTY_GROUND )
		{
			BattleField_Clip = BattleField_Empty_Clip;
		}
		else if( Current_Ground_Type == GRASS_GROUND )
		{
			BattleField_Clip = BattleField_Grass_Clip;
		}
		else if( Current_Ground_Type == SAND_GROUND )
		{
			BattleField_Clip = BattleField_Sand_Clip;
		}
		else if( Current_Ground_Type == RIVER_GROUND )
		{
			BattleField_Clip = BattleField_River_Clip;
		}
		else // not listed type (??)
		{
			P0_Logger << " Ground type present inside BattleField_Map.txt not recognized " << std::endl;
			BattleField_Clip = BattleField_Empty_Clip; //than show the empty clip as if we are outside the battlefield
			Current_Ground_Type = 0; //set the ground type to empty in order to not crash
		}

		//Create Monster & initialized it
		BattleField_Sprite* TheBattleField_Sprite = new BattleField_Sprite(x, y, Current_Ground_Type, BattleField_Clip);

		//store the monster at the end of the vector
		myBattleField_Sprite_Vector.push_back(TheBattleField_Sprite);

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
	BattleField_Map.close();

	return(myBattleField_Sprite_Vector);
}
//BattleField Render
bool BattleField::Render(std::vector<BattleField_Sprite*> BattleField_Sprite_Vector, Rect Camera, VideoSurface & Screen)
{
	//Loop on all the vector
	for(int i=0; i < BattleField_Sprite_Vector.size(); i++)
	{
		//Check if the battlefield sprite is present on the screen
		//NOTE : the -16 is half of a character sprite. They are presents because the camera is centered on the middle of the character and so they allow good surface draw at the extreme top and extreme right of the screen
		if ( ((Camera.getx()-CH_WIDTH) <= BattleField_Sprite_Vector[i]->Get_X()) && ( BattleField_Sprite_Vector[i]->Get_X() < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= BattleField_Sprite_Vector[i]->Get_Y()) && ( BattleField_Sprite_Vector[i]->Get_Y() < (Camera.gety() + Camera.geth() - 32) ) )
		{
			//It's present than draw it
			if (! Screen.blit( Background, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BG_Clip() ) )
			{
				P0_Logger << " Background Generation Failed " << GetError() << std::endl;
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - 32, CURRENT_SCREEN_WIDTH, 32) );

	//P0_Logger << " Background Generation : OK " << std::endl;
	return true;
}
