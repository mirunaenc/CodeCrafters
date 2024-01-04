#include <iostream>
#include "utility.h"
#include "bulldozer.h"
#include "game.h"
#include "pylon.h"
#include "bridge.h"
#include "board.h"
#include "player.h"

int main()
{
   
   twixt::Game twixtGame;
   twixtGame.run();


	//twixt::Board board(10);
	//twixt::Pylon pylon1{ 1,1 };
	//twixt::Pylon pylon2{ 2,3 };

	//twixt::Pylon pylon3{ 2,1 }; //  intersect
 //   twixt::Pylon pylon4{ 1,3 };
	//// 
	//// 
	////twixt::Pylon pylon3{ 0,1 }; // dont intersect
	////twixt::Pylon pylon4{ 1,3 };

	////twixt::Pylon pylon3{ 2,1 };   // dont intersect
 //  // twixt::Pylon pylon4{ 0,2 };  
	//
	////twixt::Pylon pylon3{ 3,0 };  
	////twixt::Pylon pylon4{ 4,2 };  // dont intersect


	////twixt::Pylon pylon3{ 2,1 }; // dont intersect 
	////twixt::Pylon pylon4{ 0,0 }; 

	/*twixt::Pylon p1(1, 1);
	twixt::Pylon p2(3, 2);
	twixt::Pylon p3(1, 2);
	twixt::Pylon p4(3, 1);
	
	twixt::Bridge b1(p1, p2);
	twixt::Bridge b2(p3, p4);

	if (b1.intersectsWith(b2))
		std::cout << "Intersects";
	else
		std::cout << "Doesn't intersect";*/

 
	return 0;
}
