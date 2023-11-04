export module player;

import pylon;
import bridge;
import board;
import <vector>;
import <optional>;
import <array>;



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
		Board& m_gameBoard;

	public:
		Player(uint16_t nrPylons, uint16_t nrBridges, EColor color,Board& gameBoard);
		Player(const Player& otherPlayer);
        Player& operator=(const Player& otherPlayer);
		~Player();
		
		uint16_t getNrOfAvailablePylons() const;
		void setNrOfAvailablePylons(uint16_t nrPylons);
		
		uint16_t getNrOfAvailableBridges() const;
		void setNrOfAvailableBridges(uint16_t nrBridges);

		EColor getColor() const;
		void setColor(const EColor& color);

		const Board& getGameBoard() const;
		void setGameBoard(const Board& gameBoard);

		const std::vector<Pylon>& getPylons() const;
		void setPylons(const std::vector<Pylon>& pylons);

		const std::vector<Bridge>& getBridges() const;
		void setBridges(const std::vector<Bridge>& bridges);







	};	
}