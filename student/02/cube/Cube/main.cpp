#include <iostream>

using namespace std;

int main()
{
    int input, cube;
    cout << "Enter a number: ";
    cin >> input;
    cube = input * input * input;
    if (cube / input / input != input){
        cout << "Error! The cube of " << input << " is not " << cube << endl;
    }
    else{
        cout << "The cube of " << input << " is " << cube << endl;
    }
}
