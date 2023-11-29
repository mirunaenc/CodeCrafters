#pragma once
import <random>;
import <vector>;
import board;
import pylon;
import player;

namespace twixt {

    using Position = std::pair<uint16_t, uint16_t>;

    class Bulldozer {
    
    private:
        size_t m_linePosition;
        size_t m_columnPosition;
        Board& m_board;
        std::random_device m_rd;
        std::mt19937 m_rng;
        float m_biasedCoinProbability;
        Player& m_player1;
        Player& m_player2;

    public:
        Bulldozer(Board& board, size_t initialLinePosition, size_t initialColumnPosition, float biasedCoinProbability,
       Player& player1, Player& player2);
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