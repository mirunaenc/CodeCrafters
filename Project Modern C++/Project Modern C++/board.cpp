module board;


twixt::Board::Board()
{
}

twixt::Board::Board(uint16_t size) : m_size{ size } {
    m_board.resize(m_size * m_size);
}

twixt::Board::Board(const Board& board) : m_size{ board.m_size } {
    m_board.resize(m_size * m_size);
    std::copy(board.m_board.begin(), board.m_board.end(), m_board.begin());
}

twixt::Board::Board(Board&& board) noexcept : m_size{ board.m_size } {
    m_board.resize(m_size * m_size);
    m_board = std::move(board.m_board);
}


twixt::Board& twixt::Board::operator=(const Board& board)
{
    if (this != &board) {
        m_size = board.m_size;
        m_board.resize(m_size * m_size);
        std::copy(board.m_board.begin(), board.m_board.end(), m_board.begin());
    }
    return *this;
}


twixt::Board& twixt::Board::operator=(Board&& board) noexcept
{
	if (this != &board) {
		m_size = board.m_size;
		m_board.resize(m_size * m_size);
		m_board = std::move(board.m_board);
	}
	return *this;
}

uint16_t twixt::Board::getSize() const {
    return m_size;
}

void twixt::Board::setSize(uint16_t size) {
    m_size = size;
    m_board.resize(m_size * m_size);
}

void twixt::Board::setPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon) {
    if (line < m_size && column < m_size) {
        m_board[line * m_size + column] = pylon;
    }
    else {
        std::cout << "Error at setting a pylon.";
        exit(0);
    }
}

const std::optional<twixt::Pylon>& twixt::Board::getPylon(uint16_t line, uint16_t column) const {
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
        m_board[line * m_size + column] = std::nullopt;
    }
}