#ifndef PathFinder_HH
#define PathFinder_HH

#include "Config.hh"
#include "BattleField.hh"

class Character_Base; //fwd def: to be able to instantiate

//PathFinder Class
class PathFinder
{
	//friend class ...;

private:

	//Used to know the grid size
	Point Grid_Size;

	struct Node{
		float cost_g, cost_h, cost_f;
		std::pair<int,int> parent;    // parent's coordinates who always be in the Closed_List
	};

	typedef map< pair<int,int>, Node> Node_List;


	Node_List Open_List;
	Node_List Closed_List;
	list<Point> Path;

	Point Destination;
	Node nOrigin;

//Methods
	float Diagonal_Distance(const Point& A, const Point& B);
	//Return the Euclidian distance between 2 Point (Warning does not take care of the diagonal movement cost !!)
	float Euclidian_Distance(const Point& A, const Point& B);
	//Add All Available Adjacents To Node n To the Open_List
	void Add_Available_Adjacents_To_Open_List( pair <int,int>& n, Character_Base* Character_Instance, std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector );
	void Add_To_Closed_List( pair<int,int>& p );
	bool Already_Present_In_List( pair<int,int> n, Node_List& node_list );
	pair<int,int> Best_Node( Node_List& node_list );
	void Set_Path();


	
protected:

public:
	//definition
	PathFinder();
	PathFinder(const Point& Grid_Size);
	~PathFinder();

	//Find the best path between to Point: Origin & Destination
	list<Point> Get_Path(const Point& Origin, const Point& Destination, Character_Base* Character_Instance, std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector );


};

#endif
