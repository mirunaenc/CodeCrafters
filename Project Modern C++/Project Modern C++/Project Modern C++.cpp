
import pylon;
import bridge;
import board;

#include <iostream>
#include"bulldozer.h"

int main()
{

    twixt::Pylon pilon1{ 10,10 };
    twixt::Pylon pilon{12,13};
    pilon1 = pilon;
    //std::cout << pilon1.getLine();
    //std::cout << pilon1.getLine();//test commit
    pilon = pilon1;
    pilon1.setColumn(3);
    twixt::Bridge bridge1(pilon1,pilon);
    //std::cout << bridge1.getEnd().first;
	
	if (bridge1.isConnectedTo(pilon1)) {
		std::cout << "Podul este conectat la pilon1.\n";
	}
	else {
		std::cout << "Podul nu este conectat la pilon1.\n";
	}

    
 /*   twixt::Board board(10);
    twixt::Board board2;
    board2 = board;
board2.setPylon(1, 1, twixt::Pylon(1, 1));
board2.setPylon(3, 0, twixt::Pylon(3, 0));
board2.setPylon(2, 0, twixt::Pylon(2, 0));
board2.setPylon(2, 1, twixt::Pylon(2, 1));
board2.resetPosition(2, 1);
board2.resetPosition(2, 0);
  board = board2;

  twixt::Bulldozer bulldozer(board,4,2);
  twixt::Bulldozer bulldozer2(bulldozer);
  bulldozer.setLinePosition(1);*/

	return 0;
}
