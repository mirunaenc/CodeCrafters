import pylon;
import bridge;
import board;
import player;

#include <iostream>
#include"bulldozer.h"
#include"game.h"

int main()
{
    twixt::Board gameBoard;
    twixt::Player player1;
    twixt::Player player2;
    twixt::Game twixtGame(gameBoard, player1, player2);

  
    while (!twixtGame.checkWinCondition()) {
        twixtGame.playTurn();
    }

	return 0;
}
