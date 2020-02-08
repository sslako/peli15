/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
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
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way
    bool is_working_correctly;

    Board(bool random_board);
    // Prints the game grid
    void print();

    // Moves a piece to the empty spot

    void move_piece(char direction, unsigned int moving_piece);

    // Method for checking if the board is in order and the player has won

    bool is_game_won();

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
