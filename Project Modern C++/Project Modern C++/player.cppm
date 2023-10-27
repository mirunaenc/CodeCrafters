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
		std::vector<Bridge> m_bridges;

	public:
		Player(uint16_t nrPylons, uint16_t nrBridges, EColor color);
		Player(const Player& player);
        Player& operator=(const Player& player);
		~Player();
		
		uint16_t getNrOfAvailablePylons() const;
		void setNrOfAvailablePylons(const uint16_t& nrPylons);
		
		uint16_t getNrOfAvailableBridges() const;
		void setNrOfAvailableBridges(const uint16_t& nrBridges);

		EColor getColor() const;
		void setColor(const EColor& color);

	};	
}