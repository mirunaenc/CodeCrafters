module player;

twixt::Player::Player(uint16_t nrPylons, uint16_t nrBridges, EColor color) 
	: m_nrOfAvailablePylons{ nrPylons }, m_nrOfAvailableBridges{ nrBridges }, m_color{ color }
{}
