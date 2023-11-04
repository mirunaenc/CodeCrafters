module board;

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

void twixt::Board::setPylon(uint16_t x, uint16_t y, const Pylon& pylon) {
    if (x < m_size && y < m_size) {
        m_board[y * m_size + x] = pylon;
    }
    else {
        std::cout << "Error at setting a pylon.";
        exit(0);
    }
}





