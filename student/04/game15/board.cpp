/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
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

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;


Board::Board(bool random_board): is_working_correctly(true), grid_(), is_random_initialization_(random_board)
{
    if (is_random_initialization_ == true){
        Board::random_initialization();
    }
    else{
        Board::user_initialization();
    }
}


void Board::build_board(std::vector<unsigned int>& values)
{
    // Going through a vector and placing the values in to the grid_ - 2dimensional vector for storing the game board
    int values_index = 0;
    for(int i = 0;i < SIZE;i++)
       {
           vector<unsigned int> temp;
           for(int j = 0;j < SIZE;j++)
           {
               temp.push_back(values.at(values_index));
               ++ values_index;

           }
           grid_.push_back(temp);
       }
   /* Test print:
    * for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
           cout << grid_[i][j] << " ";
       }
       cout << endl;
    } */
}

void Board::random_initialization()
{
    // Creating the board with a seed given by the player or taken from the clock.
    cout << "Enter a seed value (or an empty line): ";
    string seed_value = "";
    int seed;
    cin.ignore();
    getline(std::cin, seed_value);
    if( seed_value == "") {
        // If the user did not give a seed value, use computer time as the seed value.
        seed = time(NULL);
    } else {
        // If the user gave a seed value, use it.
        seed = stoi(seed_value);
    }
    std::vector<unsigned int> order = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // cout << seed << endl;    Test print
    Board::my_shuffle(order, seed);
    Board::build_board(order);

}

int Board::user_initialization()
{
    // Creating the board with values given by the player and checking all the numbers 1-16 are in the set of numbers given.
    std::vector <unsigned int> user_order;
    cout << "Enter the numbers 1-16 in a desired order (16 means empty):" << endl;
    unsigned int line;

    for (int i = 0; i < 16; ++i)
    {
        cin >> line;
        user_order.push_back(line);

    }
    // cout << "works" << endl;     Test print
    std::vector <unsigned int> ordered = user_order;
    std::sort(ordered.begin(), ordered.end());
    for (unsigned int i = 0; i < 16; ++i){
        if (ordered.at(i) != i + 1){
            cout << "Number " << i + 1 << " is missing" << endl;
            is_working_correctly = false;
            return EXIT_FAILURE;
        }
    }

    // cout << "checked" << endl;   Test print

    Board::build_board(user_order);
    return EXIT_SUCCESS;
}

void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}

void Board::move_piece(char direction, unsigned int moving_piece)
{
    // Finding the piece that the user wants to move from the 2-dimensional vector.
    int row = 0, column = 0;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (grid_.at(i).at(j) == moving_piece){
                row = i;
                column = j;
                i = SIZE;
                break;
            }

        }
    }

    // Changing the places of the hole and piece that is moving.
    int moving_to_row = row, moving_to_column = column;
    bool is_possible = false;
    if (direction == 'a'){
        if (grid_[row][column - 1] == 16){
            --moving_to_column;
            is_possible = true;
        }
    }
    if (direction == 'd'){
        if (grid_[row][column + 1] == 16){
            ++moving_to_column;
            is_possible = true;
        }

    }
    if (direction == 's' and row != SIZE - 1){
         if(grid_[row + 1][column] == 16){
            ++moving_to_row;
             is_possible = true;
         }
    }
    if (direction == 'w' and row != 0){
        if(grid_[row - 1][column] == 16) {
            --moving_to_row;
            is_possible = true;
        }
    }
    // cout << direction << endl;   Test print
    if (is_possible){
        grid_[moving_to_row][moving_to_column] = moving_piece;
        grid_[row][column] = 16;
    }
    else{
        cout << "Impossible direction: " << direction << endl;
    }
}

bool Board::is_game_won()
{
    // Checking if game is over by going through the grid_ and seeing if it's in order.
    unsigned int checking = 1;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (grid_[i][j] != checking){
                return false;
            }
            ++ checking;
        }
    }
    return true;
}

bool Board::is_game_winnable()
{
    // Finding the 'hole' from the gmame board
    int row = 0, column = 0, moving_row;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (grid_[i][j] == 16){
                row = i;
                column = j;
                i = SIZE;
                break;
            }
        }
    }

    // Moving the 'hole' to the bottom row
    for (moving_row = row + 1; moving_row < SIZE; ++moving_row){
        Board::move_piece('w', grid_[moving_row][column]);
    }

    // Calculating the number of inversions
    unsigned int checking, against, inversions = 0;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            checking = grid_[i][j];
            if (checking != 16){
                // cout << checking << endl;    Test print

                // First checking rest of the row where the current number is located
                for (int m = j; m < SIZE; ++m){
                    against = grid_[i][j];
                    if (checking > against){
                        ++inversions;
                    }
                }

                // Second checking all remaining rows for inversions
                for (int k = i + 1; k < SIZE; ++k){
                    for (int l = 0; l < SIZE; ++l){
                        against = grid_[k][l];
                        // cout << against << endl;     Test print
                        if (checking > against){
                            ++inversions;
                            // cout << checking << " " << against << endl;  Test print
                        }
                    }
                }
            }
        }
    }

    // Moving the hole back to it's original location
    --moving_row;
    while (moving_row != row){
        --moving_row;
        Board::move_piece('s', grid_[moving_row][column]);
    }

    // Calculating whether there are an odd or even number of inversions and returning a corresponding value
    if (inversions % 2 == 0){
        return true;
    }
    else{
        return false;
    }
}
