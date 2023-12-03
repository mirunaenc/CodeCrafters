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

bool twixt::Board::isPositionInsideBoard(uint16_t line, uint16_t column) const
{
    if (line >= 0 && line < m_size && column >= 0 && column < m_size) {
        return true;
    }
    return false;
}

void twixt::Board::addBridge(twixt::Bridge &bridge)
{
    if (twixt::Board::isValidBridge(bridge.getStart(), bridge.getEnd())) {
        m_boardBridges.push_back(bridge);
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

const std::vector<std::optional<twixt::Bridge>>& twixt::Board::getBridges() const
{
    return m_boardBridges;
}

bool twixt::Board::isValidBridge(const Pylon& start, const Pylon& end) {
    if (abs(start.getLine() - end.getLine()) != 1 || abs(start.getColumn() - end.getColumn()) != 2) {
        return false;
    }

    for (const std::optional<Bridge>& optBridge : m_boardBridges) {
        if (optBridge.has_value()) {
            const Bridge& bridge = optBridge.value();
            if ((bridge.getStart() == start && bridge.getEnd() == end) ||
                (bridge.getStart() == end && bridge.getEnd() == start)) {
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

bool twixt::Board::canPlaceLargePylon(const LargePylon& pylon)
{
    for (const auto& offset : pylon.getShape()) {
        uint16_t line = pylon.getLine() + offset.first;
        uint16_t column = pylon.getColumn() + offset.second;
        if (!isPositionInsideBoard(line, column) || getPylon(line, column).has_value()) {
            return false;
        }
    }

    size_t countLargePylons = 0;

    for (auto& optPylon : m_boardPylons) {
        if (optPylon.has_value() && dynamic_cast<LargePylon*>(&optPylon.value())) {
            countLargePylons++;
        }
    }
    if (countLargePylons > 5) {

        return false;
    }

    return true;
}

bool twixt::Board::existsBridgeBetweenPylons(const twixt::Pylon& p1, const twixt::Pylon& p2)
{
    for (const auto& optBridge : m_boardBridges) {
        if (optBridge.has_value()) {
            const twixt::Bridge& bridge = optBridge.value();
            if ((bridge.getStart() == p1 && bridge.getEnd() == p2) ||
                (bridge.getStart() == p2 && bridge.getEnd() == p1)) {
                return true;
            }
        }
    }
    return false;
}

bool twixt::Board::canPlaceBridge(const twixt::Pylon& p1, const twixt::Pylon& p2)
{
    uint16_t lineDif = abs(p1.getLine() - p2.getLine());
    uint16_t colDif = abs(p1.getColumn() - p2.getColumn());

    if (!(lineDif == 1 && colDif == 2))
        return false;
    if (!(lineDif == 2 && colDif == 1))
        return false;



    //to be continued;
    return true;
}

bool twixt::Board::isPylonOccupied(const Pylon& p)
{
    for (const auto& optBridge : m_boardBridges) {
        const twixt::Bridge& bridge = optBridge.value();
        if (bridge.getStart() == p || bridge.getEnd() == p) {
            return true;
        }
    }

    return false;
}

void twixt::Board::createBridge(twixt::Pylon& pilon)
{
    for(const auto& p : m_boardPylons) {
        if (p.has_value()) {
            twixt::Pylon actualPylon = p.value();
            if(existsBridgeBetweenPylons(pilon, actualPylon))
                return;

            if (canPlaceBridge(pilon, actualPylon)) {
                Bridge newBridge = twixt::Bridge(pilon, actualPylon);
                addBridge(newBridge);
            }
        }
        
    }
}

//important
//pozitie 1 -> \ 
//pozitie 2 -> /
//pozitie 3 -> -  _
//pozitie 4 -> _  -

int twixt::Board::getBridgePosition(const twixt::Pylon& p1, const twixt::Pylon& p2)
{
    uint16_t line1 = p1.getLine(), col1 = p1.getColumn(), line2 = p2.getLine(), col2 = p2.getColumn();
    uint16_t lineDif = abs(line1 - line2), colDif = abs(col1 - col2);
    
    if (lineDif == 2) {
        if (col1 < col2) {
            if (line1 < line2)
                return 1;
            else
                return 2;
        }
    }
    return 0;
}
