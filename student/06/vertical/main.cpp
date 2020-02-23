#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC;
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here
    int divisor = 1;
    unsigned int remainder = 0;
    while (remainder != num){
        divisor *= 10 ;
        remainder = num % divisor;
    }
    divisor /= 10;
    unsigned int current_digit = num /divisor;
    cout << current_digit << endl;
    if (num != current_digit){
        unsigned int new_num = num - divisor * current_digit;
        int check_divisor = 1;
        remainder = 0;
        while (remainder != new_num){
            check_divisor *= 10 ;
            remainder = new_num % check_divisor;
        }
        while (check_divisor != divisor){
            cout << 0 << endl;
            check_divisor *= 10;
        }
        print_vertical(new_num);
    }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
