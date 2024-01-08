#include <iostream>
#include "utility.h"
#include "bulldozer.h"
#include "game.h"
#include "pylon.h"
#include "bridge.h"
#include "board.h"
#include "player.h"
#include "RecommenderSystem.h"

int main() {
    // Inițializare Game și RecommenderSystem.
    twixt::Game game; // Presupunem că aveți un constructor adecvat.
    twixt::RecommenderSystem recommender(game);

    // Testarea generatePossibleBridges.
    auto possibleBridges = recommender.generatePossibleBridges();
    std::cout << "Numărul de bridge-uri posibile: " << possibleBridges.size() << std::endl;

    // Dacă lista este prea lungă, puteți afișa doar un număr limitat de bridge-uri sau detalii specifice.

    // Testarea evaluateMove (presupunând că aveți un bridge pentru test).
    // twixt::Bridge testBridge = ...; // Inițializați un bridge de test.
    // int score = recommender.evaluateMove(testBridge);
    // std::cout << "Scorul pentru bridge-ul testat: " << score << std::endl;

    // Testarea isGameCloseToEnd.
    bool isCloseToEnd = recommender.isGameCloseToEnd();
    std::cout << "Jocul este aproape de final: " << (isCloseToEnd ? "Da" : "Nu") << std::endl;

    // Continuați cu alte teste pentru diferite metode ale sistemului de recomandare.

    return 0;
}
