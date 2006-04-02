#include "BattleField.hh"

BattleField_Sprite::BattleField_Sprite()
{
	X = 0;
	Y = 0;

	//Default Ground type
	BattleField_Type = EMPTY_GROUND;

	//Default Clip, the empty Clip from the default tileset (useful?)
	BattleField_Clip.setx(198);
	BattleField_Clip.sety(165);
	BattleField_Clip.setw(32);
	BattleField_Clip.seth(32);
}
BattleField_Sprite::BattleField_Sprite(int x, int y, int battlefield_type, Rect battlefield_clip)
{
	X = x;
	Y = y;
	BattleField_Type = battlefield_type;
	BattleField_Clip = battlefield_clip;
}
BattleField_Sprite::~BattleField_Sprite()
{
}

//BackGround Constructor
BackGround::BackGround()
{
	//Create tileset surface
	BackGround_Tileset_Empty = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BackGround_Tileset_Grass = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BackGround_Tileset_Sands = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;
	BackGround_Tileset_Rivers = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));;

	//The default clip is the empty clip
	BackGround_Clip.setx(198);
	BackGround_Clip.sety(165);
	BackGround_Clip.setw(32);
	BackGround_Clip.seth(32);

	P0_Logger << " BackGround Construction : OK " << std::endl;
}
//BackGround Destructor
BackGround::~BackGround()
{
}
//BackGround interpretation from the file
std::vector<BattleField_Sprite*> BackGround::BackGround_Vector()
{
	//The tile offset
    int x=0, y=0;

	//The type of Ground that must be generated, by default empty
	int Current_Ground_Type = EMPTY_GROUND;
    
    //Open the map
    std::ifstream BackGround_Map("data/BackGround_Map.txt");

	//check if map has been loaded succesfully
    if(! BackGround_Map )
    {
		P0_Logger << " Can't open BackGround_Map.txt " << std::endl;
		Timer::delay(3000);
		exit(0);
    }

	while(!BackGround_Map.eof())
	{
		//Read Ground type from map file
		BackGround_Map >> Current_Ground_Type;

		//if the map file has a bug in it
		if( BackGround_Map.fail() == true )
		{
			P0_Logger << " BackGround_Map.txt corrupted " << std::endl;
			break;
			//exit(0);
		}

		//assign the good clip relative to the type read from the map file
		if( Current_Ground_Type == EMPTY_GROUND )
		{
			//The empty clip
			BackGround_Clip.setx(198);
			BackGround_Clip.sety(165);
			BackGround_Clip.setw(32);
			BackGround_Clip.seth(32);
		}
		else if( Current_Ground_Type == GRASS_GROUND )
		{
			//Grass Clip
			BackGround_Clip.setx(198);
			BackGround_Clip.sety(132);
			BackGround_Clip.setw(32);
			BackGround_Clip.seth(32);
		}
		else if( Current_Ground_Type == SAND_GROUND )
		{
			//Sand clip
			BackGround_Clip.setx(165);
			BackGround_Clip.sety(132);
			BackGround_Clip.setw(32);
			BackGround_Clip.seth(32);
		}
		else if( Current_Ground_Type == RIVER_GROUND )
		{
			//River clip
			BackGround_Clip.setx(231);
			BackGround_Clip.sety(132);
			BackGround_Clip.setw(32);
			BackGround_Clip.seth(32);
		}
		else // not listed type (??)
		{
			P0_Logger << " Ground type present inside BackGround_Map.txt not recognized " << std::endl;
			Current_Ground_Type = EMPTY_GROUND; //set the ground type to empty in order to not crash
		
			//Use default clip from the default tileset, the empty clip
			BackGround_Clip.setx(198);
			BackGround_Clip.sety(165);
			BackGround_Clip.setw(32);
			BackGround_Clip.seth(32);
		}

		//Create Monster & initialized it
		BattleField_Sprite* TheBackGround_Sprite = new BattleField_Sprite(x, y, Current_Ground_Type, BackGround_Clip);

		//store the monster at the end of the vector
		myBackGround_Sprite_Vector.push_back(TheBackGround_Sprite);

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

	//Close the BackGround map file
	BackGround_Map.close();

	P0_Logger << " BackGround Sprite Vector Creation : OK " << std::endl;

	return(myBackGround_Sprite_Vector);
}
//BackGround Render
bool BackGround::Render(std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, Rect Camera, VideoSurface & Screen)
{
	//Loop on all the vector
	for(int i=0; i < BackGround_Sprite_Vector.size(); i++)
	{
		//Check if the BackGround sprite is present on the screen
		//NOTE : the -16 is half of a character sprite. They are presents because the camera is centered on the middle of the character and so they allow good surface draw at the extreme top and extreme right of the screen
		if ( ((Camera.getx()-CH_WIDTH) <= BackGround_Sprite_Vector[i]->Get_X()) && ( BackGround_Sprite_Vector[i]->Get_X() < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= BackGround_Sprite_Vector[i]->Get_Y()) && ( BackGround_Sprite_Vector[i]->Get_Y() < (Camera.gety() + Camera.geth() - 32) ) )
		{
			//To minimize vector access
			int Current_Ground_Type = BackGround_Sprite_Vector[i]->Get_BattleField_Type();

			//It's present select the good tileset according to the terrain type
			if ( Current_Ground_Type == EMPTY_GROUND )
			{
				//Draw the BackGround empty sprite 
				if (! Screen.blit( BackGround_Tileset_Empty, Point::Point( BackGround_Sprite_Vector[i]->Get_X() - Camera.getx(), BackGround_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Empty Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == GRASS_GROUND )
			{
				//Draw the BackGround grass sprite 
				if (! Screen.blit( BackGround_Tileset_Grass, Point::Point( BackGround_Sprite_Vector[i]->Get_X() - Camera.getx(), BackGround_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Grass Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == SAND_GROUND )
			{
				//Draw the BackGround Sand sprite 
				if (! Screen.blit( BackGround_Tileset_Sands, Point::Point( BackGround_Sprite_Vector[i]->Get_X() - Camera.getx(), BackGround_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Sand Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Ground_Type == RIVER_GROUND )
			{
				//Draw the BackGround River sprite 
				if (! Screen.blit( BackGround_Tileset_Rivers, Point::Point( BackGround_Sprite_Vector[i]->Get_X() - Camera.getx(), BackGround_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " River Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else // not listed type(!!??) : impossible because the vector was created with BackGround::BackGround_Vector()
			{
				P0_Logger << " Ground type present inside BackGround_Sprite_Vector not recognized !!?? " << std::endl;
				
				//Draw the BackGround empty sprite (aka the default)
				if (! Screen.blit( BackGround_Tileset_Empty, Point::Point( BackGround_Sprite_Vector[i]->Get_X() - Camera.getx(), BackGround_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector[i]->Get_BattleField_Clip() ) )
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


//Environement Constructor
Environement::Environement()
{
	//Create tileset surface
	Environement_Tileset_Trees = RGBSurface("data/Trees Tileset.png", Color(0x73, 0x6D, 0xB5));;

	//The default clip is the minimal clip (we don't want to blit something in this case so it dont really matter)
	Environement_Clip.setx(0);
	Environement_Clip.sety(0);
	Environement_Clip.setw(0);
	Environement_Clip.seth(0);

	P0_Logger << " Environement Construction : OK " << std::endl;
}
//Environement Destructor
Environement::~Environement()
{
}
//Environement interpretation from the file
std::vector<BattleField_Sprite*> Environement::Environement_Vector()
{
	//The tile offset
    int x=0, y=0;

	//The type of Ground that must be generated, by default empty
	int Current_Env_Item_Type = NOTHING_ENV_ITEM;
    
    //Open the map
    std::ifstream Environement_Map("data/Environement_Map.txt");

	//check if map has been loaded succesfully
    if(! Environement_Map )
    {
		P0_Logger << " Can't open Environement_Map.txt " << std::endl;
		Timer::delay(3000);
		exit(0);
    }

	while(!Environement_Map.eof())
	{
		//Read Ground type from map file
		Environement_Map >> Current_Env_Item_Type;

		//if the map file has a bug in it
		if( Environement_Map.fail() == true )
		{
			P0_Logger << " Environement_Map.txt corrupted " << std::endl;
			break;
			//exit(0);
		}

		//assign the good clip relative to the type read from the map file
		if( Current_Env_Item_Type == NOTHING_ENV_ITEM )
		{
			//Minimal clip (we won't blit something in this case so it dont really matter)
			Environement_Clip.setx(0);
			Environement_Clip.sety(0);
			Environement_Clip.setw(0);
			Environement_Clip.seth(0);
		}
		else if( Current_Env_Item_Type == TREE_ENV_ITEM )
		{
			//Tree Clip (random tree from the tileset)
			Environement_Clip.setx(32 * random(0,3));
			Environement_Clip.sety(32 * random(0,7));
			Environement_Clip.setw(32);
			Environement_Clip.seth(32);
		}
		else // not listed type (??)
		{
			P0_Logger << " Environement item present inside Environement_Map.txt not recognized " << std::endl;
			Current_Env_Item_Type = NOTHING_ENV_ITEM; //set the environement type to nothing in order to not crash
		
			//Minimal clip (we won't blit something in this case so it dont really matter)
			Environement_Clip.setx(0);
			Environement_Clip.sety(0);
			Environement_Clip.setw(0);
			Environement_Clip.seth(0);
		}

		//Create Monster & initialized it
		BattleField_Sprite* TheEnvironement_Sprite = new BattleField_Sprite(x, y, Current_Env_Item_Type, Environement_Clip);

		//store the monster at the end of the vector
		myEnvironement_Sprite_Vector.push_back(TheEnvironement_Sprite);

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

	//Close the Environement map file
	Environement_Map.close();

	P0_Logger << " Environement Sprite Vector Creation : OK " << std::endl;

	return(myEnvironement_Sprite_Vector);
}
//Environement Render
bool Environement::Render(std::vector<BattleField_Sprite*> Environement_Sprite_Vector, Rect Camera, VideoSurface & Screen)
{
	//Loop on all the vector
	for(int i=0; i < Environement_Sprite_Vector.size(); i++)
	{
		//Check if the Environement sprite is present on the screen
		//NOTE : the -16 is half of a character sprite. They are presents because the camera is centered on the middle of the character and so they allow good surface draw at the extreme top and extreme right of the screen
		if ( ((Camera.getx()-CH_WIDTH) <= Environement_Sprite_Vector[i]->Get_X()) && ( Environement_Sprite_Vector[i]->Get_X() < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= Environement_Sprite_Vector[i]->Get_Y()) && ( Environement_Sprite_Vector[i]->Get_Y() < (Camera.gety() + Camera.geth() - 32) ) )
		{
			//To minimize vector access
			int Current_Env_Item_Type = Environement_Sprite_Vector[i]->Get_BattleField_Type();

			//It's present, then select the good tileset according to the environement item type
			if ( Current_Env_Item_Type == NOTHING_ENV_ITEM )
			{
				//Don't blit anything
			}
			else if( Current_Env_Item_Type == TREE_ENV_ITEM )
			{
				//Draw the Environement Tree sprite 
				if (! Screen.blit( Environement_Tileset_Trees, Point::Point( Environement_Sprite_Vector[i]->Get_X() - Camera.getx(), Environement_Sprite_Vector[i]->Get_Y() - Camera.gety() ), Environement_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Tree Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else // not listed type(!!??) : impossible because the vector was created with Environement::Environement_Vector()
			{
				P0_Logger << " Environnement item type present inside Environement_Sprite_Vector not recognized !!?? " << std::endl;
				
				//Don't blit anything
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - 32, CURRENT_SCREEN_WIDTH, 32) );

	//P0_Logger << " Environement Generation : OK " << std::endl;*/
	return true;
}
