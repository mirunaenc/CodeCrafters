module game;
import player;

twixt::Game::Game(Board GameBoard, Player player1, Player player2) 
	: m_gameBoard{ GameBoard },
	m_player1{ player1 },
	m_player2{ player2 }
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



