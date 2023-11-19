module board;

twixt::Board::Board()
{
}

twixt::Board::Board(uint16_t size) : m_size{ size } {
    m_boardPylons.resize(m_size * m_size, std::nullopt);
    m_boardBridges.resize(m_size * m_size, std::nullopt);
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
    m_boardPylons.resize(m_size * m_size, std::nullopt);
    m_boardBridges.resize(m_size * m_size, std::nullopt);
}

void twixt::Board::addPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon) {
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

void twixt::Board::addBridge(twixt::Pylon& start, twixt::Pylon& end)
{
    if (twixt::Board::isValidBridge(start, end)) {
        const twixt::Bridge newBridge = Bridge(start, end);
        m_boardBridges.push_back(newBridge);
    }
    else {
        std::cout << "Bridge is not valid. \n";
    }
}


void twixt::Board::removeBridge(const twixt::Bridge& bridge)
{
    auto it = std::find(m_boardBridges.begin(), m_boardBridges.end(), bridge);
    if (it != m_boardBridges.end()) {
        m_boardBridges.erase(it);
    }
}

void twixt::Board::provisionalPrint()
{
    for (int line = 0; line < m_size; line++) {
        for (int column = 0; column < m_size; column++) {
            if (m_boardPylons[line * m_size + column].has_value())
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        std::cout << '\n';
    }
}

const std::vector<std::optional<twixt::Pylon>>& twixt::Board::getPylons() const
{
    return m_boardPylons;
}

bool twixt::Board::isValidBridge(const Pylon& start, const Pylon& end) {
    if (abs(start.getLine() - end.getLine()) != 1 || abs(start.getColumn() - end.getColumn()) != 2) {
        return false;
    }

    for (const std::optional<Bridge>& optBridge : m_boardBridges) {
        if (optBridge.has_value()) {
            const Bridge& bridge = optBridge.value();
            if ((bridge.getStart().first == start && bridge.getEnd().second == end) ||
                (bridge.getStart().first == end && bridge.getEnd().second == start)) {
                return false;
            }
        }
    }

    return true;
}

void twixt::Board::resetBoard() {
    m_boardPylons.clear();
    m_boardBridges.clear();
    m_boardPylons.resize(m_size * m_size);
    m_boardBridges.resize(m_size * m_size);
}
