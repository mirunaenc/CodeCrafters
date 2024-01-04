#pragma once
#include <random>
#include <vector>
#include "board.h"
#include "pylon.h"
#include "player.h"

namespace twixt {

    using Position = std::pair<uint16_t, uint16_t>;

    class Bulldozer {
    
    private:
        size_t m_linePosition;
        size_t m_columnPosition;
        Board& m_board;
        std::mt19937 m_rng;
        float m_biasedCoinProbability;

    public:
        Bulldozer(Board& board, size_t initialLinePosition, size_t initialColumnPosition, float biasedCoinProbability);
        Bulldozer(const Bulldozer& other);  
        Bulldozer(Bulldozer&& other) noexcept; 
        Bulldozer& operator=(const Bulldozer& other); 
        Bulldozer& operator=(Bulldozer&& other) noexcept;  
        ~Bulldozer();

        size_t getLinePosition() const;
        size_t getColumnPosition() const;
        void setLinePosition(size_t linePosition);
        void setColumnPosition(size_t columnPosition);

        bool tossCoin();
        const float getBiasedCoinProbability() const;
        void setBiasedCoinProbability(float biasedCoinProbability);
        void moveToEmptyPosition();
        void destroyPylon();
        void playTurn();
    };

}