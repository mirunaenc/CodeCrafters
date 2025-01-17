#pragma once
#include <vector>
#include "pylon.h"

namespace twixt {
	class LargePylon : public Pylon
	{
	private:
		std::vector<std::pair<uint16_t, uint16_t>> m_shape;
		std::vector<std::pair<uint16_t, uint16_t>> m_vertices;

	public:
		LargePylon(uint16_t line, uint16_t column, const std::vector<std::pair<uint16_t, 
			uint16_t>>& shape, const std::vector<std::pair<uint16_t, uint16_t>>& vertices);
		LargePylon(uint16_t line, uint16_t column, std::vector<std::pair<uint16_t, uint16_t>>&& shape,
			std::vector<std::pair<uint16_t, uint16_t>>&& vertices) noexcept;
		LargePylon& operator=(LargePylon&& other) noexcept;

		const std::vector<std::pair<uint16_t, uint16_t>>& getShape() const;
		bool isSymmetric();
		bool isValidShape() const;
		void setShape(const std::vector<std::pair<uint16_t, uint16_t>>& shape);
		bool hasTwoVerticesOnOneSide() const;

	};

}