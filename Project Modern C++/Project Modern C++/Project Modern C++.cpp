import <iostream>;
import utility;
import "bulldozer.h";
import "game.h";
import pylon;
import bridge;
import board;
import player;

int main()
{
    twixt::Board gameBoard{ 10 };
    twixt::Player player1{ 20, 40, twixt::EColor::RED, gameBoard };
    twixt::Player player2{ 20, 40, twixt::EColor::BLACK, gameBoard };

    twixt::Game twixtGame(gameBoard , player1, player2);

  
    twixtGame.run();

   /* twixt::Board board2(3);

    twixt::Player player1(10, 10, twixt::EColor::RED, board2);
    twixt::Player player2(10, 10, twixt::EColor::BLACK, board2);

    twixt::Bulldozer bulldozer(board2, 0, 0, 0.5, player1, player2);

    player1.placePylon(0, 1);
    player1.placePylon(1, 0);
    player1.placePylon(1, 1);
    player2.placePylon(1, 2);
    player2.placePylon(2, 1);

    for(int i = 0; i < 20; i++)	
       player1.makeMove();

    for (int i = 0; i < 20; i++)
        bulldozer.playTurn();*/

	return 0;
}
