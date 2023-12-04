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

	return 0;
}
