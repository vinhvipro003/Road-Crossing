#include "Game.h"
#include "Bird.h"
#include "Car.h"
#include "Dinosaur.h"
#include "Truck.h"

void Game::EachDataSaved(ifstream &fin, const int &number) const {
	int x = 0, y = 0;
	switch (number) {
	case 1: x = 34, y = 7; break;
	case 2: x = 68, y = 7; break;
	case 3: x = 34, y = 13; break;
	case 4: x = 68, y = 13; break;
	case 5: x = 34, y = 19; break;
	case 6: x = 68, y = 19; break;
	}
	string player_name;
	int level;
	if (!fin.is_open())
		Console::GotoXY(x, y), cout << "No data";
	else {
		getline(fin, player_name);
		fin >> level;
		Console::GotoXY(x, y), cout << "Name: " << player_name;
		Console::GotoXY(x, y + 1), cout << "Level: " << level;
	}
	fin.close();
}
void Game::PrintSaveData() const {
	ifstream fin("save/save1.txt");
	this->EachDataSaved(fin, 1);

	fin.open("save/save2.txt");
	this->EachDataSaved(fin, 2);

	fin.open("save/save3.txt");
	this->EachDataSaved(fin, 3);

	fin.open("save/save4.txt");
	this->EachDataSaved(fin, 4);

	fin.open("save/save5.txt");
	this->EachDataSaved(fin, 5);

	fin.open("save/save6.txt");
	this->EachDataSaved(fin, 6);
}
void Game::LoadData(const int &number) {
	ifstream fin;
	switch (number) {
	case 1: fin.open("save/save1.txt"); break;
	case 2: fin.open("save/save2.txt"); break;
	case 3: fin.open("save/save3.txt"); break;
	case 4: fin.open("save/save4.txt"); break;
	case 5: fin.open("save/save5.txt"); break;
	case 6: fin.open("save/save6.txt"); break;
	}
	if (fin.is_open()) {
		string player_name;
		int level;
		int n;
		int _x, _y;
		
		ResetGame();
		getline(fin, player_name);
		
		fin >> level;
		this->_player->EditPlayerName(player_name);
		this->_level = level;
		fin >> _x >> _y;
		_player->Move(_x, _y);
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y,move;
			fin >> x >> y >> move;
			line1.push_back(new Car(x, y, move));
		}
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y, move;
			fin >> x >> y >> move;
			line2.push_back(new Truck(x, y, move));

		}
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y, move;
			fin >> x >> y >> move;
			line3.push_back(new Dinosaur(x, y, move));
		}
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y, move;
			fin >> x >> y >> move;
			line3.push_back(new Bird(x, y, move));

		}
		StartGame();

	}
	else {
		string text = "Error: This is empty.";
		Console::SetText(text, 60 - text.length() / 2, 2);
		_getwch(); this->LoadGame();
	}
	fin.close();
}
void Game::SaveData(const int &number) {
	ofstream fout;
	switch (number) {
	case 1: fout.open("save/save1.txt"); break;
	case 2: fout.open("save/save2.txt"); break;
	case 3: fout.open("save/save3.txt"); break;
	case 4: fout.open("save/save4.txt"); break;
	case 5: fout.open("save/save5.txt"); break;
	case 6: fout.open("save/save6.txt"); break;
	}
	if (fout.is_open())
	{
		fout << this->_player->GetName() << endl << this->_level << endl;
		fout << _player->ToString() << endl;
		fout << line1.size()<<endl;
		for (auto i : line1)
			fout << i->ToString()<<endl;
		fout << line2.size() << endl;
		for (auto i : line2)
			fout << i->ToString() << endl;
		fout << line3.size() << endl;
		for (auto i : line3)
			fout << i->ToString() << endl;
		fout << line4.size() << endl;
		for (auto i : line4)
			fout << i->ToString() << endl;
	}
	else {
		string text = "Error: Can't save the game data. Make sure in this directory has a folder \"save\".";
		Console::SetText(text, 60 - text.length() / 2, 2);
		_getwch(); this->SaveGame();
	}
	fout.close();
}

Game::Game() : STOP(false), _player(new Player), _level(1) {
	Console::ShowConsoleCursor(false);
	_gameOver = 0;
	ExitGame = 0;
	_sound = 1;
}
Game::~Game() {
	this->STOP = true;
	this->_level = 0;
	delete this->_player;
	for (auto &i : this->line1) delete i;
	line1.erase(line1.begin(), line1.end());
	for (auto &i : this->line2) delete i;
	line2.erase(line2.begin(), line2.end());
	for (auto &i : this->line3) delete i;
	line3.erase(line3.begin(), line3.end());
	for (auto &i : this->line4) delete i;
	line4.erase(line4.begin(), line4.end());
}

void Game::GetNewGameData()
{
	for (int i = 0; i < 120; i += 20)
	{
		this->line1.push_back(new Car(i, 23, 1));
	}
	for (int i = 114; i > 0; i -= 20)
	{
		this->line2.push_back(new Truck(i, 18, -1));

	}
	for (int i = 0; i < 120; i += 20)
	{
		this->line4.push_back(new Bird(i, 11, 1));
	}
	for (int i = 114; i > 0; i -= 20)
	{
		this->line3.push_back(new Dinosaur(i, 8, -1));
	}
}
void Game::DrawMap() const {
	char line = (char)196;
	Console::TextColor(12);
	Console::GotoXY(0, 29); cout << "Press Up/w to move up.";
	Console::GotoXY(0, 28); cout << "Press Down/s to move down.";
	Console::GotoXY(0, 27); cout << "Press Left/d to move right.";
	Console::GotoXY(0, 26); cout << "Press Right/a to move left.";
	Console::TextColor(15);

	for (int i = 0; i < 120; ++i)
		Console::GotoXY(i, 4), cout << line,
		Console::GotoXY(i, 9), cout << line,
		Console::GotoXY(i, 14), cout << line,
		Console::GotoXY(i, 19), cout << line,
		Console::GotoXY(i, 24), cout << line;
	Console::TextColor(9);
	Console::GotoXY(100, 29); cout << "Press P to pause.";
	Console::GotoXY(100, 28); cout << "Press L to save.";
	Console::GotoXY(100, 27); cout << "Press T to load.";
	Console::TextColor(15);
}
void Game::StartGame() {
	system("cls");
	STOP = 0;
	this->DrawMap();
	_move = 0;
	Console::GotoXY(0, 25), cout << "Player: " << this->_player->GetName();
	Console::GotoXY(110, 25), cout << "Level: " << this->_level;
	string text = "Start Here!!!"; Console::SetText(text, 60 - text.length() / 2, 29);
	text = "Finish Here!!!"; Console::SetText(text, 60 - text.length() / 2, 0);
	if (line1.empty()) GetNewGameData();
	
	_gameOver = 0;
	this->_player->Display();
	thread Light(&Game::StafficLight, this,4);
	thread lane_running(&Game::AllMove, this, this->_level);
	while (true) {
		if (_kbhit()) {
			char key = _getch();
			key = toupper((int)key);
			if (_gameOver) break;
			switch (key) {
			case 72: case 'W':case 'w':
				_move = 1;
				break;
			case 80: case 'S':case 's':
				_move = 2;
				break;
			case 75: case 'A':case 'a':
				_move = 3;
				break;
			case 77: case 'D':case 'd':
				_move = 4;
				break;
			case 'L':case 'l':
				Stop(&lane_running);
				Stop(&Light);
				SaveGame();
				StartGame();
				return;
			case 'T':case 't':
				Stop(&lane_running);
				Stop(&Light);
				LoadGame();
				return;
				break;
			}
			if (this->_player->IsFinish())
			{
				Stop(&lane_running);
				Stop(&Light);
				break;
			}
			if (_gameOver)break;
			if (this->_player->Die(line1) || this->_player->Die(line2) || this->_player->Die(line3) || this->_player->Die(line4))
				{
					_gameOver = 1;
					break;
				}

		}
	}
	if (_player->IsFinish()) this->Win();
	if (_gameOver) {
		this->GameOver();
	}
	Stop(&lane_running);
	Stop(&Light);

}
void Game::StafficLight(int n)
{
	while (!STOP)
	{
		for (int i = n; i > 0;i-- )
		{
			_stafficLight = i;
			for (int j = 1; j <= 800; j++)
			{
				Sleep(1);
				if (STOP) return;
			}
			if (this->_player->IsFinish() || _gameOver) return;
		}
		for (int i = n; i > 0; i--)
		{
			_stafficLight = -i;
			for (int j = 1; j <= 800; j++)
			{
				Sleep(1);
				if (STOP) return;
			}
			if (this->_player->IsFinish() || _gameOver) return;
		}
	}

}

bool Game::NewGame() {
	system("cls");
	Console::NewGameMenu();

	Console::Choose(31, 6);
	Console::GotoXY(54, 6);
	string player_name; getline(cin, player_name);

	if (Console::Accept()) {
		this->_player->EditPlayerName(player_name);
		return true;
	}
	else return false;
}
void Game::SaveGame() {
	system("cls");
	Console::SaveGameMenu();
	this->PrintSaveData();

	int x = 30, y = 7;
	Console::Choose(x, y); //Save-data 1

	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 72: //Up
				if (y > 7) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x, y -= 6);
				}
				break;
			case 80: //Down
				if (y < 19) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x, y += 6);
				}
				break;
			case 75: //Left
				if (x == 64) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x -= 34, y);
				}
				break;
			case 77: //Right
				if (x == 30) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x += 34, y);
				}
				break;
			}
		}
	}

	if (Console::Accept()) {
		switch (y) {
		case 7:
			if (x == 30) this->SaveData(1);
			else if (x == 64) this->SaveData(2);
			break;
		case 13:
			if (x == 30) this->SaveData(3);
			else if (x == 64) this->SaveData(4);
			break;
		case 19:
			if (x == 30) this->SaveData(5);
			else if (x == 64) this->SaveData(6);
			break;
		}
	}
}
void Game::LoadGame() {
	system("cls");
	Console::LoadGameMenu();
	this->PrintSaveData();

	int x = 30, y = 7;
	Console::Choose(x, y); //Save-data 1

	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 72: //Up
				if (y > 7) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x, y -= 6);
				}
				break;
			case 80: //Down
				if (y < 19) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x, y += 6);
				}
				break;
			case 75: //Left
				if (x == 64) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x -= 34, y);
				}
				break;
			case 77: //Right
				if (x == 30) {
					Console::GotoXY(x, y); cout << ' ';
					Console::Choose(x += 34, y);
				}
				break;
			}
		}
	}

	if (Console::Accept()) {
		switch (y) {
		case 7:
			if (x == 30) this->LoadData(1);
			else if (x == 64) this->LoadData(2);
			break;
		case 13:
			if (x == 30) this->LoadData(3);
			else if (x == 64) this->LoadData(4);
			break;
		case 19:
			if (x == 30) this->LoadData(5);
			else if (x == 64) this->LoadData(6);
			break;
		}
	}
}
bool Game::Setting() {
	system("cls");
	Console::SettingMenu();

	Console::Choose(31, 6);
	Console::GotoXY(54, 6);
	string player_name; getline(cin, player_name);

	Console::GotoXY(31, 6), cout << ' ', Console::Choose(31, 10);
	Console::GotoXY(54, 10);
	int level = 0; cin >> level, cin.get();
	if (cin.fail() || level > 10 || level < 1)
	{
		string text = "Error: Can't change to this level.";
		Console::SetText(text, 60 - text.length() / 2, 2);
		_getch();
		return false;
	}
	ResetGame();
	Console::GotoXY(31, 10); cout << ' '; Console::Choose(31, 14);
	Console::GotoXY(54, 14);
	int sound;
	cin >> sound;
	if(!(sound==1||sound==0))
	{
		string text = "Error: Can't change this sound status.";
		Console::SetText(text, 60 - text.length() / 2, 2);
		_getch();
		return false;
	}
	_sound = sound;
	Console::Choose(31, 14); 
	if (Console::Accept()) {
		this->_player->EditPlayerName(player_name);
		level = (level > 0) ? level : -level;
		this->_level = level;
	}
	return true;
}
bool Game::Exit() {
	system("cls");
	Console::ExitMenu();

	int x = 45;
	Console::Choose(x, 15);

	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 75:
				if (x == 59) {
					Console::GotoXY(x, 15); cout << ' ';
					Console::Choose(x -= 14, 15);
				}
				break;
			case 77:
				if (x == 45) {
					Console::GotoXY(x, 15); cout << ' ';
					Console::Choose(x += 14, 15);
				}
			}
		}
	}

	return x == 59;
}
bool Game::Win() {
	system("cls");
	_getch();
	int lv = this->_level+1;
	if (lv > 10) lv--;
	this->ResetGame();
	_level = lv;
	this->StartGame();
	return 1;
}
bool Game::GameOver() {
	if (ExitGame) return false;
	system("cls");
	Console::GameOverMenu();

	int x = 45;
	Console::Choose(x, 15);

	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 75:
				if (x == 59) {
					Console::GotoXY(x, 15); cout << ' ';
					Console::Choose(x -= 14, 15);
				}
				break;
			case 77:
				if (x == 45) {
					Console::GotoXY(x, 15); cout << ' ';
					Console::Choose(x += 14, 15);
				}
				break;
			}
		}
	}
	if (x == 45) {
		this->ResetGame();
		this->StartGame();
	}
	ExitGame = 1;
	return x == 59;
}
void Game::ResetGame() {
	_level = 1;
	string name = _player->GetName();
	delete _player;
	_player = new Player;
	_player->EditPlayerName(name);
	ExitGame = 0;
	for (auto &i : this->line1) delete i;
	line1.erase(line1.begin(), line1.end());
	for (auto &i : this->line2) delete i;
	line2.erase(line2.begin(), line2.end());
	for (auto &i : this->line3) delete i;
	line3.erase(line3.begin(), line3.end());
	for (auto &i : this->line4) delete i;
	line4.erase(line4.begin(), line4.end());
}
void Game::DrawLight(int light)
{
	if (light > 0) Console::TextColor(9);
	else
	{
		Console::TextColor(12);
	}
	int i = abs(light);
	Console::GotoXY(118, 20);
	cout << i;
	Console::GotoXY(1, 15);
	cout << i;
	Console::TextColor(15);
}
void Game::AllMove(const int &level) {
	_stafficLight = 4;
	while (!STOP) {
		//cout << _stafficLight;
		if (_stafficLight !=0)
		DrawLight(_stafficLight);
		if(_stafficLight>0)
		for (auto &i : this->line1) {
			if (_gameOver) return;
			if (_player->IsFinish()) return;
			this->_mutex.lock();
			i->Move(level);
			this->_mutex.unlock();
		}
		if (_stafficLight>0)
		for (auto &i : this->line2) {
			if (_gameOver) return;
			if (_player->IsFinish()) return;
			this->_mutex.lock();
			i->Move(level);
			this->_mutex.unlock();
		}
		for (auto &i : this->line3) {
			if (_gameOver) return;
			if (_player->IsFinish()) return;
			this->_mutex.lock();
			i->Move(level);
			this->_mutex.unlock();
		}
		for (auto &i : this->line4) {
			if (_gameOver) return;
			if (_player->IsFinish()) return;
			this->_mutex.lock();
			i->Move(level);
			this->_mutex.unlock();
		}
		if (_move == 1) _player->Up();
		if (_move == 2) _player->Down();
		if (_move == 3)_player->Left();
		if (_move == 4) _player->Right();
		_move = 0;
		
		if (this->_player->Die(line1) || this->_player->Die(line2) ||
			this->_player->Die(line3) || this->_player->Die(line4)) {
			_gameOver = 1;
			return;
		};
		if (_gameOver) return;
		if (_player->IsFinish()) return;
	}
}
void Game::Stop(thread* sub_thread) {
	system("cls");
	this->STOP = true;
	sub_thread->join();
}
