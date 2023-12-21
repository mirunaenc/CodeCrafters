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

int twixt::RecommenderSystem::evaluateMove(const Bridge& move)
{
  
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
