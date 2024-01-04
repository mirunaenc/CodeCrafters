#pragma once
#include <set>
#include <iostream>
#include "utility.h"

namespace twixt {
	 class Pylon {

	private:
		uint16_t m_line;
		uint16_t m_column;
		EColor m_color;

	public:

		Pylon(uint16_t line, uint16_t column);
		void setLine(uint16_t line);
		void setColumn(uint16_t column);
		void setColor(EColor color);
		uint16_t getLine() const;
		uint16_t getColumn() const;
		EColor getColor() const;
		bool operator==(const Pylon& other) const;
		virtual ~Pylon();
		bool operator==(const Pylon* pylonPtr2);
	};
}
