#pragma once
import <ctime>;
import <cstdlib>;
import <fstream>;
import board;
import player;
import utility;


namespace twixt {
	class Game {

	private:
		Board m_gameBoard;
		Player m_player1;
		Player m_player2;
		Player* m_currentPlayer = nullptr;
		Player* m_opponentPlayer = nullptr;

		friend class GameFileManager;

	public:
		Game(Board& GameBoard, Player player1, Player player2);
		Game();
		~Game();

		Game& operator=(const Game& game);
		Game& operator=(Game&& game) noexcept;
		Game(const Game& game);
		Game(Game&& game) noexcept;

		Board getGameBoard() const;
		void setGameBoard(const Board& gameBoard);

		Player getPlayer1() const;
		void setPlayer1(const Player& player1);

		Player getPlayer2() const;
		void setPlayer2(const Player& player2);

		void playTurn();
		bool checkWinCondition();
		void run();
		void randomStarter();
		void offerPieRule();

		void swapPlayers();
		
		void displayGameBoard() const;

		
	};

}


