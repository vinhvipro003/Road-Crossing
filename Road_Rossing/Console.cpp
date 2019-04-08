#include "Console.h"

void Console::BackgroundMusic() {
	//PlaySound("Patakas World.wav", NULL,);
}
void Console::DieSound()
{
	Beep(523, 500);
}
void Console::FixConsoleWindow() {
	HWND console_window = GetConsoleWindow();
	LONG style = GetWindowLong(console_window, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(console_window, GWL_STYLE, style);
}
void Console::TextColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void Console::ShowConsoleCursor(const bool &choose) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = choose;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void Console::GotoXY(const int &x, const int &y) {
	if (x < 0 || x > 129 || y < 0 || y > 29)
		return;
	COORD coord;
	coord.X = x, coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Console::SetText(const string &text, const int &x, const int &y) {
	TextColor(12);
	GotoXY(x, y), cout << text;
	TextColor(15);
}
void Console::Choose(const int &x, const int &y) {
	GotoXY(x , y); TextColor(12); cout << '+'; TextColor(15);
}
void Console::Border(const int &width, const int &height, const int &x, const int &y) {
	if (width < 1 || height < 1 || x < 0 || y < 0 || x > 129 || y > 29)
		return;

	GotoXY(x, y); cout << (char)218;
	for (int i = 0; i < width; ++i)
		cout << (char)196;
	cout << (char)191;

	for (int i = 0; i < height; ++i) {
		GotoXY(x, y + i + 1); cout << (char)179;
		GotoXY(x + width + 1, y + i + 1); cout << (char)179;
	}

	GotoXY(x, y + height + 1); cout << (char)192;
	for (int i = 0; i < width; ++i)
		cout << (char)196;
	cout << (char)217;
}
void Console::Button(const string &text, const int &width, const int &height, const int &x, const int &y) {
	Border(width, height, x, y);

	int text_length = text.length();
	if (text_length > width || height % 2 == 0)
		return;

	GotoXY((width - text_length) / 2 + x + 1, height / 2 + y + 1); 
	TextColor(10); 
	cout << text;
	TextColor(15);

}

void Console::MainMenu() {
	system("cls");
	FixConsoleWindow();
	SetConsoleTitle("Road Crossing");
	TextColor(9);
	GotoXY(38, 0); cout << "============";
	GotoXY(38, 1); cout << "==   =====  ==   ";
	GotoXY(38, 2); cout << "==  =     = ==   ";
	GotoXY(38, 3); cout << "==   ===== ==     =======      ==     ====== ";
	GotoXY(38, 4); cout << "== ====== ==      =======    ==  ==   =======";
	GotoXY(38, 5); cout << "== ==   ==  ==    ==   ==   ==    ==  ==   ==";
	GotoXY(38, 6); cout << "== ==    ==  ==   =======  ========== =======";
	GotoXY(38, 7); cout << "=====     ======  =======  ==      == ======";
	GotoXY(25, 9); cout <<  "==============  ";
	GotoXY(25, 10); cout << "==============  ";
	GotoXY(25, 11); cout << "==============  ";
	GotoXY(25, 12); cout << "====            =======   =======  =======  =======  ===  ===  ==  =======";
	GotoXY(25, 13); cout << "====            ==    ==  =======  ==       ==       ===  ==== ==  ==     ";
	GotoXY(25, 14); cout << "==============  =======   ==   ==  =======  =======  ===  == ====  ==  ====";
	GotoXY(25, 15); cout << "==============  ==    ==  =======       ==       ==  ===  ==  ===  ==   ==";
	GotoXY(25, 16); cout << "==============  ==     == =======  =======  =======  ===  ==  ===  =======";
	TextColor(15);
	Button("NEW GAME", 40, 1, 40, 17);
	Button("LOAD GAME", 40, 1, 40, 20);
	Button("SETTING", 40, 1, 40, 23);
	Button("EXIT", 40, 1, 40, 26);
}
int Console::ProcessMainMenu() {
	int y = 18;
	Console::ShowConsoleCursor(false);
	Choose(38, y); 

	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 80: 
				if (y < 27) {
					GotoXY(37, y); cout << "  ";
					Choose(38, y += 3);
				}
				break;
			case 72: 
				if (y > 18) {
					GotoXY(37, y); cout << "  ";
					Choose(38, y -= 3);
				}
				break;
			}
		}
	}

	switch (y) {
	case 18: //New Game
		return 1;
	case 27: //Exit
		return 0;
	case 21: //Load Game
		return 2;
	case 24: //Setting
		return 3;
		break;
	default: return 0;
	}
}
void Console::NewGameMenu() {
	Border(60, 20, 29, 4);

	string text = "New Game";
	SetText(text, 60 - text.length() / 2, 2);

	SetText("Player Names:", 33, 6);
	Border(32, 1, 53, 5);

	Button("Back", 10, 1, 32, 22);
	Button("GO", 10, 1, 76, 22);
}
void Console::SaveGameMenu() {
	Border(60, 20, 29, 4);

	string text = "Save Game";
	SetText(text, 60 - text.length() / 2, 2);

	Border(20, 3, 32, 5);
	SetText("Save-data 1", 34, 6);
	Border(20, 3, 32, 11);
	SetText("Save-data 3", 34, 12);
	Border(20, 3, 32, 17);
	SetText("Save-data 5", 34, 18);

	Border(20, 3, 66, 5);
	SetText("Save-data 2", 68, 6);
	Border(20, 3, 66, 11);
	SetText("Save-data 4", 68, 12);
	Border(20, 3, 66, 17);
	SetText("Save-data 6", 68, 18);

	Button("Back", 10, 1, 32, 22);
	Button("Save", 10, 1, 76, 22);
}
void Console::LoadGameMenu() {
	Border(60, 20, 29, 4);

	string text = "Load Game";
	SetText(text, 60 - text.length() / 2, 2);

	Border(20, 3, 32, 5);
	SetText("Save-data 1", 34, 6);
	Border(20, 3, 32, 11);
	SetText("Save-data 3", 34, 12);
	Border(20, 3, 32, 17);
	SetText("Save-data 5", 34, 18);

	Border(20, 3, 66, 5);
	SetText("Save-data 2", 68, 6);
	Border(20, 3, 66, 11);
	SetText("Save-data 4", 68, 12);
	Border(20, 3, 66, 17);
	SetText("Save-data 6", 68, 18);

	Button("Back", 10, 1, 32, 22);
	Button("Load", 10, 1, 76, 22);
}
void Console::SettingMenu() {
	Border(60, 20, 29, 4);

	string text = "Setting";
	SetText(text, 60 - text.length() / 2, 2);

	SetText("New player name:", 33, 6);
	Border(32, 1, 53, 5);

	SetText("Change level:", 33, 10);
	Border(32, 1, 53, 9);

	SetText("Sound 0/1 to off/on:", 33, 14);
	Border(32, 1, 53, 13);

	Button("Back", 10, 1, 32, 22);
	Button("Save", 10, 1, 76, 22);
}
void Console::ExitMenu() {
	Border(30, 5, 44, 12);

	string text = "Do you want to exit?";
	SetText(text, 60 - text.length() / 2, 10);

	Button("Continue", 10, 1, 47, 14);
	Button("Exit", 10, 1, 61, 14);
}
bool Console::Accept() {
	int x = 74;
	Choose(x, 23);

	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 75:
				if (x == 74) {
					GotoXY(x, 23); cout << ' ';
					Choose(x -= 44, 23);
				}
				break;
			case 77:
				if (x == 30) {
					GotoXY(x, 23); cout << ' ';
					Choose(x += 44, 23);
				}
				break;
			}
		}
	}

	return x == 74;
}
void Console::GameOverMenu() {
	Border(30, 5, 44, 12);

	string text = "GAME OVER! Retry?";
	SetText(text, 60 - text.length() / 2, 10);

	Button("Retry~", 10, 1, 47, 14);
	Button("Exit", 10, 1, 61, 14);
}
void Console::WinMenu() {
	Border(30, 5, 44, 12);

	string text = "You are winner! Do you want to play the next level?";
	SetText(text, 60 - text.length() / 2, 10);

	Button("Next", 10, 1, 47, 14);
	Button("Exit", 10, 1, 61, 14);
}