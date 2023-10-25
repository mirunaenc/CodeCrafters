module;

#include <cstdint>;

export module pylon;
import <iostream>;

namespace twixt {
	export class Pylon {

	private:
		uint16_t m_line;
		uint16_t m_column;
	public:
		Pylon(uint16_t line, uint16_t column);
		void setLine(const uint16_t& line);
		void setColumn(const uint16_t& column);
		uint16_t getLine () const;
		uint16_t getColumn() const;
	};
}
