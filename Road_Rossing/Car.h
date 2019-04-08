#pragma once
#include "NPC.h"
class Car : public NPC
{
public:
	Car() = default;
	Car(const int &x,const int &y,const int &move);
	void Display() const;
	void Remove() const;
	void Move(const int &level);
	bool Impact(const int &x, const int &y) const;
};

