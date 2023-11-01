module;

export module game;

import player;
import board;

namespace twixt {
	export class Game {

	private: 
		Board m_gameBoard;
		Player m_player1;
		Player m_player2;

	public: 
		Game(Board GameBoard, Player player1, Player player2);

		Game& operator=(const Game& game);

		Game(const Game& game);

	};
}