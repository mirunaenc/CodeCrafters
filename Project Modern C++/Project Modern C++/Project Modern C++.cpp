
import pylon;
import bridge;
#include <iostream>

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
    std::cout << bridge1.getEnd().first;
}
