#include "game.h"
#include "GameFileManager.h"
#include <random>
#include <conio.h>


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

	Game::Game(uint16_t boardSize, uint16_t nrOfAvailablePylons, uint16_t nrOfAvailableBridges)
		: m_gameBoard{ boardSize },
		m_player1{ nrOfAvailablePylons, nrOfAvailableBridges, EColor::RED, m_gameBoard },
		m_player2{ nrOfAvailablePylons, nrOfAvailableBridges, EColor::BLACK, m_gameBoard },
		m_currentPlayer{ &m_player1 },
		m_opponentPlayer{ &m_player2 }
	{
	}

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

	const Board& Game::getGameBoard() const
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
		const auto& bridges = m_gameBoard.getBridges();
		const uint16_t size = m_gameBoard.getSize();

		auto isCorner = [](size_t i, size_t j, int size) {
			return ((i == 0 && j == 0) || (i == 0 && j == size - 1) || (i == size - 1 && j == size - 1) || (j == 0 && i == size - 1));
			};

		std::vector<std::vector<char>> gameMatrix(size * 2 - 1, std::vector<char>(size * 2 - 1, '-'));
		for (size_t i{ 0 }; i < size * 2 - 1; ++i) {
			for (size_t j{ 0 }; j < size * 2 - 1; ++j)
			{
				if (i % 2 == 0 && j % 2 == 0 && !isCorner(i, j, size * 2 - 1)) {
					gameMatrix[i][j] = '*';
				}
				else {
					gameMatrix[i][j] = ' ';
				}
			}
		}
		// Adaugă caracterele pentru pioni
		for (const auto& pylon : pylons) {
			if (pylon.has_value()) {
				uint16_t pylonX = pylon->getLine() * 2;
				uint16_t pylonY = pylon->getColumn() * 2;
				if (pylon->getColor() == EColor::RED) {
					gameMatrix[pylonX][pylonY] = 'R';
				}
				else {
					gameMatrix[pylonX][pylonY] = 'B';
				}
			}
		}

		// Adaugă caracterele pentru punți
		for (const auto& bridge : bridges) {
			uint16_t startX = bridge.getCoordStart().first * 2;
			uint16_t startY = bridge.getCoordStart().second * 2;
			uint16_t endX = bridge.getCoordEnd().first * 2;
			uint16_t endY = bridge.getCoordEnd().second * 2;

			int difLine{ abs(startX / 2 - endX / 2) };
			int difCol{ abs(startY / 2 - endY / 2) };

			if (startX > endX && startY > endY && difLine == 2 && difCol == 1) {
				gameMatrix[endX][endY + 1] = '\\';
				gameMatrix[endX + 1][endY + 1] = '|';
				gameMatrix[endX + 2][endY + 1] = '|';
				gameMatrix[endX + 3][endY + 1] = '|';
				gameMatrix[endX + 4][endY + 1] = '\\';
			}
			else if (endX > startX && endY > startY && difLine == 2 && difCol == 1) {
				gameMatrix[startX][startY + 1] = '\\';
				gameMatrix[startX + 1][startY + 1] = '|';
				gameMatrix[startX + 2][startY + 1] = '|';
				gameMatrix[startX + 3][startY + 1] = '|';
				gameMatrix[startX + 4][startY + 1] = '\\';
			}
			else if (startX > endX && startY < endY && difLine == 2 && difCol == 1) {
				gameMatrix[endX][endY - 1] = '/';
				gameMatrix[endX + 1][endY - 1] = '|';
				gameMatrix[endX + 2][endY - 1] = '|';
				gameMatrix[endX + 3][endY - 1] = '|';
				gameMatrix[endX + 4][endY - 1] = '/';
			}
			else if (startX < endX && startY > endY && difLine == 2 && difCol == 1) {
				gameMatrix[startX][startY - 1] = '/';
				gameMatrix[startX + 1][startY - 1] = '|';
				gameMatrix[startX + 2][startY - 1] = '|';
				gameMatrix[startX + 3][startY - 1] = '|';
				gameMatrix[startX + 4][startY - 1] = '/';
			}
			else if (startX > endX && startY > endY && difCol == 2 && difLine == 1) {
				gameMatrix[endX + 1][endY] = '\\';
				gameMatrix[endX + 1][endY + 1] = ' -';
				gameMatrix[endX + 1][endY + 2] = ' -';
				gameMatrix[endX + 1][endY + 3] = ' -';
				gameMatrix[endX + 1][endY + 4] = '\\';
			}
			else if (startX < endX && startY < endY && difCol == 2 && difLine == 1) {
				gameMatrix[startX + 1][startY] = '\\';
				gameMatrix[startX + 1][startY + 1] = ' -';
				gameMatrix[startX + 1][startY + 2] = ' -';
				gameMatrix[startX + 1][startY + 3] = ' -';
				gameMatrix[startX + 1][startY + 4] = '\\';
			}
			else if (startX > endX && startY < endY && difCol == 2 && difLine == 1) {
				gameMatrix[endX + 1][endY] = '/';
				gameMatrix[endX + 1][endY - 1] = ' -';
				gameMatrix[endX + 1][endY - 2] = ' -';
				gameMatrix[endX + 1][endY - 3] = ' -';
				gameMatrix[endX + 1][endY - 4] = '/';
			}
			else if (startX < endX && startY > endY && difCol == 2 && difLine == 1)
			{
				gameMatrix[startX + 1][startY] = '/';
				gameMatrix[startX + 1][startY - 1] = ' -';
				gameMatrix[startX + 1][startY - 2] = ' -';
				gameMatrix[startX + 1][startY - 3] = ' -';
				gameMatrix[startX + 1][startY - 4] = '/';
			}
		}



		const std::string redColor = "\033[31m";
		const std::string blueColor = "\033[34m";
		const std::string resetColor = "\033[0m";

		// Afișează starea jocului cu pioni și punți
		for (uint16_t i{ 0 }; i < size * 2 - 1; ++i) {
			for (uint16_t j{ 0 }; j < size * 2 - 1; ++j) {
				if (i == 1 || i == size * 2 - 3) {
					std::cout << redColor << "- " << resetColor;
				}
				else if (j == 1 || j == size * 2 - 3) {
					std::cout << blueColor << "|" << resetColor;
				}
				else if (gameMatrix[i][j] == 'R') {
					std::cout << redColor << gameMatrix[i][j] << " " << resetColor;
				}
				else if (gameMatrix[i][j] == 'B') {
					std::cout << blueColor << gameMatrix[i][j] << " " << resetColor;
				}
				else {
					std::cout << gameMatrix[i][j] << ' ';
				}

			}
			std::cout << '\n';
		}

		std::cout << "Turn of : ";
		displayCurrentPlayer();
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

	Player* Game::getCurrentPlayer() const
	{
		return m_currentPlayer;
	}

}
