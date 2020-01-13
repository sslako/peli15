#include <iostream>


int main()
{
    int input, toprint = 1;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> input;
    while(toprint <= input){
        if (toprint % 3 == 0){
            std::cout << "zip" << std::endl;
        }
        else{
            std::cout << toprint << std::endl;
        }
        ++toprint;
    }
}
