#include "NPC.h"
#include <sstream>
string NPC::ToString()
{
	stringstream st;
	st << _x << " " << _y << " " << _move;
	return st.str();
}