module game;
import player;
import pylon;

twixt::Game::Game(Board GameBoard, Player player1, Player player2) 
	: m_gameBoard{ GameBoard },
	m_player1{ player1 },
	m_player2{ player2 }
{}

twixt::Game::Game() 
	: m_gameBoard{ 10 },
	m_player1{ 20, 40, Player::EColor::RED, m_gameBoard },
	m_player2{20, 40, Player::EColor::BLACK, m_gameBoard}
{}

twixt::Game::~Game()
{
}

twixt::Game& twixt::Game::operator=(const Game& game)
{
	if (this != &game) {
		m_gameBoard = game.m_gameBoard;
		m_player1 = game.m_player1;
		m_player2 = game.m_player2;
	}
	return *this;
}

twixt::Game::Game(const Game& game)
	: m_gameBoard{ game.m_gameBoard },
	m_player1{ game.m_player1 },
	m_player2{ game.m_player2 }
{}

twixt::Board twixt::Game::getGameBoard() const
{
	return m_gameBoard;
}

void twixt::Game::setGameBoard(const Board& gameBoard)
{
	m_gameBoard = gameBoard;
}

twixt::Player twixt::Game::getPlayer1() const
{
	return m_player1;
}

void twixt::Game::setPlayer1(const Player& player1)
{
	m_player1 = player1;
}

twixt::Player twixt::Game::getPlayer2() const
{
	return m_player2;
}

void twixt::Game::setPlayer2(const Player& player2)
{
	m_player2 = player2;
}

bool twixt::Game::isGameOver()
{
	const Board& board = m_gameBoard;
	const std::vector<Pylon>& pylons1 = m_player1.getPylons();
	const std::vector<Pylon>& pylons2 = m_player2.getPylons();

	auto isPathAvailable = [&](const Pylon& start, const Pylon& end) {
		return true; // incomplet , implementarea se face in clasa player?
	};

	for (const Pylon& pylonStart : pylons1) {
		if (pylonStart.getLine() == 0 || pylonStart.getLine() == 1) { 
			for (const Pylon& pylonFinish : pylons1) {
				if (pylonFinish.getLine() == board.getSize() - 1 || pylonFinish.getLine() == board.getSize() - 2) {  
					
					if (isPathAvailable(pylonStart, pylonFinish)) {
						
						return true;
					}
				}
			}
		}
	}

	for (const Pylon& pylonStart : pylons2) {
		if (pylonStart.getColumn() == 0 || pylonStart.getLine() == 1) {  
			for (const Pylon& pylonFinish : pylons2) {
				if (pylonFinish.getColumn() == board.getSize() - 1 || pylonFinish.getColumn() == board.getSize() - 2) {
					
					if (isPathAvailable(pylonStart, pylonFinish)) {
						
						return true;
					}
				}
			}
		}
	}

	return false;

}

void twixt::Game::modifySizeofBoard(uint16_t size)
{
	m_gameBoard.setSize(size);
}



//void twixt::Game::startGame()
//{
//	std::cout << "Please give the size of the game board: " << std::endl;
//	m_gameBoard = Board{ 22 };
//
//	m_player1 = Player{ 20, 40, Player::EColor::Red, m_gameBoard };
//	m_player2 = Player{ 20, 40, Player::EColor::Black, m_gameBoard };
//
//}



