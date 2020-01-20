#include <iostream>

using namespace std;

double factorial(int input){
    double result = input;
    int current = input - 1;
    while (current > 0){
        result = result * current;
        current -= 1;
    }
    return result;
}

int main()
{
  int total_balls, drawn_balls;
  cout << "Enter the total number of lottery balls: ";
  cin >> total_balls;
  cout << "Enter the number of drawn balls: ";
  cin >> drawn_balls;

  if (total_balls < 0 or drawn_balls < 0){
      cout << "The number of balls must be positive." << endl;
  }

  else if (total_balls < drawn_balls){
      cout << "The maximum number of drawn balls is the total amount of balls." << endl;
  }

  else{
    double total_factorial, drawn_factorial, difference_factorial, result;
    total_factorial = factorial(total_balls);
    drawn_factorial = factorial(drawn_balls);
    difference_factorial = factorial(total_balls - drawn_balls);
    result = total_factorial / (drawn_factorial * difference_factorial);

    cout << "The probability of guessing all " << total_balls << " balls correctly is 1/" << result << endl;
  }
}
