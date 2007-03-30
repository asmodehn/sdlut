#include "BattleField.hh"

BattleField_Sprite::BattleField_Sprite()
{
	X = 0;
	Y = 0;

	//Default Ground type
	BattleField_Type = EMPTY_GROUND;
}
BattleField_Sprite::BattleField_Sprite(int x, int y, int battlefield_type, Rect battlefield_clip)
{
	X = x;
	Y = y;
	BattleField_Type = battlefield_type;
	BattleField_Clip = battlefield_clip;
}


BattleField_Zone::BattleField_Zone()
{
	Allowed_Monsters = new std::vector<int>;
}

BattleField_Zone::~BattleField_Zone()
{
	delete Allowed_Monsters, Allowed_Monsters = NULL;
}
BattleField_Zone::BattleField_Zone(int x, int y, int w, int h, int nb_args, ...)
{
	Area.setx(x);
	Area.sety(y);
	Area.setw(w);
	Area.seth(h);
	Allowed_Monsters = new std::vector<int>;

	//arguments list (argument pointer)
	va_list args;
	//open the list
    va_start(args, nb_args);

    //parse arguments list until num has been reached (ie nb of args)
    for (signed int i=0; i < nb_args; i++)
	{
		//push generation allowed type monster inside the vector (arguments are int type)
		Allowed_Monsters->push_back( va_arg(args, int) );
	}

	//close the list
	va_end(args);
}
std::vector<BattleField_Zone*>* BattleField_Zone::Fill_Vector()
{
	std::vector<BattleField_Zone*>* BattleField_Zone_Vector = new std::vector<BattleField_Zone*>;
	
	//Areas
	BattleField_Zone* myArea;
	
	myArea = new BattleField_Zone(0, 0, 640, 640, 1, Humanoid);
	BattleField_Zone_Vector->push_back(myArea);

	myArea = new BattleField_Zone(640, 0, 640, 640, 0);
	BattleField_Zone_Vector->push_back(myArea);

	myArea = new BattleField_Zone(0, 640, 640, 640, 2, Humanoid, Worm);
	BattleField_Zone_Vector->push_back(myArea);

	myArea = new BattleField_Zone(640, 640, 640, 640, 1, Worm);
	BattleField_Zone_Vector->push_back(myArea);

	return BattleField_Zone_Vector;
}

//BackGround Constructor
BackGround::BackGround()
{
	//Create tileset surface
	BackGround_Tileset_Grass = RGBSurface(GRASS_GROUND_Filename, Color(0xFF, 0xFF, 0xFF));
	BackGround_Tileset_Sands = RGBSurface(SAND_GROUND_Filename, Color(0x00, 0x00, 0x00));
	BackGround_Tileset_Rivers = RGBSurface(RIVER_GROUND_Filename, Color(0xFF, 0xFF, 0xFF));
	BackGround_Tileset_Lakes = RGBSurface(LAKE_GROUND_Filename, Color(0xFF, 0xFF, 0xFF));
	BackGround_Tileset_Bridges = RGBSurface(BRIDGE_GROUND_Filename, Color(0xFF, 0xFF, 0xFF));

	//Initialize vector
	BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;

	P0_Logger << nl << "BackGround Construction : OK " << std::endl;
}
//BackGround Destructor
BackGround::~BackGround()
{
	delete BackGround_Sprite_Vector, BackGround_Sprite_Vector = NULL;
}

//BackGround interpretation from the file
std::vector<BattleField_Sprite*>* BackGround::BackGround_Vector()
{
	//The tile offset
    int x=0, y=0;

	//The type of Ground that must be generated, by default empty
	int Current_Ground_Type = EMPTY_GROUND;
    
    //Open the map
    std::ifstream BackGround_Map("Data/Battlefield/BackGround_Map.txt");

	//check if map has been loaded succesfully
    if(! BackGround_Map )
    {
		//Close the BackGround map file
		BackGround_Map.close();

		//print msg
		P0_Logger << nl << "Can't open BackGround_Map.txt " << std::endl;
		Delay(3000);
		exit(0);
    }

	while(!BackGround_Map.eof())
	{
		//Read Ground type from map file
		BackGround_Map >> Current_Ground_Type;

		//if the map file has a bug in it
		if( BackGround_Map.fail() == true )
		{
			P0_Logger << nl << "BackGround_Map.txt corrupted " << std::endl;
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
		else if( Current_Ground_Type == BRIDGE_GROUND )
		{
			//Bridge Clip
			BackGround_Clip.setx(297);
			BackGround_Clip.sety(231);
			BackGround_Clip.setw(BATF_SPRITE_W);
			BackGround_Clip.seth(BATF_SPRITE_H);
		}
		else // not listed type (??)
		{
			P0_Logger << nl << "Ground type present inside BackGround_Map.txt not recognized !!?? " << std::endl;
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
		BackGround_Sprite_Vector->push_back(TheBackGround_Sprite);

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

	P0_Logger << nl << "BackGround Sprite Vector Creation : OK " << std::endl;

	return(BackGround_Sprite_Vector);
}
//BackGround Render
bool BackGround::Render(Rect Camera, VideoSurface & Screen)
{
try {
	int it_x = 0, it_y = 0;
	if (BackGround_Sprite_Vector->size() > 0)
	{
		//to determine iterator of the top left corner of the camera
		for(int i=0; i < (LEVEL_WIDTH/BATF_SPRITE_W); i++)
		{
			if ( Camera.getx()/BATF_SPRITE_W == (BackGround_Sprite_Vector->at(i)->Get_X())/BATF_SPRITE_W )
			{
				it_x = i;
				break;
			}
		}
		for(unsigned int i=0; i < BackGround_Sprite_Vector->size(); i+=(LEVEL_WIDTH/BATF_SPRITE_W) )
		{
			if ( Camera.gety()/BATF_SPRITE_H == BackGround_Sprite_Vector->at(i)->Get_Y()/BATF_SPRITE_H )
			{
				it_y = i/(LEVEL_WIDTH/BATF_SPRITE_W);
				break;
			}
		}
	
		//P0_Logger << nl << "it_x: " << it_x << "\nit_y: " << it_y << std::endl;
		
		//Loop only on vector elements that are present on the screen
		unsigned int it = 0;
		for(int i = it_y; i < it_y + CURRENT_SCREEN_HEIGHT/BATF_SPRITE_H + 1; i++ )
		{
			for(int j = it_x; j < it_x + (CURRENT_SCREEN_WIDTH/BATF_SPRITE_W) + 1; j++)
			{
				it = i * (LEVEL_WIDTH/BATF_SPRITE_W) + j;
				if (it >= BackGround_Sprite_Vector->size())
					break;
				//Check if the BackGround sprite is present on the screen (in fact screen + character sprite dim)
				//if ( ((Camera.getx()-PC_WIDTH) <= BackGround_Sprite_Vector->at(i)->Get_X()) && ( BackGround_Sprite_Vector->at(i)->Get_X() < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-PC_HEIGHT) <= BackGround_Sprite_Vector->at(i)->Get_Y()) && ( BackGround_Sprite_Vector->at(i)->Get_Y() < (Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
				//{
					//To minimize vector access
					int Current_Bg_Type = BackGround_Sprite_Vector->at(it)->Get_BattleField_Type();

					//It's present, then select the good tileset according to the Background item type
					if ( Current_Bg_Type == EMPTY_GROUND )
					{
						//Don't draw anything
					}
					else if( Current_Bg_Type == GRASS_GROUND )
					{
						//Draw the BackGround grass sprite 
						if (! Screen.blit( BackGround_Tileset_Grass, Point::Point( BackGround_Sprite_Vector->at(it)->Get_X() - Camera.getx(), BackGround_Sprite_Vector->at(it)->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector->at(it)->Get_BattleField_Clip() ) )
							P0_Logger << nl << "Grass Sprite Generation Failed " << GetError() << std::endl;
					}
					else if( Current_Bg_Type == SAND_GROUND )
					{
						//Draw the BackGround Sand sprite 
						if (! Screen.blit( BackGround_Tileset_Sands, Point::Point( BackGround_Sprite_Vector->at(it)->Get_X() - Camera.getx(), BackGround_Sprite_Vector->at(it)->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector->at(it)->Get_BattleField_Clip() ) )
							P0_Logger << nl << "Sand Sprite Generation Failed " << GetError() << std::endl;
					}
					else if( Current_Bg_Type == RIVER_GROUND )
					{
						//Draw the BackGround River sprite 
						if (! Screen.blit( BackGround_Tileset_Rivers, Point::Point( BackGround_Sprite_Vector->at(it)->Get_X() - Camera.getx(), BackGround_Sprite_Vector->at(it)->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector->at(it)->Get_BattleField_Clip() ) )
							P0_Logger << nl << "River Sprite Generation Failed " << GetError() << std::endl;
					}
					else if( Current_Bg_Type == LAKE_GROUND )
					{
						//Draw the BackGround River sprite 
						if (! Screen.blit( BackGround_Tileset_Lakes, Point::Point( BackGround_Sprite_Vector->at(it)->Get_X() - Camera.getx(), BackGround_Sprite_Vector->at(it)->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector->at(it)->Get_BattleField_Clip() ) )
							P0_Logger << nl << "Lake Sprite Generation Failed " << GetError() << std::endl;
					}
					else if( Current_Bg_Type == BRIDGE_GROUND )
					{
						//Draw the BackGround Bridge sprite 
						if (! Screen.blit( BackGround_Tileset_Bridges, Point::Point( BackGround_Sprite_Vector->at(it)->Get_X() - Camera.getx(), BackGround_Sprite_Vector->at(it)->Get_Y() - Camera.gety() ), BackGround_Sprite_Vector->at(it)->Get_BattleField_Clip() ) )
							P0_Logger << nl << "Bridge Sprite Generation Failed " << GetError() << std::endl;
					}
					else // not listed type(!!??) : impossible because the vector was created with Background::Background_Vector()
					{
						P0_Logger << nl << "Ground type present inside BackGround_Sprite_Vector not recognized !!?? X: " << BackGround_Sprite_Vector->at(it)->Get_X() << " Y: " << BackGround_Sprite_Vector->at(it)->Get_Y() << std::endl;
						//Don't draw anything
					}
				//}
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );

	//P0_Logger << nl << "Background Generation : OK " << std::endl;
	return true; //no error
} catch (...) {
    return false; //error occured
}
}


//Environment Constructor
Environment::Environment()
{
	//Create tileset surface
	Environment_Tileset_Trees = RGBSurface(TREE_ENV_Filename, Color(0x73, 0x6D, 0xB5));
	Environment_Tileset_Rocks = RGBSurface(ROCK_ENV_Filename, Color(0xFF, 0xFF, 0xFF));
	Environment_Tileset_Walls = RGBSurface(WALL_ENV_Filename, Color(0xFF, 0xFF, 0xFF));
	Environment_Tileset_Houses = RGBSurface(HOUSE_ENV_Filename, Color(0xBF, 0x7B, 0xC7));

	//Initialize vector
	Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;

	P0_Logger << nl << "Environment Construction : OK " << std::endl;
}
//Environment Destructor
Environment::~Environment()
{
	delete Environment_Sprite_Vector, Environment_Sprite_Vector = NULL;
}

//Environment interpretation from the file
std::vector<BattleField_Sprite*>* Environment::Environment_Vector()
{
	//The tile offset
    int x=0, y=0;

	//The type of Ground that must be generated, by default empty
	int Current_Env_Item_Type = NOTHING_ENV;
    
    //Open the map
    std::ifstream Environment_Map("Data/Battlefield/Environment_Map.txt");

	//check if map has been loaded succesfully
    if(! Environment_Map )
    {
		//Close the Environment map file
		Environment_Map.close();

		//print msg
		P0_Logger << nl << "Can't open Environment_Map.txt " << std::endl;
		Delay(3000);
		exit(0);
    }

	while(!Environment_Map.eof())
	{
		//Read Ground type from map file
		Environment_Map >> Current_Env_Item_Type;

		//if the map file has a bug in it
		if( Environment_Map.fail() == true )
		{
			P0_Logger << nl << "Environment_Map.txt corrupted " << std::endl;
			break;
			//exit(0);
		}

		//assign the good clip relative to the type read from the map file
		if( Current_Env_Item_Type == NOTHING_ENV )
		{
			//Minimal clip (we won't blit something in this case so it dont really matter)
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(0);
			Environment_Clip.seth(0);
		}
		else if( Current_Env_Item_Type == TREE_ENV )
		{
			//Tree Clip (random tree the tileset)
			Environment_Clip.setx(BATF_SPRITE_W * random(0,3));
			Environment_Clip.sety(BATF_SPRITE_H * random(0,7));
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == ROCK_ENV )
		{
			//Rock Clip
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == WALL_ENV )
		{
			//Wall Clip
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else if( Current_Env_Item_Type == HOUSE_ENV )
		{
			//House Clip(random from the tileset)
			Environment_Clip.setx(BATF_SPRITE_W * random(0,5));
			Environment_Clip.sety(BATF_SPRITE_H * random(0,2));
			Environment_Clip.setw(BATF_SPRITE_W);
			Environment_Clip.seth(BATF_SPRITE_H);
		}
		else // not listed type (??)
		{
			P0_Logger << nl << "Environment item present inside Environment_Map.txt not recognized " << std::endl;
			Current_Env_Item_Type = NOTHING_ENV; //set the environment type to nothing in order to not crash
		
			//Minimal clip (we won't blit something in this case so it dont really matter)
			Environment_Clip.setx(0);
			Environment_Clip.sety(0);
			Environment_Clip.setw(0);
			Environment_Clip.seth(0);
		}

		//if env is empty we wont add anything to the vector coz its not usefull
		if ( Current_Env_Item_Type != NOTHING_ENV)
		{
			//Create Monster & initialized it
			BattleField_Sprite* TheEnvironment_Sprite = new BattleField_Sprite(x, y, Current_Env_Item_Type, Environment_Clip);

			//store the monster at the end of the vector
			Environment_Sprite_Vector->push_back(TheEnvironment_Sprite);
		}
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

	P0_Logger << nl << "Environment Sprite Vector Creation : OK " << std::endl;

	return(Environment_Sprite_Vector);
}
//Environment Render
bool Environment::Render(Rect Camera, VideoSurface & Screen)
{
try {
	//Loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector->size(); i++)
	{
		//Check if the Environment sprite is present on the screen (in fact screen + character's sprite dim)
		if ( ((Camera.getx()-PC_WIDTH) <= Environment_Sprite_Vector->at(i)->Get_X()) && ( (signed)Environment_Sprite_Vector->at(i)->Get_X() < (signed)(Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-PC_HEIGHT) <= Environment_Sprite_Vector->at(i)->Get_Y()) && ( (signed)Environment_Sprite_Vector->at(i)->Get_Y() < (signed)(Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
		{	//To minimize vector access
			int Current_Env_Item_Type = Environment_Sprite_Vector->at(i)->Get_BattleField_Type();

			//It's present, then select the good tileset according to the environment item type
			if ( Current_Env_Item_Type == NOTHING_ENV )
			{
				//Don't draw anything
			}
			else if( Current_Env_Item_Type == TREE_ENV )
			{
				//Draw the Environment Tree sprite 
				if (! Screen.blit( Environment_Tileset_Trees, Point::Point( Environment_Sprite_Vector->at(i)->Get_X() - Camera.getx(), Environment_Sprite_Vector->at(i)->Get_Y() - Camera.gety() ), Environment_Sprite_Vector->at(i)->Get_BattleField_Clip() ) )
					P0_Logger << nl << "Tree Sprite Generation Failed " << GetError() << std::endl;
			}
			else if( Current_Env_Item_Type == ROCK_ENV )
			{
				//Draw the Environment Rock sprite 
				if (! Screen.blit( Environment_Tileset_Rocks, Point::Point( Environment_Sprite_Vector->at(i)->Get_X() - Camera.getx(), Environment_Sprite_Vector->at(i)->Get_Y() - Camera.gety() ), Environment_Sprite_Vector->at(i)->Get_BattleField_Clip() ) )
					P0_Logger << nl << "Rock Sprite Generation Failed " << GetError() << std::endl;
			}
			else if( Current_Env_Item_Type == WALL_ENV )
			{
				//Draw the Environment Wall sprite 
				if (! Screen.blit( Environment_Tileset_Walls, Point::Point( Environment_Sprite_Vector->at(i)->Get_X() - Camera.getx(), Environment_Sprite_Vector->at(i)->Get_Y() - Camera.gety() ), Environment_Sprite_Vector->at(i)->Get_BattleField_Clip() ) )
					P0_Logger << nl << "Wall Sprite Generation Failed " << GetError() << std::endl;
			}
			else if( Current_Env_Item_Type == HOUSE_ENV )
			{
				//Draw the Environment Wall sprite 
				if (! Screen.blit( Environment_Tileset_Houses, Point::Point( Environment_Sprite_Vector->at(i)->Get_X() - Camera.getx(), Environment_Sprite_Vector->at(i)->Get_Y() - Camera.gety() ), Environment_Sprite_Vector->at(i)->Get_BattleField_Clip() ) )
					P0_Logger << nl << "Wall Sprite Generation Failed " << GetError() << std::endl;
			}
			else // not listed type(!!??) : impossible because the vector was created with Environment::Environment_Vector()
			{
				P0_Logger << nl << "Environnement item type present inside Environment_Sprite_Vector not recognized !!?? X: " << Environment_Sprite_Vector->at(i)->Get_X() << " Y: " << Environment_Sprite_Vector->at(i)->Get_Y() << std::endl;
				//Don't draw anything
			}
		}
	}
	//Clean the status bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );

	//P0_Logger << nl << "Environment Generation : OK " << std::endl;*/
	return true; //no error
} catch (...) {
    return false; //error occured
}
}
