#pragma once
import board;
import pylon;


namespace twixt {

    class Bulldozer {
    private:
        size_t m_linePosition;
        size_t m_columnPosition;
        Board& m_board;

    public:
        Bulldozer(Board& board, size_t initialLinePosition, size_t initialColumnPosition);
        Bulldozer(const Bulldozer& other);  
        Bulldozer(Bulldozer&& other) noexcept; 
        Bulldozer& operator=(const Bulldozer& other); 
        Bulldozer& operator=(Bulldozer&& other) noexcept;  
        ~Bulldozer();

        size_t getLinePosition() const;
        size_t getColumnPosition() const;
        void setLinePosition(size_t linePosition);
        void setColumnPosition(size_t columnPosition);
    };

}