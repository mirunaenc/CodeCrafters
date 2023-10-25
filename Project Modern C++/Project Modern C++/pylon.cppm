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
		void setLine();
		void setColumn();
		uint16_t getLine () const;
		uint16_t getColumn() const;
	};
}
