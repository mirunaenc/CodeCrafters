import bridge;
#include <vector>
#include <algorithm>
#include "game.h"
#include <iostream>

namespace twixt {
    class HintSystem {
    private:
        Game& m_game;
    public:
        HintSystem(Game& game) : m_game(game) {}

        // genereaza toate mutarile posibile pentru jucatorul curent
        std::vector<Bridge> generatePossibleMoves() {
            std::vector<Bridge> possibleMoves;
            return possibleMoves;
        }

        // evalueaza o mutare data, returnand un scor bazat pe cat de buna este mutarea
        int evaluateMove(const Bridge& move) {
            int score = 0;
            return score;
        }

        Bridge getBestMove() {
            std::vector<Bridge> possibleMoves = generatePossibleMoves();
            return *std::max_element(possibleMoves.begin(), possibleMoves.end(), this {
                return evaluateMove(a) < evaluateMove(b);
            });
        }

        void giveHint() {
            Bridge bestMove = getBestMove();
            std::cout << "Hint: cea mai bună mutare este " << bestMove.getCoordStart().first
                << " " << bestMove.getCoordStart().second << std::endl << bestMove.getCoordEnd().first
                << " " << bestMove.getCoordStart().second << std::endl;
        }
    };
}