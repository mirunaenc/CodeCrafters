#include <cstdint>

export module board;
import <vector>;
import <optional>;
import <algorithm>;
import <iostream>;
import pylon;
import bridge;

namespace twixt {
	export class Board {

	private:
		uint16_t m_size;
		std::vector<std::optional<Pylon>> m_boardPylons;
		std::vector<std::optional<Bridge>> m_boardBridges;
	public:
		Board();
		Board(uint16_t size);
		Board(const Board& board);
		Board(Board&& board) noexcept;
		Board& operator=(const Board& board);
		Board& operator=(Board&& board) noexcept;
		uint16_t getSize() const;
		void setSize(uint16_t size);
		void addPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon);
		void addBridge(Pylon& start, Pylon& end);
		const std::optional<Pylon>& getPylon(uint16_t line, uint16_t column) const;
		void resetPosition(uint16_t line, uint16_t column);
		bool isPositionInsideBoard(const Pylon& pylon) const;
		void removeBridge(const Bridge& bridge);
		void provisionalPrint();
		const std::vector<std::optional<Pylon>>& getPylons() const;
		const std::vector<std::optional<Bridge>>& getBridges() const;
		bool isValidBridge(const Pylon& start, const Pylon& end);
		void resetBoard();
	};
}