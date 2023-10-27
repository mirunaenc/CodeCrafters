module board;

import <algorithm>;
import <iterator>;

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