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

uint16_t twixt::Player::getNrOfAvailablePylons() const
{
	return m_nrOfAvailablePylons;
}

void twixt::Player::setNrOfAvailablePylons(const uint16_t& nrPylons)
{
	m_nrOfAvailablePylons = nrPylons;
}
