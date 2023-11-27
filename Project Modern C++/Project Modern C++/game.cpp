#include "game.h"


namespace twixt {
	Game::Game(Board GameBoard, Player player1, Player player2)
		: m_gameBoard{ GameBoard },
		m_player1{ player1 },
		m_player2{ player2 },
		m_currentPlayer { &m_player1 },
		m_opponentPlayer{ &m_player2 }
	{}

	Game::Game()
		: m_gameBoard{ 10 },
		m_player1{ 20, 40, Player::EColor::RED, m_gameBoard },
		m_player2{ 20, 40, Player::EColor::BLACK, m_gameBoard },
		m_currentPlayer{ &m_player1 },
		m_opponentPlayer{ &m_player2 }
	{}

	Game::~Game()
	{
	}

	Game& twixt::Game::operator=(const Game& game)
	{
		if (this != &game) {
			m_gameBoard = game.m_gameBoard;
			m_player1 = game.m_player1;
			m_player2 = game.m_player2;
			m_currentPlayer = &m_player1 ;
			m_opponentPlayer = &m_player2 ;
			
		}
		return *this;
	}

	Game& Game::operator=(Game&& game) noexcept
	{
		if (this != &game) {
			m_gameBoard = game.m_gameBoard;
			m_player1 = game.m_player1;
			m_player2 = game.m_player2;
			m_currentPlayer = &m_player1;
			m_opponentPlayer = &m_player2;
			
		}
		return *this;
	}

	

	Game::Game(const Game& game)
		: m_gameBoard{ game.m_gameBoard },
		m_player1{ game.m_player1 },
		m_player2{ game.m_player2 },
		m_currentPlayer{ &m_player1 },
		m_opponentPlayer{ &m_player2 }
	{}

	Game::Game(Game && game) noexcept
		: m_gameBoard{ game.m_gameBoard },
		m_player1{ game.m_player1 },
		m_player2{ game.m_player2 },
		m_currentPlayer{ &m_player1 },
		m_opponentPlayer{ &m_player2 }
	{}

	Board Game::getGameBoard() const
	{
		return m_gameBoard;
	}

	void Game::setGameBoard(const Board& gameBoard)
	{
		m_gameBoard = gameBoard;
	}

	Player Game::getPlayer1() const
	{
		return m_player1;
	}

	void Game::setPlayer1(const Player& player1)
	{
		m_player1 = player1;
	}

	Player Game::getPlayer2() const
	{
		return m_player2;
	}

	void Game::setPlayer2(const Player& player2)
	{
		m_player2 = player2;
	}

	void Game::playTurn()
	{
		if (checkWinCondition()) {
			std::cout << "The game has ended. We have a winner!" << std::endl;
			std::cout << "The winner is: " << std::endl;
			DisplayCurrentPlayer();
			return;
		}

		//currentPlayer->makeMove(); //the method is not implement in Player class yet.

		if (checkWinCondition()) {
			std::cout << "Congratulations! The current player has won!" << std::endl;
			std::cout << "The winner is: " << std::endl;
			DisplayCurrentPlayer();
			return;
		}

		std::swap(m_currentPlayer, m_opponentPlayer);
	}

	bool Game::checkWinCondition()
	{
		if (m_currentPlayer->isWinner()) {
			return true;
		}
		return false;
	}

	


	void Game::run()
	{
		while (!checkWinCondition()) {
			playTurn();
		}
		std::cout << "The game ends.";
		return ;
	}

	/*void Game::swapPlayers()
	{
	
		Player* temp = m_currentPlayer;
		m_currentPlayer = m_opponentPlayer;
		m_opponentPlayer = temp;

	}*/

	void Game::DisplayCurrentPlayer() {
		if (m_currentPlayer == &m_player1) {
			std::cout << "m_currentPlayer is referring to m_player1\n";
			/*std::cout << m_player1;*/
		}
		else if (m_currentPlayer == &m_player2) {
			std::cout << "m_currentPlayer is referring to m_player2\n";
			/*std::cout << m_player2;*/
		}
	}



	void Game::modifySizeofBoard(uint16_t size)
	{
		m_gameBoard.setSize(size);
	}

}
