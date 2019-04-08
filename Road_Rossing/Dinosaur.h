#include "NPC.h"
#pragma once
class Dinosaur:public NPC
{
public:
	Dinosaur() = default;
	Dinosaur(const int &x,const int &y,const int &move);
	void Display() const;
	void Remove() const;
	void Move(const int &level);
	bool Impact(const int &x, const int &y) const;
};

