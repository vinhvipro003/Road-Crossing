#pragma once
#include "NPC.h"
class Truck:public NPC
{
public:
	Truck() = default;
	Truck(const int &x,const int &y,const int &move);
	void Display() const;
	void Remove() const;
	void Move(const int &level);
	bool Impact(const int &x, const int &y) const;
};

