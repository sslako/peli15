#include <iostream>
#include <string>
#include <map>
#include <fstream>

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
    string row, name;
    string::size_type split_position;
    int points;
    map <string, int> tally;
    while (getline(input_file, row)){
        split_position = row.find(":");
        name = row.substr(0, split_position - 1);
        points = stoi(row.substr(split_position + 1));
        if (tally.find(name) != tally.end()){
            tally.insert({name, points});
        }
        else{
            tally.at(name) += points;
        }
    }
    for (auto pair : tally){
        cout << pair.first << ": " << pair.second << endl;
    }

    input_file.close();
    return EXIT_SUCCESS;
}
