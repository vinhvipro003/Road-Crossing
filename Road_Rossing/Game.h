#pragma once
#include "NPC.h"
#include "Console.h"
#include "Player.h"
#include <vector>
#include <thread>
#include <fstream>
#include <mutex>
using namespace std;

class Game {
public:
	Game();
	~Game();
	static bool Sound() { return _sound; }
	void DrawMap() const;
	void StartGame();
	bool NewGame();
	void SaveGame();
	void LoadGame();
	bool Setting();
	bool Exit();
	bool Win();
	bool GameOver();
	void ResetGame();
	void AllMove(const int &level);
	void StafficLight(int);
	void Stop(thread* sub_thread);
	void GetNewGameData();
private:
	Player * _player;
	vector<NPC*> line1;
	vector<NPC*> line2;
	vector<NPC*> line3;
	vector<NPC*> line4;
	bool STOP;
	bool ExitGame;
	int _stafficLight;
	int _level;
	static bool _sound;
	bool _game;
	bool _gameOver;
	int _move;
	mutex _mutex;
	void DrawLight(int light);
	void EachDataSaved(ifstream &fin, const int &number) const;
	void PrintSaveData() const;
	void LoadData(const int &number);
	void SaveData(const int &number);
};