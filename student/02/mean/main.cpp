#include <iostream>

// Write here a function counting the mean value

int main()
{
    int numbers, newest;
    double mean, total;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    std::cin >> numbers;
    if (numbers > 0){
        for (int luku = 1; luku <= numbers; ++luku){
            std::cout << "Input " << luku << ". number: ";
            std::cin >> newest;
            total += newest;
            // std::cout << total << std::endl;
        }
        mean = total / numbers;
        std::cout << "Mean value of the given numbers is: " << mean << std::endl;
    }
    else{
        std::cout << "Cannot count mean value from " << numbers << " numbers" << std::endl;
    }
}
