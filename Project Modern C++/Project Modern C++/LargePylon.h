#pragma once
import pylon;
#include <vector>;

namespace twixt {
	class LargePylon : public Pylon
	{
	private:
		std::vector<std::pair<uint16_t, uint16_t>> m_shape;
		std::vector<std::pair<uint16_t, uint16_t>> m_vertices;

	public:
		LargePylon(uint16_t line, uint16_t column, const std::vector<std::pair<uint16_t, 
			uint16_t>>& shape, const std::vector<std::pair<uint16_t, uint16_t>>& vertices);
		const std::vector<std::pair<uint16_t, uint16_t>>& getShape() const;
		bool isSymmetric();
	};

}