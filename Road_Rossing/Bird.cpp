#include "Bird.h"

Bird::Bird(const int &x,const int &y,const int &move) : NPC(x, y,move) {}

void Bird::Display() const {
	Console::TextColor(_color);
	Console::GotoXY(this->_x, this->_y), cout << (char)223 << (char)223 << (char)220 << (char)223 << (char)223;
	Console::TextColor(15);
}
void Bird::Remove() const {
	Console::GotoXY(this->_x, this->_y), cout << "     ";
}
void Bird::Move(const int &level) {
	NPC::Move(level);
	this->Remove();
	int i = this->_x + this->_move;
	if (i < 0) i = 115;
	if (i > 115) i = 0;
	this->_x = i;
	this->Display();
}
bool Bird::Impact(const int &x, const int &y) const {
	if (y == this->_y)
		if (x == this->_x || x == this->_x + 1 || x == this->_x + 2 || x == this->_x + 3 || x == this->_x + 4)
			return true;
	return false;
}