export module pylon;
import <set>;
import <iostream>;
import utility;

namespace twixt {
	export class Pylon {
		
	private:
		uint16_t m_line;
		uint16_t m_column;
		EColor m_color;

	public:
		
		Pylon(uint16_t line=0, uint16_t column=0);
		void setLine(uint16_t line);
		void setColumn(uint16_t column);
		void setColor(EColor color);
		uint16_t getLine () const;
		uint16_t getColumn() const;
		EColor getColor() const;
		bool operator==(const Pylon& other) const;
		virtual ~Pylon();
		bool operator==(const Pylon* pylonPtr2);
	};
}
