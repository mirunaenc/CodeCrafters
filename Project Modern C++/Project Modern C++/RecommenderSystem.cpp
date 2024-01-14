//#include "RecommenderSystem.h"
//#include "game.h"
//
//std::vector<twixt::Bridge> twixt::RecommenderSystem::generatePossibleBridges() {
//    std::vector<twixt::Bridge> possibleBridges;
//    std::vector<std::optional<twixt::Pylon>> pylons = m_game.getGameBoard().getPylons();
//    for (auto& pylon1 : pylons) {
//        if (pylon1.has_value() && pylon1->getColor() == m_game.getPlayer1().getColor()) {
//            for (auto& pylon2 : pylons) {
//                if (pylon2.has_value() && pylon2->getColor() == m_game.getPlayer1().getColor()) {
//                    twixt::Bridge potentialBridge(*pylon1, *pylon2);
//                    if (m_game.getGameBoard().isValidBridge(*pylon1, *pylon2)) {
//                        possibleBridges.push_back(potentialBridge);
//                        
//                    }
//                }
//            }
//        }
//    }
//    return possibleBridges;
//}
//
//twixt::RecommenderSystem::RecommenderSystem(Game& game) : m_game{game}
//{
//}
//
//int twixt::RecommenderSystem::connectivity(const Bridge& move)
//{
//    int score = 0;
//    // verifica daca exista alte bridge-uri care se conecteaza la aceiasi pylons ca si bridge-ul curent.
//    for (const Bridge& otherMove : m_game.getGameBoard().getBridges()) {
//        if (otherMove != move && (otherMove.getStart() == move.getStart() || otherMove.getEnd() == move.getEnd())) {
//            score++;
//        }
//    }
//    return score;
//}
//
//int twixt::RecommenderSystem::proximityToGoal(const Bridge& move) {
//    int score = 0;
//    // daca jucatorul incearca sa ajunga de la stanga la dreapta, 
//    // atunci scorul poate fi coloana pylonului de la capatul bridge-ului.
//    score = move.getEnd().getColumn();
//    return score;
//}
//
//int twixt::RecommenderSystem::blocksOpponent(const Bridge& move)
//{
//    int score = 0;
//    //daca adversarul incearca sa ajunga de la stanga la dreapta,
//    //  atunci orice bridge care se intinde de  sus in jos ar putea bloca adversarul.
//    if (move.getStart().getColumn() == move.getEnd().getColumn()) {
//        score = 1;
//    }
//    return score;
//}
//
//
//int twixt::RecommenderSystem::evaluateMove(const Bridge& move)
//{
//    int score = 0;
//
//    // cat de aproape este bridge-ul de obiectiv
//    score += proximityToGoal(move);
//
//    // daca bridge-ul blocheaza adversarul
//    score += blocksOpponent(move);
//
//    // cat de multi pylons conecteaza bridge-ul
//    score += connectivity(move);
//
//    return score;
//}
//
//int twixt::RecommenderSystem::potentialOpponentBridges(const Bridge& move)
//{
//    return 0;
//}
//
//twixt::Bridge twixt::RecommenderSystem::predictOpponentsMove() {
//    std::vector<twixt::Bridge> possibleOpponentBridges;
//    EColor currentPlayerColor = m_game.getPlayer1().getColor(); 
//    EColor opponentColor = (currentPlayerColor == EColor::RED) ? EColor::BLACK : EColor::RED;
//    auto opponentPylons = m_game.getGameBoard().getPylons();
//
//    for (auto& pylon1 : opponentPylons) {
//        if (pylon1.has_value() && pylon1->getColor() == opponentColor) {
//            for (auto& pylon2 : opponentPylons) {
//                if (pylon2.has_value() && pylon2->getColor() == opponentColor && pylon1 != pylon2) {
//                    twixt::Bridge potentialBridge(*pylon1, *pylon2);
//                    if (m_game.getGameBoard().isValidBridge(potentialBridge.getStart(), potentialBridge.getEnd())) {
//                        possibleOpponentBridges.push_back(potentialBridge);
//                    }
//                }
//            }
//        }
//    }
//
//
//        twixt::Bridge mostLikelyBridge;
//        int highestScore = -1;
//        for (const auto& bridge : possibleOpponentBridges) {
//            int score = evaluateMove(bridge);
//            if (score > highestScore) {
//                highestScore = score;
//                mostLikelyBridge = bridge;
//            }
//        }
//
//        return mostLikelyBridge;
//}
//
//twixt::Bridge twixt::RecommenderSystem::getBestMove() {
//    std::vector<twixt::Bridge> possibleMoves = generatePossibleBridges();
//    if (possibleMoves.empty()) {
//        throw std::runtime_error("Nu exista mutari posibile.");
//    }
//
//    twixt::Bridge bestMove = possibleMoves.front();
//    int highestScore = -1;
//
//    for (const auto& move : possibleMoves) {
//        int score = evaluateMove(move);
//        if (score > highestScore) {
//            highestScore = score;
//            bestMove = move;
//        }
//    }
//
//    return bestMove;
//}
//
//bool twixt::RecommenderSystem::isGameCloseToEnd() {
//    const auto& board = m_game.getGameBoard();
//    const auto& pylons = board.getPylons();
//
//    // Verifică dacă oricare dintre jucători este aproape de a completa o cale.
//    bool isRedCloseToEnd = isPlayerCloseToEnd(EColor::RED, pylons);
//    bool isBlackCloseToEnd = isPlayerCloseToEnd(EColor::BLACK, pylons);
//
//    return isRedCloseToEnd || isBlackCloseToEnd;
//}
//
//bool twixt::RecommenderSystem::isPlayerCloseToEnd(EColor playerColor, const std::vector<std::optional<twixt::Pylon>>& pylons) {
//    int minDistanceToStartEdge = INT_MAX;
//    int minDistanceToEndEdge = INT_MAX;
//    int boardSize = m_game.getGameBoard().getSize();
//
//    for (const auto& optionalPylon : pylons) {
//        if (optionalPylon.has_value() && optionalPylon->getColor() == playerColor) {
//            const auto& pylon = optionalPylon.value();
//
//             // Distanța pylonului de la marginea stângă și dreaptă a tablei de joc.
//            int distanceToStartEdge = pylon.getColumn();
//            int distanceToEndEdge = boardSize - pylon.getColumn();
//
//            minDistanceToStartEdge = std::min(minDistanceToStartEdge, distanceToStartEdge);
//            minDistanceToEndEdge = std::min(minDistanceToEndEdge, distanceToEndEdge);
//        }
//    }
//
//    // Considerăm că un jucător este aproape de a termina dacă este suficient de aproape de ambele margini.
//    // "Suficient de aproape" poate fi definit în funcție de regulile jocului; aici este un exemplu arbitrar.
//    int threshold = 3; // De exemplu, înseamnă că jucătorul este cu 3 pași de a completa calea.
//    return minDistanceToStartEdge <= threshold && minDistanceToEndEdge <= threshold;
//}
//
//
//void twixt::RecommenderSystem::giveHint() {
//    try {
//        if (isGameCloseToEnd()) {
//            std::cout << "Sfat: Jocul este aproape de final, alegeti mutarile cu atentie." << std::endl;
//        }
//
//        twixt::Bridge bestMove = getBestMove();
//        auto startCoord = bestMove.getCoordStart();
//        auto endCoord = bestMove.getCoordEnd();
//
//        std::cout << "Hint: Cea mai buna mutare este de la (" << startCoord.first << ", " << startCoord.second << ")"
//            << " la (" << endCoord.first << ", " << endCoord.second << ")" << std::endl;
//    }
//    catch (const std::runtime_error& e) {
//        std::cout << "Sfat: " << e.what() << std::endl;
//    }
//}
