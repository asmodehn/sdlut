#ifndef PathFinder_HH
#define PathFinder_HH

#include "Config.hh"

//PathFinder Class
class PathFinder
{
	//friend class ;

private:

	//used to know the grid size
	Point Grid_Size;

	struct Node{
		float cout_g, cout_h, cout_f;
		std::pair<int,int> parent;    // 'adresse' du parent (qui sera toujours dans la map fermée
	};

	typedef map< pair<int,int>, Node> Node_List;


	Node_List Open_List;
	Node_List Closed_List;
	list<Point> Path;

	Point Destination;
	Node nOrigin;

	//methods
	float Diagonal_Distance(int x1, int y1, int x2, int y2);
	void Add_Available_Adjacents_To_Open_List( pair <int,int>& n );
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

	//Find the best path between to Points
	list<Point> Get_Path(const Point& Origin, const Point& Destination);


};

#endif
