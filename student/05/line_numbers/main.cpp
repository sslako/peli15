#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string name_input, name_output;
    cout << "Input file: ";
    cin >> name_input;
    cout << "Output file: ";
    cin >> name_output;

    ifstream input_file;
    ofstream output_file;

    input_file.open(name_input);
    output_file.open(name_output);

    if (not input_file){
        cout << "Error! The file " << name_input << "cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else if (not output_file){
        cout<< "Error! The file " << name_output << "cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else{
        int row_number = 1;
        string row;
        while (getline(input_file, row)){
            output_file << row_number << " " << row << endl;
            ++row_number;
        }
    }
    output_file.close();
    input_file.close();
    return EXIT_SUCCESS;
}
