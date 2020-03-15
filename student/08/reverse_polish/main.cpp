#include <iostream>

using namespace std;

int main()
{
    int stack[80];
    int* pos;
    pos = stack;
    char line;
    string temp;
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    while(cin >> line){
        if (line == '#'){
            break;
        }
        else{
            temp += line;
        }
    }
    int a, b;
    char first = temp.at(0);
    if (first == '+' or first == '-' or first == '*' or first == '/'){
        cout << "Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    }
    for(char thing : temp){
        if (thing >= '0' && thing <= '9'){
            *pos = (int)thing - 48;
            ++pos;
        }
        else if (thing == '+'){
            if ((pos - 1) == stack){
                cout << "Error: Too few operands" << endl;
                return EXIT_FAILURE;
            }
            a = *(pos - 1);
            b = *(pos - 2);
            *(pos - 2) = a + b;
            *(pos - 1) = 0;
            --pos;
        }
        else if (thing == '-'){
            if ((pos - 1) == stack){
                cout << "Error: Too few operands" << endl;
                return EXIT_FAILURE;
            }
            b = *(pos - 1);
            a = *(pos - 2);
            *(pos - 2) = a - b;
            *(pos - 1) = 0;
            --pos;
        }
        else if (thing == '*'){
            if ((pos - 1) == stack){
                cout << "Error: Too few operands" << endl;
                return EXIT_FAILURE;
            }
            b = *(pos - 1);
            a = *(pos - 2);
            *(pos - 2) = a * b;
            *(pos - 1) = 0;
            --pos;
        }
        else if (thing == '/'){
            if ((pos - 1) == stack){
                cout << "Error: Too few operands" << endl;
                return EXIT_FAILURE;
            }
            b = *(pos - 1);
            a = *(pos - 2);
            if (b == 0){
                cout << "Error: Division by zero" << endl;
                return EXIT_FAILURE;
            }
            *(pos - 2) = a / b;
            *(pos - 1) = 0;
            --pos;
        }
        else{
            cout << "Error: Unknown character" << endl;
            return EXIT_FAILURE;
        }
    }
    --pos;
    if (pos != stack){
        cout << "Error: Too few operators" << endl;
        return EXIT_FAILURE;
    }
    cout << "Correct: " << *pos << " is the result" << endl;
    return EXIT_SUCCESS;
}
