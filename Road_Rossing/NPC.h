#pragma once
#include "Console.h"
class NPC
{
public:
public:
	NPC() = default;
	NPC(const int &x, const int &y,const int  &move):_x(x), _y(y),_move(move), _color(rand()%15+1){}
	virtual void Display() const = 0;
	virtual void Remove() const = 0;
	virtual void Move(const int &level)
	{
		Sleep(10 - level);
	}
	virtual bool Impact(const int &x, const int &y) const = 0;
	string ToString();
protected:
	int _x, _y;
	int _color;
	int _move;
};

