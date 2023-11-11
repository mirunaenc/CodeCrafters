module board;


twixt::Board::Board()
{
}

twixt::Board::Board(uint16_t size) : m_size{ size } {
    m_boardPylons.resize(m_size * m_size);
    m_boardBridges.resize(m_size * m_size);
}

twixt::Board::Board(const Board& board) : m_size{ board.m_size } {
    m_boardPylons.resize(m_size * m_size);
    m_boardBridges.resize(m_size * m_size);
    std::copy(board.m_boardPylons.begin(), board.m_boardPylons.end(), m_boardPylons.begin());
    std::copy(board.m_boardBridges.begin(), board.m_boardBridges.end(), m_boardBridges.begin());
}

twixt::Board::Board(Board&& board) noexcept : m_size{ board.m_size } {
    m_boardPylons.resize(m_size * m_size);
    m_boardBridges.resize(m_size * m_size);
    m_boardPylons = std::move(board.m_boardPylons);
    m_boardBridges = std::move(board.m_boardBridges);
}

twixt::Board& twixt::Board::operator=(const Board& board)
{
    if (this != &board) {
        m_size = board.m_size;
        m_boardPylons.resize(m_size * m_size);
        m_boardBridges.resize(m_size * m_size);
        std::copy(board.m_boardPylons.begin(), board.m_boardPylons.end(), m_boardPylons.begin());
        std::copy(board.m_boardBridges.begin(), board.m_boardBridges.end(), m_boardBridges.begin());
    }
    return *this;
}


twixt::Board& twixt::Board::operator=(Board&& board) noexcept
{
    if (this != &board) {
        m_size = board.m_size;
        m_boardPylons.resize(m_size * m_size);
        m_boardBridges.resize(m_size * m_size);
        m_boardPylons = std::move(board.m_boardPylons);
        m_boardBridges = std::move(board.m_boardBridges);
    }
    return *this;
}

uint16_t twixt::Board::getSize() const {
    return m_size;
}

void twixt::Board::setSize(uint16_t size) {
    m_size = size;
    m_boardPylons.resize(m_size * m_size);
    m_boardBridges.resize(m_size * m_size);
}

void twixt::Board::setPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon) {
    if (line < m_size && column < m_size) {
        m_boardPylons[line * m_size + column] = pylon;
    }
    else {
        std::cout << "Error at setting a pylon.";
        exit(0);
    }
}

const std::optional<twixt::Pylon>& twixt::Board::getPylon(uint16_t line, uint16_t column) const {
    if (line < m_size && column < m_size) {
        return m_boardPylons[line * m_size + column];
    }
    else {
        std::cout << "Error at method getPylon.";
        exit(0);
    }
}

void twixt::Board::resetPosition(uint16_t line, uint16_t column) {
    if (line < m_size && column < m_size) {
        m_boardPylons[line * m_size + column] = std::nullopt;
    }
}

bool twixt::Board::isPositionInsideBoard(const twixt::Pylon& pylon) const
{
    uint16_t line = pylon.getLine();
    uint16_t column = pylon.getColumn();

    if (line >= 0 && line < m_size && column >= 0 && column < m_size) {
        return true;
    }
    return false;
}


void twixt::Board::removeBridge(const twixt::Bridge& bridge)
{
    auto it = std::find(m_boardBridges.begin(), m_boardBridges.end(), bridge);
    if (it != m_boardBridges.end()) {
        m_boardBridges.erase(it);
    }
}
