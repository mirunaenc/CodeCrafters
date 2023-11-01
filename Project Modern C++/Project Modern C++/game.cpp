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