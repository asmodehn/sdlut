#include "PathFinder.hh"

PathFinder::PathFinder()
{
	Grid_Size = Point();
};

PathFinder::PathFinder(const Point& Grid_Size)
{
	this->Grid_Size = Grid_Size;
};

PathFinder::~PathFinder() {};

float PathFinder::Diagonal_Distance(int x1, int y1, int x2, int y2)
{
    int diagonal_cost = min( abs(x1-x2), abs(y1-y2) );
	int straight_cost = abs(x1-x2) + abs(y1-y2);
	return (sqrt(2.f) * diagonal_cost) + straight_cost - (2*diagonal_cost);
}


//Add All Available Adjacents To Node n To the Open_List
void PathFinder::Add_Available_Adjacents_To_Open_List(pair <int,int>& n)
{
    Node tmp;

    //check all adjacents
	for (int i=n.first-Grid_Size.getx(); i<=n.first+Grid_Size.getx(); i+=Grid_Size.getx()){
		for (int j=n.second-Grid_Size.gety(); j<=n.second+Grid_Size.gety(); j+=Grid_Size.gety()){
            //
			//todo check if terrain allow node
			//
			if ((i==n.first) && (j==n.second))  //we dont want to check with ourself
                continue;

			//we move on top of a grid
			pair<int,int> it( i, j );

            if (!Already_Present_In_List(it, Closed_List)){
                /* le noeud n'est pas déjà présent dans la Closed_List */

                tmp.cout_g = Closed_List[n].cout_g + Diagonal_Distance( i, j, n.first, n.second );
				tmp.cout_h = Diagonal_Distance( i, j, Destination.getx(), Destination.gety() );
				//need a tie breaker here of 1/1000? -> http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S12
                tmp.cout_f = tmp.cout_g + tmp.cout_h;
                tmp.parent = n;

                if (Already_Present_In_List(it, Open_List)){
                    /* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
                    if (tmp.cout_f < Open_List[it].cout_f){
                        /* si le nouveau chemin est meilleur, on update */
                        Open_List[it]=tmp;
                    }

                    /* le noeud courant a un moins bon chemin, on ne change rien */


                }else{
                    /* le noeud n'est pas présent dans la liste ouverte, on l'ajoute */
                    Open_List[pair<int,int>(i,j)]=tmp;
                }
            }
        }
    }
}

bool PathFinder::Already_Present_In_List(pair<int,int> n, Node_List& node_list)
{
    Node_List::iterator i = node_list.find(n);
    if (i==node_list.end())
        return false; //not present
    else
        return true;
}

/*
    fonction qui renvoie la clé du meilleur noeud de la liste
*/
pair<int,int> PathFinder::Best_Node( Node_List& node_list )
{
    float BestNode_Cost = node_list.begin()->second.cout_f;
    pair<int,int> BestNode_Key = node_list.begin()->first;

    for ( Node_List::iterator i = node_list.begin(); i!=node_list.end(); i++ )
	{
        if ( i->second.cout_f < BestNode_Cost )
		{
            BestNode_Cost = i->second.cout_f;
            BestNode_Key = i->first;
        }
	}

    return BestNode_Key;
}

/*
    fonction qui passe l'élément p de la liste ouverte dans la fermée
*/
void PathFinder::Add_To_Closed_List(pair<int,int>& p)
{
    Node& n = Open_List[p];
    Closed_List[p]=n;

    // il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable
    if (Open_List.erase(p)==0)
        cerr << "n'apparait pas dans la liste ouverte, impossible à supprimer" << endl;
    return;
}

void PathFinder::Set_Path()
{
    // l'arrivée est le dernier élément de la liste fermée.
	Node_List::iterator i = Closed_List.end();
    i--;

    Node& tmp = i->second;

    Point n;
    pair<int,int> previous;
    n.setx( Destination.getx() );
    n.sety( Destination.gety() );
    previous.first  = tmp.parent.first;
    previous.second = tmp.parent.second;
    Path.push_front(n);

	//until we reached the origin
    while ( previous != nOrigin.parent )
	{
        n.setx( previous.first );
        n.sety( previous.second );
        Path.push_front(n);

        tmp = Closed_List[tmp.parent];
        previous.first  = tmp.parent.first;
        previous.second = tmp.parent.second;
    }
}

list<Point> PathFinder::Get_Path(const Point& Origin, const Point& Destination)
{
	//initial Node
	nOrigin.cout_g = 0;
	nOrigin.cout_h = Diagonal_Distance( Origin.getx(), Origin.gety(), Destination.getx(), Destination.gety() );
    nOrigin.cout_f = nOrigin.cout_g + nOrigin.cout_h;
    nOrigin.parent.first  = Origin.getx();
    nOrigin.parent.second = Origin.gety();

	this->Destination = Destination;

    pair <int,int> Current;

    /* déroulement de l'algo A* */

    Current.first  = Origin.getx();
    Current.second = Origin.gety();
    // ajout de courant dans la liste ouverte

    Open_List[Current]=nOrigin;
    Add_To_Closed_List(Current);
    Add_Available_Adjacents_To_Open_List(Current);


    while( !( (Current.first == Destination.getx()) && (Current.second == Destination.gety() ) )
            &&
           !Open_List.empty()
         )
	{

        // on cherche le meilleur noeud de la liste ouverte, on sait qu'elle n'est pas vide donc il existe
        Current = Best_Node(Open_List);

        // on le passe dans la liste fermee, il ne peut pas déjà y être
        Add_To_Closed_List(Current);

        Add_Available_Adjacents_To_Open_List(Current);
    }

	//if a path has been founded
    if ( (Current.first == Destination.getx()) && (Current.second == Destination.gety()) )
	{
        Set_Path();
    }

	//
	//todo: set this to NULL or something similar at initialization
	//
	return Path;
}