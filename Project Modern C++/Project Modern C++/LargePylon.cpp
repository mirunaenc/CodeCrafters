#include "LargePylon.h"

twixt::LargePylon::LargePylon(uint16_t line, uint16_t column, const std::vector<std::pair<uint16_t, uint16_t>>& shape) : Pylon{line, column}, m_shape{shape} 
{
}

const std::vector<std::pair<uint16_t, uint16_t>>& twixt::LargePylon::getShape() const
{
	return m_shape;
}
