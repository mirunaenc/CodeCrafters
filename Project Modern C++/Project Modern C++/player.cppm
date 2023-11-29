export module player;
import <vector>;
import <optional>;
import <array>;
import <iostream>;
import pylon;
import bridge;
import board;
import utility;

namespace twixt {
	
	export class Player {

	public:
		/*enum class EColor : uint8_t
		{
			RED,
			BLACK
		};*/
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
		Player(Player&& otherPlayer) noexcept;
        Player& operator=(Player&& otherPlayer) noexcept;
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

		void placePylon(uint16_t line, uint16_t column);
	
		void placeBridge(const Bridge& bridge);

		int getPositionPylonInVector(const Pylon& pylon);


		bool hasPylon(const Pylon& pylon) const;

		bool isWinner();

		void removePylon(const Pylon& pylon);

		bool hasRoadDFS(uint16_t currentLine, uint16_t currentColumn, std::vector<bool>& visited);

		bool hasWinningRoad();

		void makeMove();
	};	
}