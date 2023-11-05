module board;

import <iostream>;
import <algorithm>;
import <iterator>;
import <vector>;
import pylon;

twixt::Board::Board(uint16_t size) : m_size{ size } {
	m_board.resize(m_size);
}

twixt::Board& twixt::Board::operator=(const Board& board)
{
    if (this != &board) {
        m_size = board.m_size;
        m_board.resize(m_size);
        std::copy(board.m_board.begin(), board.m_board.end(), back_inserter(m_board));
    }
    return *this;
}

twixt::Board::Board(const Board& board) : m_size{ board.m_size } {
        m_board.resize(m_size);
        std::copy(board.m_board.begin(), board.m_board.end(), back_inserter(m_board));
}

uint16_t twixt::Board::getSize() const {
    return m_size;
}

void twixt::Board::setSize(uint16_t size) {
    m_size = size;
    m_board.resize(m_size);
}

void twixt::Board::setPylon(uint16_t line, uint16_t column, const Pylon& pylon) {
    if (line < m_size && column < m_size) {
        m_board[line * m_size + column] = pylon;
    }
    else {
        std::cout << "Error at setting a pylon.";
        exit(0);
    }
}

const twixt::Pylon& twixt::Board::getPylon(uint16_t line, uint16_t column) const {
    if (line < m_size && column < m_size) {
        return m_board[line * m_size + column];
    }
    else {
        std::cout << "Error at method getPylon.";
        exit(0);
    }
}

void twixt::Board::resetPosition(uint16_t line, uint16_t column) {
    if (line < m_size && column < m_size) {
        m_board[line * m_size + column] = null;
    }
}





