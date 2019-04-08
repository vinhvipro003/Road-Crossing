#include "Player.h"
#include "Game.h"
#include <sstream>
Player::Player() : _x(60), _y(25), _alive(true), _name("New player") {}

void Player::Display() const {
	Console::TextColor(23);
	Console::GotoXY(this->_x, this->_y), cout << (char)220;
	Console::GotoXY(this->_x, this->_y + 1), cout << (char)94;
	Console::TextColor(15);
}
void Player::Move(int x, int y)
{
	Clear();
	_x = x;
	_y = y;
}
void Player::Clear() const {
	Console::TextColor(15);
	Console::GotoXY(this->_x, this->_y), cout << ' ';
	Console::GotoXY(this->_x, this->_y + 1), cout << ' ';
}
void Player::Up() {
	this->Clear();
	if ((this->_y - 1 == 24) || (this->_y - 1 == 19) || (this->_y - 1 == 14) || (this->_y - 1 == 9) || (this->_y - 1 == 4))
		this->_y -= 3;
	else if (this->_y > 0)
		--this->_y;
	this->Display();
}
void Player::Down() {
	this->Clear();
	if ((this->_y + 2 == 24) || (this->_y + 2 == 19) || (this->_y + 2 == 14) || (this->_y + 2 == 9) || (this->_y + 2 == 4))
		this->_y += 3;
	else if (this->_y <= 25)
		++this->_y;
	this->Display();
}
void Player::Left() {
	this->Clear();
	if (this->_x > 1)
		--this->_x;
	this->Display();
}
void Player::Right() {
	this->Clear();
	if (this->_x <= 118)
		++this->_x;
	this->Display();
}
bool Player::Impact(const NPC &npc) {
	return npc.Impact(this->_x, this->_y) || npc.Impact(this->_x, this->_y + 1);
}
bool Player::Die(const vector <NPC*>npc)
{
	for (auto i : npc)
		if (Impact(*i))
		{
			Console::GotoXY(55, 15);
			Console::TextColor(12);
			cout << "You die!";
			Console::TextColor(15);
			if(Game::Sound()) Console::DieSound();
			return true;
		}

	return false;
}
void Player::EditPlayerName(const string &new_name) {
	this->_name = new_name;
}
string Player::GetName() const {
	return this->_name;
}
bool Player::IsFinish() const {
	if (_y <= 2) {
		Console::GotoXY(55, 15);
		Console::TextColor(12);
		cout << "Level Up!";
		Console::TextColor(15);
	}
	return this->_y <= 2;
}
string Player::ToString()
{
	stringstream st;
	st << _x << " " << _y;
	return st.str();
}
