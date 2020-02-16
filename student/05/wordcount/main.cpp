#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>

using namespace std;

int main()
{
    string input_file_name;
    cout << "Input file: ";
    cin >> input_file_name;

    ifstream input_file;
    input_file.open(input_file_name);

    if (not input_file){
        cout << "Error! The file " << input_file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    // things

    string row, current_word, input;
    int row_number = 1, next_space = 0;
    map <string, set <int>> tally;
    while (getline(input_file, input)){
        row = input;
        while (next_space != -1){
            next_space = row.find_first_of(" ");
            current_word = row.substr(0, next_space);
            tally[current_word].insert(row_number);
            row.erase(0, next_space + 1);
        }
        ++row_number;
        next_space = 0;
    }

    // printout

    for (auto info : tally){
        cout << info.first << ": ";
        set <int> all_rows = info.second;
        for (int rows : all_rows){
            all_rows.erase(rows);
            if (all_rows.empty()){
                cout << rows << endl;
            }
            else{
                cout << rows << ", ";
            }
        }
    }

    //end

    input_file.close();
    return EXIT_SUCCESS;

}
