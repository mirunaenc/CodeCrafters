#include "board.h"

twixt::Board::Board()
{
}

twixt::Board::Board(uint16_t size) : m_size{ size } {
    m_boardPylons.resize(m_size * m_size, std::nullopt);
    //m_boardBridges.resize(m_size * m_size, std::nullopt);
}

twixt::Board::Board(const Board& board) : m_size{ board.m_size } {
    m_boardPylons.resize(m_size * m_size);
    //m_boardBridges.resize(m_size * m_size);
    std::copy(board.m_boardPylons.begin(), board.m_boardPylons.end(), m_boardPylons.begin());
    std::copy(board.m_boardBridges.begin(), board.m_boardBridges.end(), m_boardBridges.begin());
}

twixt::Board::Board(Board&& board) noexcept : m_size{ board.m_size } {
    m_boardPylons.resize(m_size * m_size);
    //m_boardBridges.resize(m_size * m_size);
    m_boardPylons = std::move(board.m_boardPylons);
    m_boardBridges = board.m_boardBridges;
}

twixt::Board& twixt::Board::operator=(const Board& board)
{
    if (this != &board) {
        m_size = board.m_size;
        m_boardPylons.resize(m_size * m_size);
        //m_boardBridges.resize(m_size * m_size);
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
        //m_boardBridges.resize(m_size * m_size);
        m_boardPylons = std::move(board.m_boardPylons);
        m_boardBridges = board.m_boardBridges;
    }
    return *this;
}

uint16_t twixt::Board::getSize() const {
    return m_size;
}

void twixt::Board::setSize(uint16_t size) {
    m_size = size;
    m_boardPylons.resize(m_size * m_size, std::nullopt);
    //m_boardBridges.resize(m_size * m_size, std::nullopt);
}

//void twixt::Board::addPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon) {
//    if (line < m_size && column < m_size) {
//        m_boardPylons[line * m_size + column] = pylon;
//    }
//    else {
//        std::cout << "Error at setting a pylon.";
//        exit(0);
//    }
//}

void twixt::Board::addPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon) {
    if (!pylon.has_value()) {
        std::cout << "Error: Trying to set an empty pylon." << std::endl;
        return; // Înlocuiește exit(0) cu un comportament mai sigur în caz de eroare
    }

    if (line < m_size && column < m_size) {
        m_boardPylons[line * m_size + column] = pylon.value(); // Accesează valoarea din std::optional folosind .value()
    }
    else {
        std::cout << "Error: Trying to set a pylon outside the board boundaries." << std::endl;
        return; // Înlocuiește exit(0) cu un comportament mai sigur în caz de eroare
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

bool twixt::Board::isPositionOccupied(uint16_t i, uint16_t j)
{
    if (!isPositionInsideBoard(i, j))
        return false;

    for (const auto& pilon : m_boardPylons) {
        if (pilon.has_value()) {
            twixt::Pylon actualPylon = pilon.value();
            if (actualPylon.getLine() == i && actualPylon.getColumn() == j)
                return false;
        }
    }
    return true;
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

const std::vector<twixt::Bridge>& twixt::Board::getBridges() const
{
    return m_boardBridges;
}

bool twixt::Board::isValidBridge(const Pylon& start, const Pylon& end) {
    /*uint16_t difLine{ abs(start.getLine() - end.getLine()) };
    uint16_t difCol{ abs(end.getColumn() - end.getColumn()) };

    if (difLine > 2 || difCol > 2 || difLine == 0 || difCol == 0)
        return false;
    if (difLine == 1 && difCol != 2)
        return false;
    if (difLine == 2 && difCol != 1)
        return false;

    for (const Bridge& bridge : m_boardBridges) {
        if ((bridge.getStart() == start && bridge.getEnd() == end) ||
            (bridge.getStart() == end && bridge.getEnd() == start)) {
            return false;
        }
    }*/

    return true;
}

void twixt::Board::resetBoard() {
    m_boardPylons.clear();
    m_boardBridges.clear();
    m_boardPylons.resize(m_size * m_size);
    //m_boardBridges.resize(m_size * m_size);
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
    /*for (const auto& optBridge : m_boardBridges) {
        if (optBridge.has_value()) {
            const twixt::Bridge& bridge = optBridge.value();
            if ((bridge.getStart() == p1 && bridge.getEnd() == p2) ||
                (bridge.getStart() == p2 && bridge.getEnd() == p1)) {
                return true;
            }
        }
    }*/

    for (const Bridge& bridge : m_boardBridges) {
        if ((bridge.getStart() == p1 && bridge.getEnd() == p2) ||
            (bridge.getStart() == p2 && bridge.getEnd() == p1)) {
            return true;
        }
    }

    return false;
}

bool twixt::Board::canPlaceBridge(twixt::Pylon& p1, twixt::Pylon& p2)
{
    if(!isPositionInsideBoard(p1.getLine(), p1.getColumn()) || 
        !isPositionInsideBoard(p2.getLine(), p2.getColumn()) ||
            (p1.getLine() == p2.getLine()) && p1.getColumn() == p2.getColumn()) {
        return false;
    }

    if (!isValidBridge(p1, p2)) {
        return false;
    }

    Bridge newBridge = twixt::Bridge(p1, p2);

    for (const auto& existingBridge : m_boardBridges) {
        if (newBridge.intersectsWith(existingBridge))
            return false;
    }

    return true;
}

bool twixt::Board::isPylonOccupied(const Pylon& p)
{
    /*for (const auto& optBridge : m_boardBridges) {
        const twixt::Bridge& bridge = optBridge.value();
        if (bridge.getStart() == p || bridge.getEnd() == p) {
            return true;
        }
    }*/

    for (const Bridge& bridge : m_boardBridges) {
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

void twixt::Board::saveBoardState(std::ofstream& file) const
{
    file << m_size << "\n";

    for (const auto& pylon : m_boardPylons) {
        if (pylon.has_value()) {
            file << pylon->getLine() << " " << pylon->getColumn() << " " << static_cast<int>(pylon->getColor()) << "\n";
        }
    }
    for (const auto& bridge : m_boardBridges) {
        file <<bridge.getStart().getLine() << " " << bridge.getStart().getColumn()
            << " " << bridge.getEnd().getLine() << " " << bridge.getEnd().getColumn() << "\n";
    }
}

void twixt::Board::loadBoardState(std::ifstream& file)
{
    std::string line;
    if (std::getline(file, line)) {
        m_size = std::stoi(line);

        m_boardPylons.clear();
        m_boardPylons.resize(m_size * m_size);


        for (size_t i = 0; i < m_size * m_size; ++i) {
            uint16_t line, column;
            int color;
            if (file >> line >> column >> color) {
                m_boardPylons[i] = Pylon(line, column);
                m_boardPylons[i]->setColor(static_cast<EColor>(color));
            }
        }

        while (std::getline(file, line)) {
            uint16_t startLine, startColumn, endLine, endColumn;
            if (std::istringstream(line) >> startLine >> startColumn >> endLine >> endColumn) {
       
                std::optional<Pylon> startPylon = getPylon(startLine, startColumn);
                std::optional<Pylon> endPylon = getPylon(endLine, endColumn);

                
                if (startPylon.has_value() && endPylon.has_value()) {
                    Bridge newBridge(startPylon.value(), endPylon.value());
                    addBridge(newBridge);
                }
                else {
                    std::cout << "Eroare: Piloni invalizi pentru crearea podului." << std::endl;
                }
            }
        }
    }
}

bool twixt::Board::hasRoadDFS(uint16_t currentLine, uint16_t currentColumn, std::vector<bool>& visited)
{
    EColor pylonColor = EColor::NONE;

    if(this->getPylon(currentLine, currentColumn).has_value())
        pylonColor = this->getPylon(currentLine, currentColumn).value().getColor();


    if (pylonColor == EColor::RED)
        if (currentLine == this->getSize() - 1)
            return true;    

    if (pylonColor == EColor::BLACK)
        if (currentColumn == this->getSize() - 1)
            return true;
  
    visited[currentLine * this->getSize() + currentColumn] = true;

    // Check all adjacent positions
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) { 
            if (std::abs(i) + std::abs(j) == 3) { // Check only diagonally connected pylons
                uint16_t nextLine = currentLine + i;
                uint16_t nextColumn = currentColumn + j;

                if (this->isPositionInsideBoard(nextLine, nextColumn) &&
                    !visited[nextLine * this->getSize() + nextColumn] &&
                    this->getPylon(currentLine, currentColumn).has_value() &&
                    this->getPylon(nextLine, nextColumn).has_value()
                    && this->getPylon(nextLine, nextColumn).value().getColor() == this->getPylon(currentLine, currentColumn).value().getColor()
                    //&& this->existsBridgeBetweenPylons(m_gameBoard.getPylon(currentLine, currentColumn).value(), m_gameBoard.getPylon(nextLine, nextColumn).value())
                    )
                {
                    if (hasRoadDFS(nextLine, nextColumn, visited))
                        return true;
                }
            }
        }
    }

    return false;
}

twixt::EColor twixt::Board::hasWinningRoad()
{

    std::vector<bool> visited(this->getSize() * this->getSize(), false);

    // Check for horizontal winning road
        for (uint16_t i = 0; i < this->getSize(); ++i) {
            if(this->getPylon(i,0).has_value())
            if (visited[i * this->getSize() + 0] == false && this->getPylon(i,0).value().getColor() == EColor::BLACK && this->hasRoadDFS(i, 0, visited))
                return EColor::BLACK;
        }
    

    // Check for vertical winning road
        for (uint16_t j = 0; j < this->getSize(); ++j) {
            if (this->getPylon(0, j).has_value())
            if (visited[0 * this->getSize() + j] == false && this->getPylon(0,j).value().getColor() == EColor::RED && this->hasRoadDFS(0, j, visited))
                return EColor::RED;
        }  
    return EColor::NONE;
}

QGraphicsView* twixt::Board::createQGraphicsView(QWidget* parent)
{
    QGraphicsScene* scene = new QGraphicsScene(parent);
   
    for (uint16_t i{ 0 }; i < m_size; ++i) {
        for (uint16_t j{ 0 }; j < m_size; ++j) {
            QPointF position(j * 30, i * 30); // Adjust the position as needed

            if (this->getPylon(i,j).has_value() ) 
            {
                twixt::EColor pylonColor = this->getPylon(i, j).value().getColor();
                QBrush brush = (pylonColor == twixt::EColor::RED) ? QBrush(Qt::red) : QBrush(Qt::black);

                QGraphicsEllipseItem* ellipse = scene->addEllipse(position.x(), position.y(), 20, 20, QPen(Qt::black), brush);
            }
            else {
                // No pylon at this position, draw a white ellipse
                QBrush brush(Qt::white);
                QGraphicsEllipseItem* ellipse = scene->addEllipse(position.x(), position.y(), 20, 20, QPen(Qt::black), brush);
            }
        }
    }
    
     QGraphicsView* view = new QGraphicsView(scene);
    
    return view;
}
