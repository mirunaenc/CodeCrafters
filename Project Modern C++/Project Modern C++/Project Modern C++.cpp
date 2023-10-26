
import pylon;
#include <iostream>

int main()
{

    /*uint8_t x = 10, y = 12;*/
    twixt::Pylon pilon1{ 10,10 };
    twixt::Pylon pilon{};
    pilon1 = pilon;
    std::cout << pilon1.getLine();
    std::cout << pilon1.getLine();//test commit
    pilon = pilon1;

}
