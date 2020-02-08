/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
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

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;


Board::Board(bool random_board): is_random_initialization_(random_board), grid_(), is_working_correctly(true)
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
    int values_index = 0;
    for(int i = 0;i < SIZE;i++)
       {
           vector<unsigned int> temp;
           for(int j = 0;j < SIZE;j++)
           {
               temp.push_back(values.at(values_index));
               ++ values_index;

           }
           //cout<<typeid(temp).name()<<endl;
           grid_.push_back(temp);
       }
   for(int i = 0; i < SIZE; i++){
       for(int j = 0; j < SIZE; j++){
           cout << grid_[i][j] << " ";
       }
       cout << endl;
    }
}

void Board::random_initialization()
{
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
    cout << seed << endl;
    Board::my_shuffle(order, seed);
    Board::build_board(order);

}

int Board::user_initialization()
{
    std::vector <unsigned int> user_order;
    cout << "Enter the numbers 1-16 in a desired order (16 means empty):" << endl;
    unsigned int line;

    for (int i = 0; i < 16; ++i)
    {
        cin >> line;
        user_order.push_back(line);

    }
    cout << "works" << endl;
    std::vector <unsigned int> ordered = user_order;
    std::sort(ordered.begin(), ordered.end());
    for (unsigned int i = 0; i < 16; ++i){
        if (ordered.at(i) != i + 1){
            cout << "Number " << i + 1 << " is missing" << endl;
            is_working_correctly = false;
            return EXIT_FAILURE;
        }
    }

    cout << "checked" << endl;

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
    int row, column;
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

    int moving_to_row = row, moving_to_column = column;
    if (direction == 'a'){
        --moving_to_column;
    }
    if (direction == 'd'){
        ++moving_to_column;
    }
    if (direction == 's'){
        ++moving_to_row;
    }
    if (direction == 'w'){
        --moving_to_row;
    }

    grid_[moving_to_row][moving_to_column] = moving_piece;
    grid_[row][column] = 16;
}

