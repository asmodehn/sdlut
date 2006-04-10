#include "BattleField.hh"

BattleField_Sprite::BattleField_Sprite()
{
	X = 0;
	Y = 0;

	//Default Ground type
	BattleField_Type = EMPTY_GROUND;

	//Default Clip (minimal clip)
	BattleField_Clip.setx(0);
	BattleField_Clip.sety(0);
	BattleField_Clip.setw(0);
	BattleField_Clip.seth(0);
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

BattleField_Zone::BattleField_Zone()
{
	Area.setx(0);
	Area.sety(0);
	Area.setw(0);
	Area.seth(0);
}
BattleField_Zone::BattleField_Zone(int x, int y, int w, int h, int nb_args, ...)
{
	Area.setx(x);
	Area.sety(y);
	Area.setw(w);
	Area.seth(h);

	//arguments list (argument pointer)
	va_list args;
	//open the list
    va_start(args, nb_args);

    //parse arguments list until num has been reached (ie nb of args)
    for (int i=0; i < nb_args; i++)
	{
		//push generation allowed type monster inside the vector (arguments are int type)
		Allowed_Monsters.push_back( va_arg(args, int) );
	}

	//close the list
	va_end(args);
}
BattleField_Zone::~BattleField_Zone()
{
}
std::vector<BattleField_Zone*> BattleField_Zone::Fill_Vector()
{
	std::vector<BattleField_Zone*> BattleField_Zone_Vector;
	
	//Areas
	BattleField_Zone* myArea;
	
	myArea = new BattleField_Zone(0, 0, 640, 640, 1, Humanoid);
	BattleField_Zone_Vector.push_back(myArea);

	myArea = new BattleField_Zone(640, 0, 640, 640, 0);
	BattleField_Zone_Vector.push_back(myArea);

	myArea = new BattleField_Zone(0, 640, 640, 640, 2, Humanoid, Worm);
	BattleField_Zone_Vector.push_back(myArea);

	myArea = new BattleField_Zone(640, 640, 640, 640, 1, Worm);
	BattleField_Zone_Vector.push_back(myArea);

	return BattleField_Zone_Vector;
}

//BackGround Constructor
BackGround::BackGround()
{
	//Create tileset surface
	BackGround_Tileset_Grass = RGBSurface("data/Grass.png", Color(0xFF, 0xFF, 0xFF));
	BackGround_Tileset_Sands = RGBSurface("data/Sand Tileset.png", Color(0x00, 0x00, 0x00));
	BackGround_Tileset_Rivers = RGBSurface("data/Water.png", Color(0xFF, 0xFF, 0xFF));
	BackGround_Tileset_Lakes = RGBSurface("data/Water.png", Color(0xFF, 0xFF, 0xFF));

	//The default clip (minimal clip)
	BackGround_Clip.setx(0);
	BackGround_Clip.sety(0);
	BackGround_Clip.setw(0);
	BackGround_Clip.seth(0);

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
			//The empty clip (we wont blit anything in this case)
			BackGround_Clip.setx(0);
			BackGround_Clip.sety(0);
			BackGround_Clip.setw(0);
			BackGround_Clip.seth(0);
		}
		else if( Current_Ground_Type == GRASS_GROUND )
		{
			//Grass Clip
			BackGround_Clip.setx(0);
			BackGround_Clip.sety(0);
			BackGround_Clip.setw(BATF_SPRITE_W);
			BackGround_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Ground_Type == SAND_GROUND )
		{
			//Sand clip (random sand from the tileset)
			BackGround_Clip.setx(BATF_SPRITE_W * random(0,4));
			BackGround_Clip.sety(BATF_SPRITE_H * random(0,1));
			BackGround_Clip.setw(BATF_SPRITE_W);
			BackGround_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Ground_Type == RIVER_GROUND )
		{
			//River clip
			BackGround_Clip.setx(0);
			BackGround_Clip.sety(0);
			BackGround_Clip.setw(BATF_SPRITE_W);
			BackGround_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Ground_Type == LAKE_GROUND )
		{
			//Lake clip
			BackGround_Clip.setx(0);
			BackGround_Clip.sety(0);
			BackGround_Clip.setw(BATF_SPRITE_W);
			BackGround_Clip.seth(BATF_SPRITE_H);
		}
		else // not listed type (??)
		{
			P0_Logger << " Ground type present inside BackGround_Map.txt not recognized !!?? " << std::endl;
			Current_Ground_Type = EMPTY_GROUND; //set the ground type to empty in order to not crash
		
			//Use default clip from the default tileset, the empty clip
			BackGround_Clip.setx(0);
			BackGround_Clip.sety(0);
			BackGround_Clip.setw(0);
			BackGround_Clip.seth(0);
		}

		//Create Monster & initialized it
		BattleField_Sprite* TheBackGround_Sprite = new BattleField_Sprite(x, y, Current_Ground_Type, BackGround_Clip);

		//store the monster at the end of the vector
		myBackGround_Sprite_Vector.push_back(TheBackGround_Sprite);

		//Move to next position
        x += BATF_SPRITE_W;
        
        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;
            
            //Move to the next line
            y += BATF_SPRITE_H;    
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
		//Check if the BackGround sprite is present on the screen (in fact screen + character sprite dim)
		if ( ((Camera.getx()-CH_WIDTH) <= BackGround_Sprite_Vector[i]->Get_X()) && ( BackGround_Sprite_Vector[i]->Get_X() < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= BackGround_Sprite_Vector[i]->Get_Y()) && ( BackGround_Sprite_Vector[i]->Get_Y() < (Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
		{
			//To minimize vector access
			int Current_Ground_Type = BackGround_Sprite_Vector[i]->Get_BattleField_Type();

			//It's present select the good tileset according to the terrain type
			if ( Current_Ground_Type == EMPTY_GROUND )
			{
				//Don't draw anything
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
			else if( Current_Ground_Type == LAKE_GROUND )
			{
				//Draw the BackGround River sprite 
				if (! Screen.blit( BackGround_Tileset_Lakes, Point::Point( BackGround_Sprite_Vector[i]->Get_X() - Camera.getx(), BackGround_Sprite_Vector[i]->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Lake Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else // not listed type(!!??) : impossible because the vector was created with BackGround::BackGround_Vector()
			{
				P0_Logger << " Ground type present inside BackGround_Sprite_Vector not recognized !!?? X: " << BackGround_Sprite_Vector[i]->Get_X() << " Y: " << BackGround_Sprite_Vector[i]->Get_Y() << std::endl;
				
				//Don't draw anything
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );

	//P0_Logger << " Background Generation : OK " << std::endl;
	return true;
}


//Environment Constructor
Environment::Environment()
{
	//Create tileset surface
	Environment_Tileset_Trees = RGBSurface("data/Trees Tileset.png", Color(0x73, 0x6D, 0xB5));
	Environment_Tileset_Rocks = RGBSurface("data/Rock.png", Color(0xFF, 0xFF, 0xFF));
	Environment_Tileset_Walls = RGBSurface("data/Wall.png", Color(0xFF, 0xFF, 0xFF));
	Environment_Tileset_Houses = RGBSurface("data/Houses Tileset.png", Color(0xBF, 0x7B, 0xC7));
	Environment_Tileset_Bridges = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));

	//The default clip is the minimal clip (we don't want to blit something in this case so it dont really matter)
	Environment_Clip.setx(0);
	Environment_Clip.sety(0);
	Environment_Clip.setw(0);
	Environment_Clip.seth(0);

	P0_Logger << " Environment Construction : OK " << std::endl;
}
//Environment Destructor
Environment::~Environment()
{
}
//Environment interpretation from the file
std::vector<BattleField_Sprite*> Environment::Environment_Vector()
{
	//The tile offset
    int x=0, y=0;

	//The type of Ground that must be generated, by default empty
	int Current_Env_Item_Type = NOTHING_ENV_ITEM;
    
    //Open the map
    std::ifstream Environment_Map("data/Environment_Map.txt");

	//check if map has been loaded succesfully
    if(! Environment_Map )
    {
		P0_Logger << " Can't open Environment_Map.txt " << std::endl;
		Timer::delay(3000);
		exit(0);
    }

	while(!Environment_Map.eof())
	{
		//Read Ground type from map file
		Environment_Map >> Current_Env_Item_Type;

		//if the map file has a bug in it
		if( Environment_Map.fail() == true )
		{
			P0_Logger << " Environment_Map.txt corrupted " << std::endl;
			break;
			//exit(0);
		}

		//assign the good clip relative to the type read from the map file
		if( Current_Env_Item_Type == NOTHING_ENV_ITEM )
		{
			//Minimal clip (we won't blit something in this case so it dont really matter)
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(0);
			Environment_Clip.seth(0);
		}
		else if( Current_Env_Item_Type == TREE_ENV_ITEM )
		{
			//Tree Clip (random tree the tileset)
			Environment_Clip.setx(BATF_SPRITE_W * random(0,3));
			Environment_Clip.sety(BATF_SPRITE_H * random(0,7));
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == ROCK_ENV_ITEM )
		{
			//Rock Clip
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == WALL_ENV_ITEM )
		{
			//Wall Clip
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == HOUSE_ENV_ITEM )
		{
			//House Clip(random from the tileset)
			Environment_Clip.setx(BATF_SPRITE_W * random(0,5));
			Environment_Clip.sety(BATF_SPRITE_H * random(0,2));
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == BRIDGE_ENV_ITEM )
		{
			//Bridge Clip
			Environment_Clip.setx(297);
			Environment_Clip.sety(231);
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else // not listed type (??)
		{
			P0_Logger << " Environment item present inside Environment_Map.txt not recognized " << std::endl;
			Current_Env_Item_Type = NOTHING_ENV_ITEM; //set the environment type to nothing in order to not crash
		
			//Minimal clip (we won't blit something in this case so it dont really matter)
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(0);
			Environment_Clip.seth(0);
		}

		//Create Monster & initialized it
		BattleField_Sprite* TheEnvironment_Sprite = new BattleField_Sprite(x, y, Current_Env_Item_Type, Environment_Clip);

		//store the monster at the end of the vector
		myEnvironment_Sprite_Vector.push_back(TheEnvironment_Sprite);

		//Move to next position
        x += BATF_SPRITE_W;
        
        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;
            
            //Move to the next line
            y += BATF_SPRITE_H;    
        }
	}

	//Close the Environment map file
	Environment_Map.close();

	P0_Logger << " Environment Sprite Vector Creation : OK " << std::endl;

	return(myEnvironment_Sprite_Vector);
}
//Environment Render
bool Environment::Render(std::vector<BattleField_Sprite*> Environment_Sprite_Vector, Rect Camera, VideoSurface & Screen)
{
	//Loop on all the vector
	for(int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		//Check if the Environment sprite is present on the screen (in fact screen + character's sprite dim)
		if ( ((Camera.getx()-CH_WIDTH) <= Environment_Sprite_Vector[i]->Get_X()) && ( Environment_Sprite_Vector[i]->Get_X() < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= Environment_Sprite_Vector[i]->Get_Y()) && ( Environment_Sprite_Vector[i]->Get_Y() < (Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
		{
			//To minimize vector access
			int Current_Env_Item_Type = Environment_Sprite_Vector[i]->Get_BattleField_Type();

			//It's present, then select the good tileset according to the environment item type
			if ( Current_Env_Item_Type == NOTHING_ENV_ITEM )
			{
				//Don't blit anything
			}
			else if( Current_Env_Item_Type == TREE_ENV_ITEM )
			{
				//Draw the Environment Tree sprite 
				if (! Screen.blit( Environment_Tileset_Trees, Point::Point( Environment_Sprite_Vector[i]->Get_X() - Camera.getx(), Environment_Sprite_Vector[i]->Get_Y() - Camera.gety() ), Environment_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Tree Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Env_Item_Type == ROCK_ENV_ITEM )
			{
				//Draw the Environment Rock sprite 
				if (! Screen.blit( Environment_Tileset_Rocks, Point::Point( Environment_Sprite_Vector[i]->Get_X() - Camera.getx(), Environment_Sprite_Vector[i]->Get_Y() - Camera.gety() ), Environment_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Rock Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Env_Item_Type == WALL_ENV_ITEM )
			{
				//Draw the Environment Wall sprite 
				if (! Screen.blit( Environment_Tileset_Walls, Point::Point( Environment_Sprite_Vector[i]->Get_X() - Camera.getx(), Environment_Sprite_Vector[i]->Get_Y() - Camera.gety() ), Environment_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Wall Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Env_Item_Type == HOUSE_ENV_ITEM )
			{
				//Draw the Environment Wall sprite 
				if (! Screen.blit( Environment_Tileset_Houses, Point::Point( Environment_Sprite_Vector[i]->Get_X() - Camera.getx(), Environment_Sprite_Vector[i]->Get_Y() - Camera.gety() ), Environment_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Wall Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else if( Current_Env_Item_Type == BRIDGE_ENV_ITEM )
			{
				//Draw the Environment Bridge sprite 
				if (! Screen.blit( Environment_Tileset_Bridges, Point::Point( Environment_Sprite_Vector[i]->Get_X() - Camera.getx(), Environment_Sprite_Vector[i]->Get_Y() - Camera.gety() ), Environment_Sprite_Vector[i]->Get_BattleField_Clip() ) )
				{
					P0_Logger << " Wall Sprite Generation Failed " << GetError() << std::endl;
				}
			}
			else // not listed type(!!??) : impossible because the vector was created with Environment::Environment_Vector()
			{
				P0_Logger << " Environnement item type present inside Environment_Sprite_Vector not recognized !!?? X: " << Environment_Sprite_Vector[i]->Get_X() << " Y: " << Environment_Sprite_Vector[i]->Get_Y() << std::endl;
				
				//Don't blit anything
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );

	//P0_Logger << " Environment Generation : OK " << std::endl;*/
	return true;
}
