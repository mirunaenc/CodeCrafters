#include "player.h"


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
	m_gameBoard.placePylon(line, column, m_color);
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
      if (m_gameBoard.hasWinningRoad() == this->getColor() )
		return true;
	return false;
}

void twixt::Player::makeMove()
{
	getUserInputAndPlacePylon();
	updateBridges();
}

void twixt::Player::savePlayerState(std::ofstream& file) const
{
	file << m_nrOfAvailablePylons << "\n";
	file << m_nrOfAvailableBridges << "\n";
	file << static_cast<int>(m_color) << "\n";
}

void twixt::Player::loadPlayerState(std::ifstream& file)
{
	try {
		std::string line;

		if (std::getline(file, line)) {
			m_nrOfAvailablePylons = std::stoi(line);
		}

		if (std::getline(file, line)) {
			m_nrOfAvailableBridges = std::stoi(line);
		}

		if (std::getline(file, line)) {
			m_color = static_cast<EColor>(std::stoi(line));
		}

	}
	catch (const std::exception& e) {
		std::cerr << "Eroare la incarcarea starii jucatorului: " << e.what() << std::endl;
	}
}

bool twixt::Player::positionIsNotCorner(uint16_t line, uint16_t column)
{
	if(line == 0 && column == 0)
		return false;
	if(line == 0 && column == m_gameBoard.getSize() - 1)
		return false;
    if(line == m_gameBoard.getSize() - 1 && column == 0)
		return false;
    if(line == m_gameBoard.getSize() - 1 && column == m_gameBoard.getSize() - 1)
		return false;
	return true;
}

bool twixt::Player::positionIsEnemySide(uint16_t line, uint16_t column)
{
	if(m_color == EColor::RED)
	{
		if(column == 0 || column == m_gameBoard.getSize() - 1)
			return true;
	}
	else if(m_color == EColor::BLACK)
	{
		  if(line == 0 || line == m_gameBoard.getSize() - 1)
            return true;
	}
	return false;
}

void twixt::Player::getUserInputAndPlacePylon()
{
	uint16_t line, column;

	std::cout << "Enter the line and column of the pylon you want to place: ";
	std::cin >> line >> column;

	while (m_gameBoard.getPylon(line, column).has_value() || !positionIsNotCorner(line, column) || positionIsEnemySide(line, column)) {
		std::cout << "Invalid position! Type the values again!" << std::endl;
		std::cout << "Enter the line and column of the pylon you want to place: ";
		std::cin >> line >> column;
	}

	placePylon(line, column);
}

void twixt::Player::updateBridges()
{
	std::cout << "Do you want to update the bridges? (y/n)";
	char answer;
	std::cin >> answer;
	while (answer == 'y')
	{
		std::cout << "Enter the line and column of the start pylon: ";
		uint16_t line, column;
		std::cin >> line >> column;
		std::cout << "Enter the line and column of the end pylon: ";
		uint16_t line2, column2;
		std::cin >> line2 >> column2;

		if (m_gameBoard.getPylon(line, column).has_value() && m_gameBoard.getPylon(line2, column2).has_value())
		{
			if (m_gameBoard.existsBridgeBetweenPylons(m_gameBoard.getPylon(line, column).value(),
				m_gameBoard.getPylon(line2, column2).value()))
			{
				// to do: remove bridge , primeste 2 piloni ,si da erase la bridge ul care este intre cei 2 piloni 
			 
			} 
			else
				placeBridge(m_gameBoard.getPylon(line, column).value(), m_gameBoard.getPylon(line2, column2).value());
		
			//Bridge* bridge = new Bridge(m_gameBoard.getPylon(line, column).value(), m_gameBoard.getPylon(line2, column2).value());
			//m_gameBoard.addBridge(*bridge);

		}

		std::cout << "Do you still want to update the bridges? (y/n)";
		std::cin >> answer;
	}
}
