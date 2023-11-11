#include <cstdint>

export module board;
import <array>;
import <optional>;
import <vector>;
import pylon;

namespace twixt {
	export class Board {

	private:
		uint16_t m_size;
		std::optional<std::vector<Pylon>> m_board;
	public:
		Board(uint16_t size);
		Board(const Board& board);
		Board& operator=(const Board& board);
		uint16_t getSize() const;
		void setSize(uint16_t size);
		void setPylon(uint16_t line, uint16_t column, const Pylon& pylon);
		const Pylon& getPylon(uint16_t line, uint16_t column) const;
		void resetPosition(uint16_t line, uint16_t column);
	};
}