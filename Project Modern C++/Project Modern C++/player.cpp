module player;


twixt::Player::Player(uint16_t nrPylons, uint16_t nrBridges, EColor color, Board& gameBoard) 
	: m_nrOfAvailablePylons{ nrPylons }, m_nrOfAvailableBridges{ nrBridges }, m_color{ color }, m_gameBoard(gameBoard)
{}

twixt::Player::Player(const Player& otherPlayer)
	: m_nrOfAvailablePylons{ otherPlayer.m_nrOfAvailablePylons},
	m_nrOfAvailableBridges{ otherPlayer.m_nrOfAvailableBridges},
	m_color{ otherPlayer.m_color},m_pylons{ otherPlayer.m_pylons},
	m_bridges{ otherPlayer.m_bridges},
	m_gameBoard{ otherPlayer.m_gameBoard}
{}

twixt::Player& twixt::Player::operator=(const Player& otherPlayer)
{
	if (this != &otherPlayer) {
		m_nrOfAvailablePylons = otherPlayer.m_nrOfAvailablePylons;
		m_nrOfAvailableBridges = otherPlayer.m_nrOfAvailableBridges;
		m_color = otherPlayer.m_color;
		m_pylons = otherPlayer.m_pylons;
		m_bridges = otherPlayer.m_bridges;
		m_gameBoard = otherPlayer.m_gameBoard;
	}
	return *this;
}


uint16_t twixt::Player::getNrOfAvailablePylons() const
{
	return m_nrOfAvailablePylons;
}

void twixt::Player::setNrOfAvailablePylons(uint16_t nrPylons)
{
	m_nrOfAvailablePylons = nrPylons;
}

uint16_t twixt::Player::getNrOfAvailableBridges() const
{
	return m_nrOfAvailableBridges;
}

void twixt::Player::setNrOfAvailableBridges(uint16_t nrBridges)
{
	m_nrOfAvailableBridges = nrBridges;
}

twixt::Player::EColor twixt::Player::getColor() const
{
	return m_color;
}

void twixt::Player::setColor(const EColor& color)
{
	m_color = color;
}

twixt::Player::~Player()
{

}

const twixt::Board& twixt::Player::getGameBoard() const
{
	return m_gameBoard;
}

void twixt::Player::setGameBoard(const Board& gameBoard)
{
	m_gameBoard = gameBoard;
}

const std::vector<twixt::Pylon>& twixt::Player::getPylons() const
{
	return m_pylons;
}

void twixt::Player::setPylons(const std::vector<Pylon>& pylons)
{
	m_pylons = pylons;
}

const std::vector<twixt::Bridge>& twixt::Player::getBridges() const
{
	return m_bridges;
}

void twixt::Player::setBridges(const std::vector<Bridge>& bridges)
{
	m_bridges = bridges;
}

void twixt::Player::placePylon(uint16_t line, uint16_t column)
{
	Pylon pylon(line, column);
	m_gameBoard.setPylon(line, column, pylon);
	m_pylons.push_back(pylon);
	setNrOfAvailablePylons(m_nrOfAvailablePylons - 1);
}

void twixt::Player::placeBridge(const Bridge& bridge)
{
	m_bridges.push_back(bridge);
	setNrOfAvailableBridges(m_nrOfAvailableBridges - 1);
}


int twixt::Player::getPositionPylonInVector(const Pylon& pylon)
{
	for (int index = 0; index < m_pylons.size();index++)
	{
		if (m_pylons[index] == pylon)
			return index;
	}
	return -1;
}
