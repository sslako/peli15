#include <iostream>


int main()
{
    int input, toprint = 1;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> input;
    while(toprint <= input){
        std::cout << toprint << std::endl;
        ++ toprint;
    }
}
