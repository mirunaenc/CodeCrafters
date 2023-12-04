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

twixt::Player::Player(Player&& otherPlayer) noexcept
	: m_nrOfAvailablePylons{ otherPlayer.m_nrOfAvailablePylons },
	m_nrOfAvailableBridges{ otherPlayer.m_nrOfAvailableBridges },
	m_color{ otherPlayer.m_color }, m_pylons{ otherPlayer.m_pylons },
	m_bridges{ otherPlayer.m_bridges },
	m_gameBoard{ otherPlayer.m_gameBoard }
{}


twixt::Player& twixt::Player::operator=(Player&& otherPlayer) noexcept
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


twixt::EColor twixt::Player::getColor() const
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

const std::vector<twixt::Pylon*>& twixt::Player::getPylons() const
{
	return m_pylons;
}

void twixt::Player::setPylons(const std::vector<Pylon*>& pylons)
{
	m_pylons = pylons;
}

const std::vector<twixt::Bridge*>& twixt::Player::getBridges() const
{
	return m_bridges;
}

void twixt::Player::setBridges(const std::vector<Bridge*>& bridges)
{
	m_bridges = bridges;
}

void twixt::Player::placePylon(uint16_t line, uint16_t column)
{
	Pylon pylon(line, column);
	pylon.setColor(m_color);
	m_gameBoard.addPylon(line, column, pylon);
	//m_pylons.push_back(&pylon);
	setNrOfAvailablePylons(m_nrOfAvailablePylons - 1);
}

void twixt::Player::placeBridge(const Pylon& start,const Pylon& end)
{
	//Bridge bridge(start,end);
	//m_gameBoard.addBridge(bridge);
	//m_bridges.push_back(&bridge);  
	setNrOfAvailableBridges(m_nrOfAvailableBridges - 1);
}


int twixt::Player::getPositionPylonInVector(const Pylon* pylonPtr)
{
	auto it = std::find(m_pylons.begin(), m_pylons.end(), pylonPtr);

	if (it != m_pylons.end())
		return static_cast<int>(std::distance(m_pylons.begin(), it));
	else
		return -1;
}

bool twixt::Player::hasPylon(const Pylon* pylonPtr) const
{
	auto it = std::find(m_pylons.begin(), m_pylons.end(), pylonPtr);
	if(it != m_pylons.end())
		return true;
    return false;
}

bool twixt::Player::isWinner()
{
      if (hasWinningRoad())
		return true;
	return false;
}

void twixt::Player::removePylon(const Pylon* pylon)
{
	int index = getPositionPylonInVector(pylon);
	if (index != -1)
	{
		m_pylons.erase(m_pylons.begin() + index);
	}
}

bool twixt::Player::hasRoadDFS(uint16_t currentLine, uint16_t currentColumn, std::vector<bool>& visited)
{
	if (m_color == EColor::RED) 
			if (currentLine == m_gameBoard.getSize() - 1)
			return true; 
	else 	
		if (currentLine == m_gameBoard.getSize() - 2)
			return true; 	

	if(m_color == EColor::BLACK)
		if (currentColumn == m_gameBoard.getSize() - 1)
			return true; 
	else
		if (currentColumn == m_gameBoard.getSize() - 2)
			return true; 


	visited[currentLine * m_gameBoard.getSize() + currentColumn] = true;

	// Check all adjacent positions
	for (int i = -2; i <= 2; ++i) {
		for (int j = -2; j <= 2; ++j) {
			if (std::abs(i) + std::abs(j) == 3) { // Check only diagonally connected pylons
				uint16_t nextLine = currentLine + i;
				uint16_t nextColumn = currentColumn + j;

				if (m_gameBoard.isPositionInsideBoard(nextLine, nextColumn) &&
					!visited[nextLine * m_gameBoard.getSize() + nextColumn] &&
					m_gameBoard.getPylon(currentLine, currentColumn).has_value() &&
						m_gameBoard.getPylon(nextLine, nextColumn).has_value()
					&& m_gameBoard.existsBridgeBetweenPylons(m_gameBoard.getPylon(currentLine, currentColumn).value(), m_gameBoard.getPylon(nextLine, nextColumn).value())
					)				
				{
					if (hasRoadDFS(nextLine, nextColumn, visited)) 
						return true;
				}
			}
		}
	}

	return false;
}

bool twixt::Player::hasWinningRoad()
{
	std::vector<bool> visited(m_gameBoard.getSize() * m_gameBoard.getSize(), false);

	// Check for horizontal winning road
	if (m_color == EColor::BLACK) {
		for (uint16_t i = 0; i < m_gameBoard.getSize(); ++i) {
			if (visited[i * m_gameBoard.getSize() + 0] == false && hasRoadDFS(i, 0, visited))
				return true;
			
			if(visited[i * m_gameBoard.getSize() + 1] == false && hasRoadDFS(i, 1, visited))
				return true;
		}
	}

	// Check for vertical winning road
	if (m_color == EColor::RED) {
		for (uint16_t j = 0; j < m_gameBoard.getSize(); ++j) {
			if (visited[0 * m_gameBoard.getSize() + j] == false && hasRoadDFS(0, j, visited))
				return true;
			
			if(visited[1 * m_gameBoard.getSize() + j] == false && hasRoadDFS(1, j, visited))
				return true;
		}
	}
	return false;
}

void twixt::Player::makeMove()
{
	uint16_t line, column;
    std::cout << "Enter the line and column of the pylon you want to place: ";
	std::cin >> line >> column;
	placePylon(line, column);
}
