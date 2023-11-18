#pragma once
import pylon;
#include <vector>;

namespace twixt {
	class LargePylon : public Pylon
	{
	private:
		std::vector<std::pair<uint16_t, uint16_t>> m_shape;
	public:
		LargePylon(uint16_t line = 0, uint16_t column = 0, const std::vector<std::pair<uint16_t, uint16_t>>& shape);
		const std::vector<std::pair<uint16_t, uint16_t>>& getShape() const;
	};

}