#include "Game.h"
bool Game::_sound = 1;
int main()
{
	bool IsSetting = 0;
	srand(time(NULL));
	try {
		Game game;
		while (true) {
			Console::MainMenu();
			switch (Console::ProcessMainMenu()) {
			/*case 0://Done
				if (game.Exit()) {
					//game.SaveGame();
					return EXIT_SUCCESS;
				}
				else continue;*/
			case 1://Editing
				
				if (!IsSetting)
				{
					game.NewGame();
					game.ResetGame();
				}
				game.StartGame();
				break;
			case 2://Done
				game.LoadGame();
				break;
			case 3://Done
				IsSetting=game.Setting();
				break;
			default: return EXIT_FAILURE;
			}
		}
	}
	catch (...) {
		return EXIT_FAILURE;
	}
	
}