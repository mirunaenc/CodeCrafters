#include <cstdint>

export module board;
import <array>;
import pylon;
import <optional>;
import <vector>;

namespace twixt {
	export class Board {

	private:
		uint16_t m_size;
		std::vector<Pylon> m_board;
	public:
		Board(uint16_t size);

		Board& operator=(const Board& board);

		Board(const Board& board);

		uint16_t getSize() const;

		void setSize(uint16_t size);

		void setPylon(uint16_t line, uint16_t column, const Pylon& pylon);

		const Pylon& getPylon(uint16_t line, uint16_t column) const;

		void resetPosition(uint16_t line, uint16_t column);
	};
}