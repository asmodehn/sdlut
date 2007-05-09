#ifndef Base_HH
#define Base_HH

#include <ctime>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdarg.h> //for methods with an unllimited number of parameters
#include <stdexcept>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include <stdio.h>
#include "libxml/xmlreader.h"

#include "SDL.hh"

using namespace RAGE;
using namespace RAGE::SDL;


//To check colission (small beginning of a physical engine^^)
bool check_collision(const Rect& A, const Rect& B);

//random function
int random(int min, int max);

//Convert Int To String
std::string Int_To_String(const int &to_convert);
//Convert String To Int
int String_To_Int(const std::string &to_convert);

//Style the time to "Xd Xh Xmin Xs"
std::string Time_Style(const int& time);

#endif
