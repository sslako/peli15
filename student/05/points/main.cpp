#include <iostream>
#include <string>
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
        cout << "Error! The " << input_file_name << "cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    string row, name;
    string::size_type split_position;
    int points;
    map <string, int> tally;
    while (getline(input_file, row)){
        split_position = row.find(":");
        name = row.substr(row.begin(), split_position - 1);
        points = stoi(row.substr(split_position + 1, row.end()));
        if (not tally.find(name)){
            tally = {name, points};
        }
        else{
            tally.at(name) += points;
        }
    }
    for (auto pair : tally){
        cout << pair.first() << ": " << pair.second << endl;
    }

    return EXIT_SUCCESS;
}
