﻿import bridge;
#include <vector>
#include <algorithm>
#include "game.h"
#include <iostream>

namespace twixt {
    class RecommenderSystem {
    private:
        Game& m_game;
    public:
        RecommenderSystem(Game& game);

        // genereaza toate bridge-urile posibile pentru jucatorul curent
        std::vector<Bridge> generatePossibleBridges();

        // evalueaza o mutare data, returnand un scor bazat pe cat de buna este mutarea
        int evaluateMove(const Bridge& move);

        Bridge getBestMove();

        void giveHint();
    };
}