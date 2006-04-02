#include "BattleField.hh"

BattleField_Sprite::BattleField_Sprite()
{
	X = 0;
	Y = 0;

	//Default Ground type
	Ground_Type = EMPTY_GROUND;

	//Default Clip, the empty Clip from the default tileset (useful?)
	BattleField_Clip.setx(198);
	BattleField_Clip.sety(165);
	BattleField_Clip.setw(32);
	BattleField_Clip.seth(32);
}
BattleField_Sprite::BattleField_Sprite(int x, int y, int ground_type, Rect battlefield_clip)
{
	X = x;
	Y = y;
	Ground_Type = ground_type;
	BattleField_Clip = battlefield_clip;
}
BattleField_Sprite::~BattleField_Sprite()
{
}

//BattleField Constructor
BattleField::BattleField()
{
	//Create tileset surface
	BattleField_Tileset_Empty = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BattleField_Tileset_Grass = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BattleField_Tileset_Sands = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BattleField_Tileset_Rivers = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BattleField_Tileset_Trees = RGBSurface("data/Trees Tileset.png", Color(0x73, 0x6D, 0xB5));;

	//The default clip is the empty clip
	BattleField_Clip.setx(198);
	BattleField_Clip.sety(165);
	BattleField_Clip.setw(32);
	BattleField_Clip.seth(32);

	P0_Logger << " BattleField Construction : OK " << std::endl;
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
			//The empty clip
			BattleField_Clip.setx(198);
			BattleField_Clip.sety(165);
			BattleField_Clip.setw(32);
			BattleField_Clip.seth(32);
		}
		else if( Current_Ground_Type == GRASS_GROUND )
		{
			//Grass Clip
			BattleField_Clip.setx(198);
			BattleField_Clip.sety(132);
			BattleField_Clip.setw(32);
			BattleField_Clip.seth(32);
		}
		else if( Current_Ground_Type == SAND_GROUND )
		{
			//Sand clip
			BattleField_Clip.setx(165);
			BattleField_Clip.sety(132);
			BattleField_Clip.setw(32);
			BattleField_Clip.seth(32);
		}
		else if( Current_Ground_Type == RIVER_GROUND )
		{
			//River clip
			BattleField_Clip.setx(231);
			BattleField_Clip.sety(132);
			BattleField_Clip.setw(32);
			BattleField_Clip.seth(32);
		}
		else if( Current_Ground_Type == TREE_GROUND )
		{
			//Tree Clip (random tree from the tileset)
			BattleField_Clip.setx(32 * random(0,3));
			BattleField_Clip.sety(32 * random(0,7));
			BattleField_Clip.setw(32);
			BattleField_Clip.seth(32);
		}
		else // not listed type (??)
		{
			P0_Logger << " Ground type present inside BattleField_Map.txt not recognized " << std::endl;
			Current_Ground_Type = EMPTY_GROUND; //set the ground type to empty in order to not crash
		
			//Use default clip from the default tileset, the empty clip
			BattleField_Clip.setx(198);
			BattleField_Clip.sety(165);
			BattleField_Clip.setw(32);
			BattleField_Clip.seth(32);
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

	P0_Logger << " BattleField Sprite Vector Creation : OK " << std::endl;

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
			//To minimize vector access
			int Current_Ground_Type = BattleField_Sprite_Vector[i]->Get_Ground_Type();

			//It's present select the good tileset according to the terrain type
			if ( Current_Ground_Type == EMPTY_GROUND )
			{
				//Draw the battlefield empty sprite 
				if (! Screen.blit( BattleField_Tileset_Empty, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Empty Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == GRASS_GROUND )
			{
				//Draw the battlefield grass sprite 
				if (! Screen.blit( BattleField_Tileset_Grass, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Grass Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == SAND_GROUND )
			{
				//Draw the battlefield Sand sprite 
				if (! Screen.blit( BattleField_Tileset_Sands, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Sand Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == RIVER_GROUND )
			{
				//Draw the battlefield River sprite 
				if (! Screen.blit( BattleField_Tileset_Rivers, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " River Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == TREE_GROUND )
			{
				//Draw the battlefield background (grass)
				Rect BG_Clip;
				BG_Clip.setx(198);
				BG_Clip.sety(132);
				BG_Clip.setw(32);
				BG_Clip.seth(32);

				//Draw the tree background sprite (grass)
				if (! Screen.blit( BattleField_Tileset_Grass, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BG_Clip ) )
				{
					P0_Logger << " Grass BG Sprite Generation Failed " << GetError() << std::endl;
				}

				//Draw the battlefield Tree sprite 
				if (! Screen.blit( BattleField_Tileset_Trees, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Tree Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else // not listed type(!!??) : impossible because the vector was created with BattleField::BattleField_Vector()
			{
				P0_Logger << " Ground type present inside BattleField_Sprite_Vector not recognized !!?? " << std::endl;
				
				//Draw the battlefield empty sprite (aka the default)
				if (! Screen.blit( BattleField_Tileset_Empty, Point::Point( BattleField_Sprite_Vector[i]->Get_X() - Camera.getx(), BattleField_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BattleField_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Empty Sprite Generation Failed " << GetError() << std::endl;
				}
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - 32, CURRENT_SCREEN_WIDTH, 32) );

	//P0_Logger << " Background Generation : OK " << std::endl;
	return true;
}
