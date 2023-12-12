#include <fstream>
#include "game.h"

namespace twixt {
	class GameFileManager
	{
		static void saveGame(const Game& game);
		static void loadGame(Game& game);
	};
}


