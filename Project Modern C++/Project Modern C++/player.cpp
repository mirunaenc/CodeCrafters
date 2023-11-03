module player;

twixt::Player::Player(uint16_t nrPylons, uint16_t nrBridges, EColor color) 
	: m_nrOfAvailablePylons{ nrPylons }, m_nrOfAvailableBridges{ nrBridges }, m_color{ color }
{}

twixt::Player::Player(const Player& player)
	: m_nrOfAvailablePylons{player.m_nrOfAvailablePylons},
	m_nrOfAvailableBridges{player.m_nrOfAvailableBridges},
	m_color{player.m_color},m_pylons{player.m_pylons},
	m_bridges{player.m_bridges}
{}

twixt::Player& twixt::Player::operator=(const Player& player)
{
	if (this != &player) {
		m_nrOfAvailablePylons = player.m_nrOfAvailablePylons;
		m_nrOfAvailableBridges = player.m_nrOfAvailableBridges;
		m_color = player.m_color;
		m_pylons = player.m_pylons;
		m_bridges = player.m_bridges;
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


