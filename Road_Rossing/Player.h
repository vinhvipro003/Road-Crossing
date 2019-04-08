#pragma once

#include "NPC.h"
#include <vector>
class Player
{
public:
	Player();
	void Display() const;
	void Clear() const;
	void Up();
	void Down();
	void Left();
	void Right();
	bool Impact(const NPC &npc);
	void Move(int x, int y);
	void EditPlayerName(const string &new_name);
	string GetName() const;
	bool IsFinish() const;
	bool Die(const vector<NPC*>);
	string ToString();
private:
	int _x, _y;
	bool _alive;
	string _name;

};

