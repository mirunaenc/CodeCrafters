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
   
   // twixt::Game twixtGame;
   // twixtGame.run();


	twixt::Board board(10);
	twixt::Pylon pylon1{ 1,1 };
	twixt::Pylon pylon2{ 2,3 };

	twixt::Pylon pylon3{ 2,1 }; //  intersect
    twixt::Pylon pylon4{ 1,3 };
	// 
	// 
	//twixt::Pylon pylon3{ 0,1 }; // dont intersect
	//twixt::Pylon pylon4{ 1,3 };

	//twixt::Pylon pylon3{ 2,1 };   // dont intersect
   // twixt::Pylon pylon4{ 0,2 };  
	
	//twixt::Pylon pylon3{ 3,0 };  
	//twixt::Pylon pylon4{ 4,2 };  // dont intersect


	//twixt::Pylon pylon3{ 2,1 }; // dont intersect 
	//twixt::Pylon pylon4{ 0,0 }; 
	

	twixt::Bridge bridge1(pylon1,pylon2);
	twixt::Bridge bridge2(pylon3,pylon4);


	if (bridge1.intersectsWith(bridge2)) {
		std::cout << "Bridges intersect." << std::endl;
	}
	else {
		std::cout << "Bridges do not intersect." << std::endl;
	}


	return 0;
}
