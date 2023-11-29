import "LargePylon.h";

twixt::LargePylon::LargePylon(uint16_t line, uint16_t column, const std::vector<std::pair<uint16_t, uint16_t>>& shape,
    const std::vector<std::pair<uint16_t, uint16_t>>& vertices) : Pylon{line, column}, m_shape{shape}, m_vertices{ vertices } {
    if (!isSymmetric()) {
        throw std::invalid_argument("Peaks are not symmetric!");
    }
}

const std::vector<std::pair<uint16_t, uint16_t>>& twixt::LargePylon::getShape() const
{
	return m_shape;
}

bool twixt::LargePylon::isSymmetric()
{
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        uint16_t oppositeX = m_shape[i].first - (m_vertices[i].first - m_shape[i].first);
        uint16_t oppositeY = m_shape[i].second - (m_vertices[i].second - m_shape[i].second);

        auto oppositePair = std::make_pair(oppositeX, oppositeY);
        if (std::find(m_vertices.begin(), m_vertices.end(), oppositePair) == m_vertices.end()) {
            return false; 
        }
    }
    return true; 
}