/*!
 * Description: This is designed to contain everything linked to AI stuff
 * It will be simple at first.
 * 
 * Author: XorfacX <xorfacx@gmail.com>
 *
 * Creation: 18/05/2007
 *
 * Copyright: See licence for info
 */

#ifndef AI_HH
#define AI_HH

#include "Config.hh"

//PathFinder Class
class AI
{
	//friend class ;

private:
	AI();
	~AI();

	//Method called by Choose_Destination() which pick a destination from an available list
	static Point Pick_Best_Destination_From_List();
	//Method called by Choose_Destination() which pick a random destination inside character sight range
	static Point Find_Random_Destination(const Point& Origin, const int& Sight_Range);
	//Method which round the destination to the best position on the grid defined by the grid size
	static void Round_Destination(const Point& Origin, Point& Destination, const Point& Grid_Size);

protected:

public:
	//This method is designed to choose a destination randomly between available destinations a character have or simply randomly inside the character's sight range using the grid size defined by the characters dimensions
	static Point Choose_Destination(const Point& Origin, const int& Sight_Range, const Point& Grid_Size);
};

#endif
