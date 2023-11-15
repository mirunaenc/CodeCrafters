
#include "bulldozer.h"

namespace twixt {

    Bulldozer::Bulldozer(Board& board, size_t initialLinePosition, size_t initialColumnPosition, float biasedCoinProbability)
        : m_board{ board }, m_linePosition{ initialLinePosition }, m_columnPosition{ initialColumnPosition },
        m_biasedCoinProbability{ biasedCoinProbability }, m_rng(m_rd()) {}

    Bulldozer::Bulldozer(const Bulldozer& other)
        : m_board{ other.m_board }, m_linePosition{ other.m_linePosition }, m_columnPosition{ other.m_columnPosition },
        m_biasedCoinProbability{ other.m_biasedCoinProbability }, m_rng(m_rd()) {}


    Bulldozer::Bulldozer(Bulldozer&& other) noexcept
        : m_board{other.m_board}, m_linePosition{ other.m_linePosition }, m_columnPosition{ other.m_columnPosition },
        m_biasedCoinProbability{ other.m_biasedCoinProbability },m_rng(m_rd()) {
   }

    Bulldozer& Bulldozer::operator=(const Bulldozer& other) {
        if (this != &other) {
            m_board = other.m_board; 
            m_linePosition = other.m_linePosition;
            m_columnPosition = other.m_columnPosition;
            m_biasedCoinProbability = other.m_biasedCoinProbability;
        }
        return *this;
    }
    Bulldozer& Bulldozer::operator=(Bulldozer&& other) noexcept {
        if (this != &other) {
            m_board = other.m_board;  // because Board has a proper move assignment operator
            m_linePosition = other.m_linePosition;
            m_columnPosition = other.m_columnPosition;
  		  m_biasedCoinProbability = other.m_biasedCoinProbability;
        }
        return *this;
    }

    Bulldozer::~Bulldozer() {
   
    }

    size_t Bulldozer::getLinePosition() const {
        return m_linePosition;
    }

    size_t Bulldozer::getColumnPosition() const {
        return m_columnPosition;
    }

    void Bulldozer::setLinePosition(size_t linePosition) {
        m_linePosition = linePosition;
    }

    void Bulldozer::setColumnPosition(size_t columnPosition) {
        m_columnPosition = columnPosition;
    }

    bool Bulldozer::tossCoin()
    {
        std::uniform_real_distribution<float> distribution(0.0, 1.0);
        float randomValue = distribution(m_rng);
        return randomValue < m_biasedCoinProbability;    
    }

    const float Bulldozer::getBiasedCoinProbability() const
    {
        return m_biasedCoinProbability;
    }

    void Bulldozer::setBiasedCoinProbability(float biasedCoinProbability)
    {
        m_biasedCoinProbability = biasedCoinProbability;
    }

    void Bulldozer::moveToEmptyPosition()
    {
        std::vector<twixt::Position> emptyPositions;
        
          for (size_t line = 0; line < m_board.getSize(); ++line) 
          {
			for (size_t column = 0; column < m_board.getSize(); ++column)
            {
				 if (!m_board.getPylons()[line * m_board.getSize() + column].has_value())
		        	emptyPositions.push_back(twixt::Position{ line, column });			    
			}
		  }
        std::uniform_int_distribution<size_t> distribution(0, emptyPositions.size() - 1);
		size_t randomIndex = distribution(m_rng);

        setLinePosition(emptyPositions[randomIndex].first);
        setColumnPosition(emptyPositions[randomIndex].second);
    }

}
