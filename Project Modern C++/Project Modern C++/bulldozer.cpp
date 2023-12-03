import "bulldozer.h";

namespace twixt {

    Bulldozer::Bulldozer(Board& board, size_t initialLinePosition, size_t initialColumnPosition, float biasedCoinProbability,
        Player& player1, Player& player2)
        : m_board{ board }, m_linePosition{ initialLinePosition }, m_columnPosition{ initialColumnPosition },
        m_biasedCoinProbability{ biasedCoinProbability },  m_player1{ player1 }, m_player2{player2} 
    {
        std::random_device m_rd;
        m_rng.seed(m_rd());
    }

    Bulldozer::Bulldozer(const Bulldozer& other)
        : m_board{ other.m_board }, m_linePosition{ other.m_linePosition }, m_columnPosition{ other.m_columnPosition },
        m_biasedCoinProbability{ other.m_biasedCoinProbability },  m_player1{ other.m_player1 }, m_player2{ other.m_player2 } 
    {
        std::random_device m_rd;
        m_rng.seed(m_rd());
    }


    Bulldozer::Bulldozer(Bulldozer&& other) noexcept
        : m_board{other.m_board}, m_linePosition{ other.m_linePosition }, m_columnPosition{ other.m_columnPosition },
        m_biasedCoinProbability{ other.m_biasedCoinProbability }, m_player1{ other.m_player1 }, m_player2{ other.m_player2 } 
    {
		std::random_device m_rd;
        m_rng.seed(m_rd());
    }

    Bulldozer& Bulldozer::operator=(const Bulldozer& other) {
        if (this != &other) {
            m_board = other.m_board; 
            m_linePosition = other.m_linePosition;
            m_columnPosition = other.m_columnPosition;
            m_biasedCoinProbability = other.m_biasedCoinProbability;
            m_player1 = other.m_player1;
            m_player2 = other.m_player2;
        }
        return *this;
    }
    Bulldozer& Bulldozer::operator=(Bulldozer&& other) noexcept {
        if (this != &other) {
            m_board = other.m_board;  // because Board has a proper move assignment operator
            m_linePosition = other.m_linePosition;
            m_columnPosition = other.m_columnPosition;
  		  m_biasedCoinProbability = other.m_biasedCoinProbability;
			m_player1 = other.m_player1;
			m_player2 = other.m_player2;
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
        
          for (uint16_t line = 0; line < m_board.getSize(); ++line)
          {
			for (uint16_t column = 0; column < m_board.getSize(); ++column)
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

    void Bulldozer::destroyPylon()
    {
        std::vector<twixt::Position> occupiedPositions;

        for (uint16_t line = 0; line < m_board.getSize(); ++line)
        {
            for (uint16_t column = 0; column < m_board.getSize(); ++column)
            {
                if (m_board.getPylons()[line * m_board.getSize() + column].has_value())
                    occupiedPositions.push_back(twixt::Position{ line, column });
            }
        }

        if(occupiedPositions.size() == 0)
			return;

        std::uniform_int_distribution<size_t> distribution(0, occupiedPositions.size() - 1);
        size_t randomIndex = distribution(m_rng);

        Pylon pylon = m_board.getPylon(occupiedPositions[randomIndex].first, occupiedPositions[randomIndex].second).value();     
      
        if(m_player1.hasPylon(&pylon))
			m_player1.removePylon(&pylon);
		else
			m_player2.removePylon(&pylon);

        m_board.resetPosition(occupiedPositions[randomIndex].first, occupiedPositions[randomIndex].second);

        setLinePosition(occupiedPositions[randomIndex].first);
        setColumnPosition(occupiedPositions[randomIndex].second);
    }

    void Bulldozer::playTurn()
    {
		if (tossCoin())
			destroyPylon();
		else
			moveToEmptyPosition();
    }

}
