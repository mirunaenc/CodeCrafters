
#include <cstdint>;
#include <set>

export module pylon;
import <iostream>;

namespace twixt {
	export class Pylon {
		
	private:
		uint16_t m_line;
		uint16_t m_column;

	public:
		
		Pylon(uint16_t line=0, uint16_t column=0);
		void setLine(uint16_t line);
		void setColumn(uint16_t column);
		uint16_t getLine () const;
		uint16_t getColumn() const;
		Pylon(const Pylon& pylon);
		Pylon& operator=(const Pylon& pylon);
		bool operator==(const Pylon& other) const;
		Pylon(Pylon&& other) noexcept;
		Pylon& operator=(Pylon&& other) noexcept;
		~Pylon();
	};
}
