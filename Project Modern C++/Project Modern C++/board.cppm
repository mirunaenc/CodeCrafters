module;

#include <cstdint>

export module board;
import <array>;
import pylon;
import <optional>;
import <vector>;

namespace twixt {
	export class Board {

	private:
		const uint16_t m_size;
		std::vector<Pylon> m_board;
	public:
		Board(uint16_t m_size);
	};
}