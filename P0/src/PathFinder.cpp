#include "PathFinder.hh"

PathFinder::PathFinder()
{
	Grid_Size = Point();
	Path.clear();
};

PathFinder::PathFinder(const Point& Grid_Size)
{
	this->Grid_Size = Grid_Size;
	Path.clear();
};

PathFinder::~PathFinder()
{
};

//Return the diagonal distance between two Point using a diagonal cost to go at the same speed in diagonals than in horizontals/verticals
float PathFinder::Diagonal_Distance(const Point& _A, const Point& _B)
{
    int diagonal_cost = min( abs(_A.getx() - _B.getx()), abs(_A.gety() - _B.gety()) );
	int straight_cost = abs(_A.getx() - _B.getx()) + abs(_A.gety() - _B.gety());
	return (sqrt((float)2) * diagonal_cost) + straight_cost - (2*diagonal_cost);
}

//Return the Euclidian distance between 2 Point (Warning does not take care of the diagonal movement cost !!)
float PathFinder::Euclidian_Distance(const Point& _A, const Point& _B)
{
	return sqrt( (float)( (_A.getx() - _B.getx())*(_A.getx() - _B.getx()) + (_A.gety() - _B.gety())*(_A.gety() - _B.gety()) ) );
}

//Add All Available Adjacents To Node n To the Open_List
void PathFinder::Add_Available_Adjacents_To_Open_List(pair <int,int>& n, Character_Base* Character_Instance, std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector )
{
try {
    Node tmp;

    //check all adjacents
	for (int i=n.first-Grid_Size.getx(); i<=n.first+Grid_Size.getx(); i+=Grid_Size.getx()){
		for (int j=n.second-Grid_Size.gety(); j<=n.second+Grid_Size.gety(); j+=Grid_Size.gety()){
            
			//we dont want to check with ourself
			if ((i==n.first) && (j==n.second))  
                continue;

			//if terrain don't allow node
			if ( !Character_Instance->Manage_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector, false) )
				continue;

			//we move on top of a grid
			pair<int,int> it( i, j );

			//Node not presents in Closed_List
            if ( !Already_Present_In_List(it, Closed_List) )
			{
				//cost from the parent + cost from the current Point to the Parent
                tmp.cost_g = Closed_List[n].cost_g + Diagonal_Distance( Point(i, j) , Point(n.first, n.second) );

				//cost from the current Point to the Destination
				tmp.cost_h = Diagonal_Distance( Point(i, j), Destination );

				//need a tie breaker here of 1/1000??? -> http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S12
                
				//sum
				tmp.cost_f = tmp.cost_g + tmp.cost_h;

				//Set parent
                tmp.parent = n;

				//Check if node is already in Open_List
                if (Already_Present_In_List(it, Open_List))
				{
                    //Node already presents in Open_List, we must check costs
                    if (tmp.cost_f < Open_List[it].cost_f){
                        //better or same cost, than update his cost (if the cost is the same we should also update it coz we update the parent !)
                        Open_List[it]=tmp;
                    }
                    //worse cost, don't change anything

                }
				else
				{
                    //Node not presents in Open_List, we must add it
                    Open_List[pair<int,int>(i,j)]=tmp;
                }

				//if we have reached the destination, no need to work more
				if (tmp.cost_h == 0) 
					return;

            } //if ( !Already_Present_In_List(it, Closed_List) )
        } //for on x
    } //for on y

} catch (std::exception &exc) {
	throw std::logic_error( "PathFinder::Add_Available_Adjacents_To_Open_List(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In PathFinder::Add_Available_Adjacents_To_Open_List()");  
}
}

//tell if a node his present in a given node list
bool PathFinder::Already_Present_In_List(pair<int,int> n, Node_List& node_list)
{
try {

    Node_List::iterator i = node_list.find(n);
    if (i==node_list.end())
        return false; //not present
    else
        return true;

} catch (std::exception &exc) {
	throw std::logic_error( "PathFinder::Already_Present_In_List(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In PathFinder::Already_Present_In_List()");  
}
}

//return the key of the best node af a node list
pair<int,int> PathFinder::Best_Node( Node_List& node_list )
{
try {
	//Set the BestNode_Cost to the 1st one
    float BestNode_Cost = node_list.begin()->second.cost_f;
    pair<int,int> BestNode_Key = node_list.begin()->first;

	//loop on all the list to find the best cost_f
    for ( Node_List::iterator i = node_list.begin(); i!=node_list.end(); i++ )
	{
		//if the cost is better we set BestNode_Cost to this cost and the key to this node
        if ( i->second.cost_f < BestNode_Cost )
		{
            BestNode_Cost = i->second.cost_f;
            BestNode_Key = i->first;
        }
		//When the BestNode_Cost is the same as the current cost_f we should look for the best cost_g
		else if ( i->second.cost_f == BestNode_Cost )
		{
			//the current node has a best cost_h than the current best node so the current node is better
			if (i->second.cost_h < node_list[BestNode_Key].cost_h)
				BestNode_Key = i->first;
		}
	}

    return BestNode_Key;

} catch (std::exception &exc) {
	throw std::logic_error( "PathFinder::Best_Node(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In PathFinder::Best_Node()");  
}
}

//move the element from the open list to the closed list
void PathFinder::Add_To_Closed_List(pair<int,int>& p)
{
try {
    Node& n = Open_List[p];
    Closed_List[p]=n;

    //erase it from Open_List
    if (Open_List.erase(p)==0)
        cerr << "Not present in Open_List !!! Can't Erase It !" << endl;
    return;

} catch (std::exception &exc) {
	throw std::logic_error( "PathFinder::Add_To_Closed_List(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In PathFinder::Add_To_Closed_List()");  
}
}

//Transform the Closed_List in the Path from the Origin (without containing it) to the Destination
void PathFinder::Set_Path()
{
try {
	//Designed to contain the parent coords
	pair<int,int> previous;

	//At the begining the parent is the destination
	previous.first  = Destination.getx();
    previous.second = Destination.gety();

	//Add the Destination to the Path (nb: we're sure this won't crash coz we only called this method after that the Destination has been added to the Closed_List)
	Path.push_front( Destination );
		
	//Set the tmp node as the Destination
	Node& tmp = Closed_List[previous];

	//Get the parent node of the destination
    previous.first  = tmp.parent.first;
    previous.second = tmp.parent.second;

	//Loop until we reached the Origin
    while ( previous != nOrigin.parent )
	{
		//if the parent is not the Origin we add it to the Path
        Path.push_front( Point( previous.first, previous.second) );

		//get the parent node of the current parent
        tmp = Closed_List[tmp.parent];
        previous.first  = tmp.parent.first;
        previous.second = tmp.parent.second;
    }

} catch (std::exception &exc) {
	throw std::logic_error( "PathFinder::Set_Path(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In PathFinder::Set_Path()");  
}
}

//Return the best Path between two Point (if Path.size() == 0, Path not found)
list<Point> PathFinder::Get_Path(const Point& Origin, const Point& Destination, Character_Base* Character_Instance, std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector )
{
try {
	this->Destination = Destination;

	//initial Node
	nOrigin.cost_g = 0;
	nOrigin.cost_h = Diagonal_Distance( Origin, Destination );
    nOrigin.cost_f = nOrigin.cost_h;
    nOrigin.parent.first  = Origin.getx();
    nOrigin.parent.second = Origin.gety();

    pair <int,int> Current;

    Current.first  = Origin.getx();
    Current.second = Origin.gety();

	//Add the Origin to the closed list & his adjacent to the Open_List
    Open_List[Current]=nOrigin;
    Add_To_Closed_List(Current);
    Add_Available_Adjacents_To_Open_List(Current, Character_Instance, Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );

	//loop until destination reached or Open_List empty
    while( !( (Current.first == Destination.getx()) && (Current.second == Destination.gety() ) )
            &&
           !Open_List.empty()
         )
	{

        //We look for the best node in the Open_List (we've checked Open_List is not empty so there won't be an error)
        Current = Best_Node(Open_List);

        //We add it to the Closed_List, it can't be already there
        Add_To_Closed_List(Current);

		//we've found the destination, we can set the PAth. Also there is no need to check adjacents anymore so we can leave the loop
		if ( (Current.first == Destination.getx()) && (Current.second == Destination.gety()) )
		{
			Set_Path();
			break;
		}

		//we add all his adjacent to the Open_List to check them
        Add_Available_Adjacents_To_Open_List(Current, Character_Instance, Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );
    }

	return Path;

} catch (std::exception &exc) {
	Path.clear();
	throw std::logic_error( "PathFinder::Get_Path(), " + (string)exc.what() );
} catch (...) {
	Path.clear();
	throw std::logic_error("Unhandled Error In PathFinder::Get_Path()");  
}
}