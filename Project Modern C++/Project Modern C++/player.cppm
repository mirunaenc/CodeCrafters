module;

export module player;

import pylon;
import bridge;
import <vector>;



namespace twixt {
	

	export class Player {

	public:
		enum class EColor : uint8_t
		{
			Red,
			Black
		};
	private:
		uint16_t m_nrOfAvailablePylons;
		uint16_t m_nrOfAvailableBridges;
		EColor m_color;
		std::vector<Pylon> m_pylons;
		std::vector<Bridge> m_bridge;

	public:
		Player(uint16_t nrPylons, uint16_t nrBridges, EColor color);

	};	
}