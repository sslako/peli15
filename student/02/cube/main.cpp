#include <iostream>

using namespace std;

int main()
{
    int input, cube;
    cout << "Enter a number: ";
    cin >> input;
    if (input == 0){
        cout << "The cube of 0 is 0." << endl;
    }
    else{
        cube = input * input * input;
        if (cube / input / input != input){
            cout << "Error! The cube of " << input << " is not " << cube << "." << endl;
        }
        else{
            cout << "The cube of " << input << " is " << cube << "." << endl;
        }
    }
}
