#include "game.h"
import "game.h";
import "GameFileManager.h";
import <random>;
import <conio.h>;


namespace twixt {
	Game::Game(Board& GameBoard, Player player1, Player player2)
		: m_gameBoard{ GameBoard },
		m_player1{ player1 },
		m_player2{ player2 },
		m_currentPlayer { &m_player1 },
		m_opponentPlayer{ &m_player2 }
	{}

	Game::Game()
		: m_gameBoard{ 10 },
		m_player1{ 20, 40, EColor::RED, m_gameBoard },
		m_player2{ 20, 40, EColor::BLACK, m_gameBoard },
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
			displayCurrentPlayer();
			return;
		}

		m_currentPlayer->makeMove(); 

		if (checkWinCondition()) {
			std::cout << "Congratulations! The current player has won!" << std::endl;
			std::cout << "The winner is: " << std::endl;
			displayCurrentPlayer();
			return;
		}

		swapPlayers();
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
	
		std::cout << "Do you want to load the saved game? (yes/no)" << std::endl;
		std::string response;
		std::getline(std::cin, response);

		
		std::transform(response.begin(), response.end(), response.begin(), ::tolower);

		if (response == "yes") {
			twixt::GameFileManager::loadGame(*this);
		}

		while (!checkWinCondition()) {
			displayGameBoard();
			playTurn();
			std::cout << "Do you want save the game? (yes/no)"<<std::endl;
			std::string yes;
			std::cin >> yes;
			if (yes == "yes") {
				twixt::GameFileManager::saveGame(*this);
			}
			
			
		}
		std::cout << "The game ends.";
		return ;
	}

	void Game::randomStarter()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 10);

		int randomNumber = dis(gen);
		if (randomNumber % 2 == 0) {
			m_currentPlayer = &m_player1;
			m_opponentPlayer = &m_player2;
		}
		else {
			m_currentPlayer = &m_player2;
			m_opponentPlayer = &m_player1;
		}
	}

	void Game::offerPieRule()
	{
		std::cout << "The pie rule is in effect. Do you want to swap sides? (Y/N): ";
		char choice;
		std::cin >> choice;

		if (choice == 'Y' || choice == 'y') {
			swapPlayers(); // Schimbă jucătorii
			std::cout << "Players have swapped sides.\n";
			displayGameBoard(); // Afișează tabla actualizată după schimbarea părților
		}
		else {
			std::cout << "No changes made.\n";
		}
	}

	void Game::swapPlayers()
	{
	
		Player* temp = m_currentPlayer;
		m_currentPlayer = m_opponentPlayer;
		m_opponentPlayer = temp;

	}


	void Game::displayGameBoard() const /// still in process
	{
		
		std::system("cls"); 

		const auto& pylons = m_gameBoard.getPylons();
		/*const auto& bridges = m_gameBoard.getBridges();*/
		const uint16_t size = m_gameBoard.getSize();

		for (uint16_t i = 0; i < size; ++i) {
			for (uint16_t j = 0; j < size; ++j) {
				bool pylonExists = false;
				char displayChar = '-'; 

				for (const auto& pylon : pylons) {
					if (pylon.has_value() && pylon->getLine() == i && pylon->getColumn() == j) {
						pylonExists = true;
						if (pylon->getColor() == EColor::RED) { /// must to resolve this
							displayChar = 'R'; 
						}
						else {
							displayChar = 'B';
						}
						break;
					}
				}

				std::cout << displayChar << ' ';
			}
			std::cout << '\n';
		}
	

		if (m_currentPlayer != nullptr) {
			std::cout << "Turn of : ";
			if (m_currentPlayer == &m_player1) {
				std::cout << "Player RED\n";
			}
			else {
				std::cout << "Player BLACK\n";
			}
		}
		else {
			std::cout << "No player's turn!\n";
		}
	}

	void Game::displayCurrentPlayer() const
	{
		if (m_currentPlayer != nullptr) {
			if (m_currentPlayer == &m_player1) {
				std::cout << "Player RED\n";
			}
			else {
				std::cout << "Player BLACK\n";
			}
		}
		else {
			std::cout << "No color!\n";
		}
	}

}
