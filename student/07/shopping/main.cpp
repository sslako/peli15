#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct Product {
    string product_name;
    double price;
    bool operator <(const Product& other )  {
           return product_name < other.product_name;
       }
    bool operator >(const Product& other )  {
        return product_name > other.product_name;
    }
    bool operator ==(const Product& other )  {
        return product_name == other.product_name;
    }
};

double const OUT_OF_STOCK = -1;

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

int find_product(vector<Product>& source, string target){
    for (unsigned int pos = 0; pos < source.size(); ++pos){
        if (source.at(pos).product_name == target){
            return pos;
        }
    }
    return -1;
}


int read_input_file(map <string, map<string, vector<Product>>>& data_base){
    string name_input;
    cout << "Input file: ";
    cin >> name_input;
    ifstream input_file;

    input_file.open(name_input);

    if (not input_file){
        cout << "Error! The input file cannot be opened." << endl;
        return false;
    }


    string row, chain, location, product_name;
    double price;
    vector<string> parts;
    while (getline(input_file, row)){
        parts = split(row, ';');
        if (parts.size() == 4 and parts.at(0) != "" and parts.at(1) != "" and parts.at(2) != "" and parts.at(3) != ""){
            chain = parts.at(0);
            location = parts.at(1);
            product_name = parts.at(2);
            if (parts.at(3) == "out-of-stock"){
                price = OUT_OF_STOCK;
            }
            else{
                price = stod(parts.at(3));
            }

            vector<Product> items_at_location = data_base[chain][location];
            int position = find_product(items_at_location, product_name);
            if (position != -1){
                Product current_product = items_at_location[position];
                current_product.price = price;
                // cout << current_product.price << endl;
            }

            else{
                Product temp;
                temp = {product_name, price};
                data_base[chain][location].push_back(temp);
            }
        }
        else{
            cout << "Error: the input file has an erroneous line" << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    map <string, map<string, vector<Product>>> data_base;
    if (not read_input_file(data_base)){
        return EXIT_FAILURE;
    }
    cin.ignore();
    string command;
    while (true){
        cout << "> ";
        getline(cin, command);

        if (command == "quit"){
            return EXIT_SUCCESS;
        }
        else if (command == "chains"){
            cout << "Chains command not yet implemented" << endl;
        }
        else if (command == "products"){
            cout << "Products command not yet implemented" << endl;
        }

        else{
            vector <string> command_parts;
            command_parts = split(command, ' ');


            if (command_parts.at(0) == "stores"){
                cout << "Stores command not yet implemented" << endl;
            }
            else if (command_parts.at(0) == "selection"){
                cout << "Selection command not yet implemented" << endl;
            }
            else if (command_parts.at(0) == "cheapest"){
                cout << "Cheapest command not yet implemented" << endl;
            }
            else{
                cout << "Error: unknown command: " << command << endl;
            }
        }
    }
}
