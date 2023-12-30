#include "RecommenderSystem.h"
#include "game.h"

std::vector<twixt::Bridge> twixt::RecommenderSystem::generatePossibleBridges() {
    std::vector<twixt::Bridge> possibleBridges;
    std::vector<std::optional<twixt::Pylon>> pylons = m_game.getGameBoard().getPylons();
    for (auto& pylon1 : pylons) {
        if (pylon1.has_value() && pylon1->getColor() == m_game.getPlayer1().getColor()) {
            for (auto& pylon2 : pylons) {
                if (pylon2.has_value() && pylon2->getColor() == m_game.getPlayer1().getColor()) {
                    twixt::Bridge potentialBridge(*pylon1, *pylon2);
                    if (m_game.getGameBoard().isValidBridge(*pylon1, *pylon2)) {
                        possibleBridges.push_back(potentialBridge);
                        
                    }
                }
            }
        }
    }
    return possibleBridges;
}

twixt::RecommenderSystem::RecommenderSystem(Game& game) : m_game{game}
{
}

int twixt::RecommenderSystem::connectivity(const Bridge& move)
{
    int score = 0;
    // verifica daca exista alte bridge-uri care se conecteaza la aceiasi pylons ca si bridge-ul curent.
    for (const Bridge& otherMove : m_game.getGameBoard().getBridges()) {
        if (otherMove != move && (otherMove.getStart() == move.getStart() || otherMove.getEnd() == move.getEnd())) {
            score++;
        }
    }
    return score;
}

int twixt::RecommenderSystem::proximityToGoal(const Bridge& move) {
    int score = 0;
    // daca jucatorul incearca sa ajunga de la stanga la dreapta, 
    // atunci scorul poate fi coloana pylonului de la capatul bridge-ului.
    score = move.getEnd().getColumn();
    return score;
}

int twixt::RecommenderSystem::blocksOpponent(const Bridge& move)
{
    int score = 0;
    //daca adversarul incearca sa ajunga de la stanga la dreapta,
    //  atunci orice bridge care se intinde de  sus in jos ar putea bloca adversarul.
    if (move.getStart().getColumn() == move.getEnd().getColumn()) {
        score = 1;
    }
    return score;
}


int twixt::RecommenderSystem::evaluateMove(const Bridge& move)
{
    int score = 0;

    // cat de aproape este bridge-ul de obiectiv
    score += proximityToGoal(move);

    // daca bridge-ul blocheaza adversarul
    score += blocksOpponent(move);

    // cat de multi pylons conecteaza bridge-ul
    score += connectivity(move);

    return score;
}

int twixt::RecommenderSystem::potentialOpponentBridges(const Bridge& move)
{
    return 0;
}

twixt::Bridge twixt::RecommenderSystem::predictOpponentsMove()
{
    std::vector<twixt::Bridge> possibleOpponentBridges;
    std::vector<std::optional<twixt::Pylon>> opponentPylons = m_game.getGameBoard().getPylons();
}

twixt::Bridge twixt::RecommenderSystem::getBestMove() {
    std::vector<twixt::Bridge> possibleMoves = generatePossibleBridges();
    return *std::max_element(possibleMoves.begin(), possibleMoves.end(), [this](const twixt::Bridge& a, const twixt::Bridge& b) {
        return evaluateMove(a) < evaluateMove(b);
        });
}

void twixt::RecommenderSystem::giveHint() {
    twixt::Bridge bestMove = getBestMove();
    std::cout << "Hint: cea mai buna mutare este " << bestMove.getCoordStart().first
        << " " << bestMove.getCoordStart().second << std::endl << bestMove.getCoordEnd().first
        << " " << bestMove.getCoordStart().second << std::endl;
}
