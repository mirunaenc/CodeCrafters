import pylon;
import bridge;
import board;
import player;

#include <iostream>
#include"bulldozer.h"
#include"game.h"

int main()
{
	  
    twixt::Board board2(3);

    board2.setPylon(1, 1, twixt::Pylon(1, 1));
    board2.setPylon(2, 0, twixt::Pylon(2, 0));
    board2.setPylon(1, 0, twixt::Pylon(1, 0));
    board2.setPylon(2, 1, twixt::Pylon(2, 1));



  twixt::Bulldozer bulldozer(board2,3,2,0.3f);
 

  for (int i = 0; i < 10; ++i)
  {
	  bulldozer.moveToEmptyPosition();
  }

  //for (int i = 0; i < 10; ++i) {
	 // if (bulldozer3.tossCoin()) {
		//  std::cout << "destroy" << std::endl;
	 // }
	 // else {
		//  std::cout << "do not destroy" << std::endl;
	 // }
  //}


	return 0;
}
