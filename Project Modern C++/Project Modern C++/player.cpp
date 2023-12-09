module player;


twixt::Player::Player(uint16_t nrPylons, uint16_t nrBridges, EColor color, Board& gameBoard)
	: m_nrOfAvailablePylons{ nrPylons }, m_nrOfAvailableBridges{ nrBridges }, m_color{ color }, m_gameBoard(gameBoard)
{}

twixt::Player& twixt::Player::operator=(Player&& otherPlayer) noexcept
{
	if (this != &otherPlayer) {
		m_nrOfAvailablePylons = otherPlayer.m_nrOfAvailablePylons;
		m_nrOfAvailableBridges = otherPlayer.m_nrOfAvailableBridges;
		m_color = otherPlayer.m_color;
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

const twixt::Board& twixt::Player::getGameBoard() const 
{
	return m_gameBoard;
}

void twixt::Player::setGameBoard(const Board& gameBoard) 
{
	m_gameBoard = gameBoard;
}


void twixt::Player::placePylon(uint16_t line, uint16_t column)
{
	Pylon* pylon = new Pylon(line, column);
	pylon->setColor(m_color);

	std::optional<Pylon> optionalPylon = *pylon;

	m_gameBoard.addPylon(line, column, optionalPylon);
	if(optionalPylon.has_value())
		m_gameBoard.createBridge(optionalPylon);

	setNrOfAvailablePylons(m_nrOfAvailablePylons - 1);
}

void twixt::Player::placeBridge(const Pylon& start,const Pylon& end)
{
	//Bridge bridge(start,end);
	//m_gameBoard.addBridge(bridge);
	setNrOfAvailableBridges(m_nrOfAvailableBridges - 1);
}


bool twixt::Player::isWinner()
{
      if (hasWinningRoad())
		return true;
	return false;
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
	std::cout<<"Do you want to update the bridges? (y/n)";
	char answer;
	std::cin>>answer;
	while (answer == 'y')
	{
		std::cout << "Enter the line and column of the start pylon: ";
		size_t line, column;
		std::cin >>line>>column;
std::cout << "Enter the line and column of the end pylon: ";
		size_t line2, column2;
		std::cin >>line2>>column2;

		if (m_gameBoard.getPylon(line, column).has_value() && m_gameBoard.getPylon(line2, column2).has_value())
		{
			if(m_gameBoard.existsBridgeBetweenPylons(m_gameBoard.getPylon(line, column).value(),
				m_gameBoard.getPylon(line2, column2).value()))
				
				placeBridge(m_gameBoard.getPylon(line, column).value(), m_gameBoard.getPylon(line2, column2).value())
		}
		
		m_gameBoard.getPylon(line, column).value();
		
	   

		std::cout<<"Do you still want to update the bridges? (y/n)";
		std::cin>>answer;
	}
}
