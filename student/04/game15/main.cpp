/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Lauri Koivunen
 * Student number: 292028
 * UserID: sslako ( Necessary due to gitlab folder naming. )
 * E-Mail: lauri.j.koivunen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <string>
#include <iostream>
using namespace std;

// More functions

int main()
{
    // More functionality
    string input = "";
    bool is_random;

    while (true){
        cout << "Random initialization (y/n): ";
        cin >> input;
        if (input == "y" or input == "Y"){
            is_random = true;
            break;
        }
        else if (input == "n" or input == "N"){
            is_random = false;
            break;
        }
    }
    Board play_area = Board(is_random);
    if (play_area.is_working_correctly == false){
        return EXIT_FAILURE;
    }

    char command;
    unsigned int number;
    while(true){
            play_area.print();
            cout << "Dir (command, number): " << endl;
            cin >> command;
            if (command == 'q'){
                return EXIT_SUCCESS;
            }
            cin >> number;
            cout << command << number << endl;
            play_area.move_piece(command, number);
    }

    return EXIT_SUCCESS;
}
