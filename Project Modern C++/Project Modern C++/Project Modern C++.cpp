import pylon;
import bridge;
import board;
import player;

#include <iostream>
#include"bulldozer.h"
#include"game.h"

int main()
{
	//twixt::Board tabla{ 2 };
	//twixt::Pylon pilon{ 1, 0 };
	//tabla.setPylon(1, 0, pilon);
	//tabla.provisionalPrint();

 //   twixt::Pylon pilon1{ 10,10 };
 //   twixt::Pylon pilon{12,13};
 //   pilon1 = pilon;
 //   //std::cout << pilon1.getLine();
 //   //std::cout << pilon1.getLine();//test commit
 //   pilon = pilon1;
 //   pilon1.setColumn(3);
 //   twixt::Bridge bridge1(pilon1,pilon);
 //   //std::cout << bridge1.getEnd().first;
	//
	//if (bridge1.isConnectedTo(pilon1)) {
	//	std::cout << "Podul este conectat la pilon1.\n";
	//}
	//else {
	//	std::cout << "Podul nu este conectat la pilon1.\n";
	//}

    
    twixt::Board board(10);
    twixt::Board board2;
    board2 = board;
board2.setPylon(1, 1, twixt::Pylon(1, 1));
board2.setPylon(3, 0, twixt::Pylon(3, 0));
board2.setPylon(2, 0, twixt::Pylon(2, 0));
board2.setPylon(2, 1, twixt::Pylon(2, 1));
board2.resetPosition(2, 1);
board2.resetPosition(2, 0);
  board = board2;

  twixt::Bulldozer bulldozer(board,4,2,0.3f);
  twixt::Bulldozer bulldozer2(bulldozer);
  bulldozer.setLinePosition(1);
  twixt::Bulldozer bulldozer3(board, 4, 2, 0.3f);
  bulldozer3 = bulldozer2;
  bulldozer3.setBiasedCoinProbability(0.7f);

  for (int i = 0; i < 10; ++i) {
	  if (bulldozer3.tossCoin()) {
		  std::cout << "destroy" << std::endl;
	  }
	  else {
		  std::cout << "do not destroy" << std::endl;
	  }
  }


	//twixt::Game newGame;
	//std::cout << newGame.getPlayer1().getNrOfAvailableBridges();
	//newGame.modifySizeofBoard(12);
	//twixt:: Player player1 =  newGame.getPlayer1();

	//if (player1.getColor() == twixt::Player::EColor::RED) {
	//	std::cout << "red";
	//}
	return 0;
}
