#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Console {
public:
	static void BackgroundMusic();
	static void DieSound();
	static void FixConsoleWindow();
	static void TextColor(int x);
	static void ShowConsoleCursor(const bool &choose);
	static void GotoXY(const int &x, const int &y);
	static void SetText(const string &text, const int &x, const int &y);
	static void Choose(const int &x, const int &y);
	static void Border(const int &width, const int &height, const int &x, const int &y);
	static void Button(const string &text, const int &width, const int &height, const int &x, const int &y);
	static void MainMenu();
	static int ProcessMainMenu();
	static void NewGameMenu();
	static void SaveGameMenu();
	static void LoadGameMenu();
	static void SettingMenu();
	static void ExitMenu();
	static bool Accept();
	static void GameOverMenu();
	static void WinMenu();
};