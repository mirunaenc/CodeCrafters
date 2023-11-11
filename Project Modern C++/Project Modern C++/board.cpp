module board;

import <iostream>;
import <algorithm>;
import <iterator>;
import <vector>;
import <optional>;
import pylon;

twixt::Board::Board(uint16_t size) : m_size{ size } {
    m_board = std::vector<Pylon>(size * size);
}

twixt::Board::Board(const Board& board) : m_size{ board.m_size }, m_board{ board.m_board } 
{}

twixt::Board::Board(Board&& board) noexcept : m_size{ board.m_size }, m_board{ board.m_board }
{}

twixt::Board& twixt::Board::operator=(const Board & board)
{
    if (m_board != board.m_board) {
        m_size = board.m_size;
        m_board = board.m_board;
    }
}

twixt::Board& twixt::Board::operator=(Board&& board) noexcept
{
    if (m_board != board.m_board) {
        m_size = board.m_size;
        m_board = board.m_board;
    }
}

uint16_t twixt::Board::getSize() const {
    return m_size;
}

void twixt::Board::setSize(uint16_t size) {
    m_size = size;
    m_board = std::vector<Pylon>(size * size);
}

void twixt::Board::setPylon(uint16_t line, uint16_t column, const Pylon& pylon) {
    if (line < m_size && column < m_size) {
        m_board.value()[line * m_size + column] = pylon;
    }
    else {
        std::cout << "Error at setting a pylon.";
        exit(0);
    }
}

const twixt::Pylon& twixt::Board::getPylon(uint16_t line, uint16_t column) const {
    if (line < m_size && column < m_size) {
        return m_board.value()[line * m_size + column];
    }
    else {
        std::cout << "Error at method getPylon.";
        return Pylon{};
    }
}

void twixt::Board::resetPosition(uint16_t line, uint16_t column) {
    if (line < m_size && column < m_size) {
        m_board.value()[line * m_size + column] = Pylon{};
    }
}