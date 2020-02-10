/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author
 * Name: Lauri Koivunen
 * Student number: 292028
 * UserID: sslako
 * E-Mail: lauri.j.koivunen@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <iostream>

using namespace std;

const int SIZE = 4;

class Board
{
public:
    // Attribute for telling the main function if the user-dictated board was generated correctly

    bool is_working_correctly;

    // Class initializing function, splits into two different functions depending on method of initialization

    Board(bool random_board);

    // Prints the game grid

    void print();

    // Moves a piece to the empty spot

    void move_piece(char direction, unsigned int moving_piece);

    // Method for checking if the board is in order and the player has won

    bool is_game_won();

    // Method used at the beginning of the game to see if the game is winnable

    bool is_game_winnable();

private:
    // Game grid for the 15 puzzle

    std::vector<std::vector<unsigned int>> grid_;

    // Attribute for determining the initialization of the board

    bool is_random_initialization_;

    // Shuffles the numbers vector by using seed as a seed value

    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Takes a vector with generated values and places them into the grid_ vector

    void build_board(std::vector<unsigned int>& values);

    // Creates the game board in a random fashion with the help of my_shuffle

    void random_initialization();

    // Creates the game board in the order that the user inputs numbers

    int user_initialization();

};

#endif // BOARD_HH
