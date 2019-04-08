#include "Truck.h"

Truck::Truck(const int &x, const int &y,const int&move) : NPC(x,y,move) {}

void Truck::Display() const {
	char block = (char)219;
	Console::TextColor(_color);
	Console::GotoXY(this->_x, this->_y), cout << block << block << block << block << block << block;
	Console::GotoXY(this->_x + 2, this->_y - 1), cout << block << block << block << block;
	Console::TextColor(15);
}
void Truck::Remove() const {
	Console::GotoXY(this->_x, this->_y), cout << "      ";
	Console::GotoXY(this->_x + 2, this->_y - 1), cout << "    ";
}
void Truck::Move(const int &level) {
	NPC::Move(level);
	this->Remove();
	int i = this->_x + this->_move;
	if (i < 1) i = 114;
	if (i > 114) i = 1;
	this->_x = i;
	this->Display();
}
bool Truck::Impact(const int &x, const int &y) const {
	if (y == this->_y)
		if ((x == this->_x) || (x == this->_x + 1) || (x == this->_x + 2) || (x == this->_x + 3) || (x == this->_x + 4) || (x == this->_x + 5))
			return true;
	if (y == this->_y - 1)
		if ((x == this->_x + 2) || (x == this->_x + 3) || (x == this->_x + 4) || (x == this->_x + 5))
			return true;
	return false;
}