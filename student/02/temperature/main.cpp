#include <iostream>

using namespace std;

int main()
{
    int input;
    cout << "Enter a temperature: ";
    cin >> input;
    cout << input << " degrees Celsius is " << input * 1.8 + 32 << " degrees Fahrenheit" << endl;
    cout << input << " degrees Fahrenheit is " << (input - 32) / 1.8 << " degrees Celsius" << endl;
    // Write your code here

    return 0;
}
