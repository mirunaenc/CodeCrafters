import <algorithm>;
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

bool twixt::LargePylon::isValidShape() const
{
    if (m_shape.size() == 4) {

        std::vector<std::pair<uint16_t, uint16_t>> sortedShape = m_shape;
        std::sort(sortedShape.begin(), sortedShape.end());

        if (sortedShape[0].first == sortedShape[1].first && sortedShape[0].second + 1 == sortedShape[1].second &&
            sortedShape[0].first + 1 == sortedShape[2].first && sortedShape[0].second == sortedShape[2].second &&
            sortedShape[2].first == sortedShape[3].first && sortedShape[2].second + 1 == sortedShape[3].second) {
            return true;
        }
    }
    else if (m_shape.size() == 5) {
        std::vector<std::pair<uint16_t, uint16_t>> sortedShape = m_shape;
        std::sort(sortedShape.begin(), sortedShape.end());

        if (sortedShape[1].first == sortedShape[2].first && sortedShape[1].second + 1 == sortedShape[2].second &&
            sortedShape[2].second + 1 == sortedShape[3].second &&
            sortedShape[0].first + 1 == sortedShape[2].first && sortedShape[0].second == sortedShape[2].second &&
            sortedShape[2].first + 1 == sortedShape[4].first && sortedShape[2].second == sortedShape[4].second) {
            return true;
        }
    }
    return false;
}

void twixt::LargePylon::setShape(const std::vector<std::pair<uint16_t, uint16_t>>& shape) {
    m_shape = shape;
    if (!isValidShape()) {
        throw std::invalid_argument("Forma furnizata nu este valida!");
    }
}

bool twixt::LargePylon::hasTwoVerticesOnOneSide() const {
   
    int verticesTop = 0, verticesBottom = 0, verticesLeft = 0, verticesRight = 0;

    // determinam limitele formei pilonului
    auto [minX, maxX, minY, maxY] = std::tuple{ m_shape[0].first, m_shape[0].first, m_shape[0].second, m_shape[0].second };
    for (const auto& point : m_shape) {
        minX = std::min(minX, point.first);
        maxX = std::max(maxX, point.first);
        minY = std::min(minY, point.second);
        maxY = std::max(maxY, point.second);
    }

    // verif fiecare varf pentru a determina pe ce latura se afla
    for (const auto& vertice : m_vertices) {
        if (vertice.second == minY) verticesBottom++;
        if (vertice.second == maxY) verticesTop++;
        if (vertice.first == minX) verticesLeft++;
        if (vertice.first == maxX) verticesRight++;
    }

    // verif daca exista exact doua varfuri pe o singura latura
    return (verticesTop == 2 && verticesBottom == 0 && verticesLeft == 0 && verticesRight == 0) ||
        (verticesTop == 0 && verticesBottom == 2 && verticesLeft == 0 && verticesRight == 0) ||
        (verticesTop == 0 && verticesBottom == 0 && verticesLeft == 2 && verticesRight == 0) ||
        (verticesTop == 0 && verticesBottom == 0 && verticesLeft == 0 && verticesRight == 2);
}