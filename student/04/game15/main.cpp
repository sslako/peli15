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
 * Program author
 * Name: Lauri Koivunen
 * Student number: 292028
 * UserID: sslako ( Necessary due to gitlab folder naming. )
 * E-Mail: lauri.j.koivunen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * The program has been mostly created in the class Board and the main function 
 * contains only some bits in it. All command asking is done in main and these 
 * values are then given to the class. 
 * */

#include "board.hh"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    // Determining the method for initializing the board and then creating it.
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
        else{
            cout << "Unknown choice: " << input << endl;
        }
    }
    Board play_area = Board(is_random);
    if (play_area.is_working_correctly == false){
        return EXIT_FAILURE;
    }

    // play_area.print();   Test print

   if (play_area.is_game_winnable() == false){
       cout << "Game is not solvable. What a pity." << endl;

        // play_area.print();   Test print

        return EXIT_SUCCESS;
    }

    // play_area.print();   Test print

    cout << "Game is solvable: Go ahead!" << endl;

    // The basic structure for completing a player's turn.
    string command;
    char command_char;
    unsigned int number;
    while(true){
        play_area.print();
        // Asking and forwarding the player's next move to the class.
        cout << "Dir (command, number): ";
        cin >> command;
        if (command == "q"){
            return EXIT_SUCCESS;
        }
        cin >> number;

        // Checking that the player's input is valid.
        if (command == "a" or command == "s" or command == "d" or command == "w"){
            if (number < 17 and number > 0){
                // cout << command << number << endl;   Test print
                command_char = command[0];
                play_area.move_piece(command_char, number);
            }
            else{
                cout << "Invalid number: " << number << endl;
            }
        }
        // Check for if the game is over and the player has won
        else{
            cout << "Unknown command: " << command << endl;
        }
        if (play_area.is_game_won() == true){
            play_area.print();
            cout << "You won!" << endl;
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
