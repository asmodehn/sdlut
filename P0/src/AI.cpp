#include "AI.hh"

AI::AI()
{
}

AI::~AI()
{
}


Point AI::Choose_Destination(const Point& Origin, const int& Sight_Range, const Point& Grid_Size)
{
	Point Dest;
	
	//todo : check 1st if there is a destination inside defined list using Pick_Best_Destination_From_List()
	//else do that
	Dest = Find_Random_Destination(Origin, Sight_Range);

	//round the destination
	Round_Destination(Origin, Dest, Grid_Size);

	return Dest;
}

Point AI::Find_Random_Destination(const Point& Origin, const int& Sight_Range)
{
	Point Destination;
	//Set coord inside the sight range and inside the level
	Destination.setx( random( max(Origin.getx() - Sight_Range, 0), min(Origin.getx() + Sight_Range, LEVEL_WIDTH) ) );
	Destination.sety( random( max(Origin.gety() - Sight_Range, 0), min(Origin.gety() + Sight_Range, LEVEL_HEIGHT) ) );

	//As the sight range is a circle we must check if the distance is inside the sight range
	while ( (float)Sight_Range < sqrt( (float)( ( Origin.getx()-Destination.getx() )*( Origin.getx()-Destination.getx() ) + ( Origin.gety()-Destination.gety() )*( Origin.gety()-Destination.gety() ) ) ) )
	{//we'r not inside the sight range, we must retry
		Destination.setx( random( max(Origin.getx() - Sight_Range, 0), min(Origin.getx() + Sight_Range, LEVEL_WIDTH) ) );
		Destination.sety( random( max(Origin.gety() - Sight_Range, 0), min(Origin.gety() + Sight_Range, LEVEL_HEIGHT) ) );
	}

	return Destination;

}

Point AI::Pick_Best_Destination_From_List()
{
	//todo
	return Point();
}

//Method which round the destination to the best position on the grid defined by the grid size
void AI::Round_Destination(const Point& Origin, Point& Destination, const Point& Grid_Size)
{
	//Modifiers that tell us the difference between the Origin and the grid size
	int modifier_x = Origin.getx() - ( (Origin.getx()/Grid_Size.getx()) * Grid_Size.getx() );
	int modifier_y = Origin.gety() - ( (Origin.gety()/Grid_Size.gety()) * Grid_Size.gety() );

	//we round to the E%Grid_Size_Width than shift by the modifier_x
	Destination.setx( ( (Destination.getx()/Grid_Size.getx()) * Grid_Size.getx() ) + modifier_x);
	//in case we go to far we moved back from on grid square
	if ( Destination.getx() > LEVEL_WIDTH )
		Destination.setx(Destination.getx() - Grid_Size.getx());

	//we round to the E%Grid_Size_Heigt than shift by the modifier_y
	Destination.sety( ( (Destination.gety()/Grid_Size.gety()) * Grid_Size.gety() ) + modifier_y);
	//in case we go to far we moved back from on grid square
	if ( Destination.gety() > LEVEL_HEIGHT )
		Destination.sety(Destination.gety() - Grid_Size.gety());
}
