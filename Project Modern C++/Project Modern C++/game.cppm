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
		Game();
		~Game();

		Game& operator=(const Game& game);
		Game(const Game& game);

		Board getGameBoard() const;
		void setGameBoard(const Board& gameBoard);

		Player getPlayer1() const;
		void setPlayer1(const Player& player1);

		Player getPlayer2() const;
		void setPlayer2(const Player& player2);


		void startGame();
		bool isGameOver();

		void modifySizeofBoard(uint16_t size);

	};
	
}