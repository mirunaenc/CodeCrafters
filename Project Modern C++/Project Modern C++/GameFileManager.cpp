#include "GameFileManager.h"
#include <string>

namespace twixt {
    void GameFileManager::saveGame(const Game& game)
    {
        try {
            std::ofstream file("savedGame.txt");
            if (file.is_open()) {
                file << "=== Board State ===\n";
                game.m_gameBoard.saveBoardState(file);


                file << "=== Player 1 State ===\n";
                game.m_player1.savePlayerState(file);
                file << "=== Player 2 State ===\n";
                game.m_player2.savePlayerState(file);

                file.close();
                std::cout << "Jocul a fost salvat cu succes! " << std::endl;
            }
            else {
                throw std::runtime_error("Nu s-a putut deschide fisierul pentru salvare.");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }
    }

    void GameFileManager::loadGame(Game& game)
    {
        std::ifstream file("savedGame.txt");
        try {
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    if (line == "=== Board State ===") {
                         game.m_gameBoard.loadBoardState(file);
                    }
                    else if (line == "=== Player 1 State ===") {
                        // m_player1.loadPlayerState(file);
                    }
                    else if (line == "=== Player 2 State ===") {
                        // m_player2.loadPlayerState(file);
                    }
                    // Implementați logica pentru interpretarea și încărcarea stării jocului din fișier
                }
                file.close();
                std::cout << "Jocul a fost incarcat cu succes! " << std::endl;
            }
            else {
                throw std::runtime_error("Nu s-a putut deschide fisierul pentru incarcare.");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }

    }

}

