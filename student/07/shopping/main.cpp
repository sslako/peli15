/* Shopping
 *
 * Desc:
 *  This program reads a source file and stores it's contents of stores and their
 * selections. These selections are used to print out the chains included, locations
 * in a specific chain, products in all stores and selection in a specific store. The
 * also is capable of searching the cheapest price for a specific product and displaying
 * its price in different stores.
 *
 * Program author
 * Name: Lauri Koivunen
 * Student number: 292028
 * UserID: sslako
 * E-Mail: lauri.j.koivunen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * The fundamental data base to which the input file is read is stored as a
 * map <string, map<string, vector<Product>>>. The first map tracks the chain
 * and the second, nested map, a specific location in the chain. The inner map
 * contains a vector with struct Products that contain the name and price of
 * the products in the store.
 *
 * The program uses the constant OUT_OF_STOCK to track which items are not available.
 * Its value is specified as -1. This shouldn't cause issues since -1 is not an expected
 * price for a product.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

double const OUT_OF_STOCK = -1;

// Stores the information of singular products includes the name and price of a product
struct Product {
    string product_name;
    double price;

    // Operator for ordering the structs for the purposes of the selection command
    bool operator<(const Product& other) const
    {
        return product_name < other.product_name;
    }

    // Method used when reading input file if the same location has the same product listed multiple times
    void change_price(double new_price){
        price = new_price;
    }
};

// Split function from course material for splitting inputs into vectors
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

// Assistant function for reading input file and seeing if a store already has a product
// Returns the position of the item in the input vector or -1 if it's not included
int find_product(vector<Product>& source, string target){
    for (unsigned int pos = 0; pos < source.size(); ++pos){
        if (source.at(pos).product_name == target){
            return pos;
        }
    }
    return -1;
}

// Function for reading the input file and storing it
int read_input_file(map <string, map<string, vector<Product>>>& data_base){
    // Asking for the file to be read
    string name_input;
    cout << "Input file: ";
    cin >> name_input;
    ifstream input_file;

    input_file.open(name_input);

    // Checking if file of the name excists and quitting program if needed
    if (not input_file){
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

    // Reading one line of input file at a time and storing it
    string row, chain, location, product_name;
    double price;
    vector<string> parts;
    while (getline(input_file, row)){

        // Checking if input line includes necessary fields
        parts = split(row, ';');
        if (parts.size() == 4 and parts.at(0) != "" and parts.at(1) != "" and parts.at(2) != "" and parts.at(3) != ""){

            // Separating all the fields to their own values to be stored
            chain = parts.at(0);
            location = parts.at(1);
            product_name = parts.at(2);
            // CHecking if there is price and setting it accordingly
            if (parts.at(3) == "out-of-stock"){
                price = OUT_OF_STOCK;
            }
            else{
                price = stod(parts.at(3));
            }

            // Checking if a product already excists in a location
            vector<Product>& items_at_location = data_base[chain][location];
            int position = find_product(items_at_location, product_name);
            if (position != -1){
                // Altering price of an existing prodict struct
                Product& current_product = items_at_location[position];
                current_product.change_price(price);
                // cout << current_product.price << endl;
            }

            else{
                // Creating a new product and storing it in the data structure
                Product temp;
                temp = {product_name, price};
                data_base[chain][location].push_back(temp);
            }
        }
        else{
            cout << "Error: the input file has an erroneous line" << endl;
            input_file.close();
            return false;
        }
    }
    input_file.close();
    return true;
}

// Command for printing out names of all the chains in the data base
void print_chains(map <string, map<string, vector<Product>>>& data_base){
    for (auto chain : data_base){
        cout << chain.first << endl;
    }
}

// Command for printing out the locations of a specific chain
void print_stores (map <string, map<string, vector<Product>>> data_base, vector <string> command_parts){
    string chain = command_parts.at(0);
    // Checking if the chain excists in the data base
    if (data_base.find(chain) == data_base.end()){
        cout << "Error: unknown chain name" << endl;
        return;
    }

    // Printing the names of all the chains
    map<string, vector<Product>> chain_locations = data_base[chain];
    for (auto location : chain_locations){
        cout << location.first << endl;
    }

}

// Command to print names of all the products in the system
void print_products(map <string, map<string, vector<Product>>> data_base){
    set <string> all_products;
    // Going through the entire data base and putting the names of all products in a set
    for (auto chain : data_base){
        for (auto store : chain.second){
            vector <Product> products;
            products = store.second;
            for (Product item : products){
                all_products.insert(item.product_name);
            }
        }
    }

    // Printing all the product names found
    for (string product : all_products){
        cout << product << endl;
    }
}

// Command for printing all products in a location
void print_selection(map <string, map<string, vector<Product>>>& data_base, vector <string> specifications){
    string chain, store;
    chain = specifications.at(0);
    store = specifications.at(1);

    // CHecking if the chain excists in the data base
    if (data_base.find(chain) == data_base.end()){
        cout << "Error: unknown chain name" << endl;
        return;
    }

    // Checking if the store location excists in the data base
    if (data_base[chain].find(store) == data_base[chain].end()){
        cout << "Error: unknown store" << endl;
        return;
    }

    vector <Product> selection = data_base[chain][store];

    cout << fixed;
    cout << setprecision(2);

    // Printing out all the products in the location
    sort(selection.begin(), selection.end());
    for (Product item : selection){

        string name = item.product_name;
        double price = item.price;

        // Checking if the price excists and printing accordingly
        if (price == OUT_OF_STOCK){
            cout << name << " out of stock" << endl;
        }
        else{
            cout << name << " " << price << endl;
        }
    }
}

// Command for finding the store with the cheapest price for a specific product
void find_cheapest(map <string, map<string, vector<Product>>> data_base, vector<string> specifications){
    string product = specifications.at(0);
    double cheapest_price = -1;
    map <string, vector<string>> stores_with_cheapest_price;
    bool is_out_of_stock = false;
    // Going through all stores and seeing if they have the desired product and at what price
    for (auto chain : data_base){
        for (auto store : chain.second){
            vector <Product> products;
            products = store.second;
            for (Product item : products){
                if (item.product_name == product){
                    double current_price = item.price;

                    // Checking what the price is and if it's smaller than what was already found
                    if (current_price == OUT_OF_STOCK){
                        is_out_of_stock = true;
                    }
                    else if (current_price < cheapest_price or cheapest_price == -1){
                        cheapest_price = current_price;
                        stores_with_cheapest_price.clear();
                        stores_with_cheapest_price[chain.first].push_back(store.first);
                    }
                    else if (current_price == cheapest_price){
                        stores_with_cheapest_price[chain.first].push_back(store.first);
                    }
                    break;
                }
            }
        }
    }
    // Printing info if no store has the product available
    if (stores_with_cheapest_price.empty()){
        if (is_out_of_stock){
            cout << "The product is temporarily out of stock everywhere" << endl;
        }
        else{
            cout << "The product is not part of product selection" << endl;
        }
    }
    // Printing the cheapest price and which locations had it
    else{
        cout << fixed;
        cout << setprecision(2);
        cout << cheapest_price << " euros" << endl;
        for (auto chain : stores_with_cheapest_price){
            for (auto store : chain.second){
                cout << chain.first << " " << store << endl;
            }
        }
    }
}

int main()
{
    // Initializing the data structure and reading the input file
    map <string, map<string, vector<Product>>> data_base;
    if (not read_input_file(data_base)){
        return EXIT_FAILURE;
    }

    string command;
    while (true){
        // Reading user's command
        cout << "> ";
        cin >> command;

        string specifications;
        vector <string> command_parts;
        getline(cin, specifications);
        command_parts = split(specifications, ' ', true);

        // Executing the appropriate command based on input
        if (command == "quit"){
            return EXIT_SUCCESS;
        }

        else if (command == "chains"){
            // cout << "Chains command not yet implemented" << endl;
            if (command_parts.size() == 0){
                print_chains(data_base);
            }
            else{
                cout << "Error: error in command chains" << endl;
            }
        }

        else if (command == "products"){
            // cout << "Products command not yet implemented" << endl;
            if (command_parts.size() == 0){
                print_products(data_base);
            }
            else{
                cout << "Error: error in command products" << endl;
            }
        }

        else if (command == "stores"){
            // cout << "Stores command not yet implemented" << endl;
            if (command_parts.size() == 1){
                print_stores(data_base, command_parts);
            }
            else{
                cout << "Error: error in command stores" << endl;
            }
        }

        else if (command == "cheapest"){
            if (command_parts.size() == 1){
                //cout << "Cheapest command not yet implemented" << endl;
                find_cheapest(data_base, command_parts);

            }
            else{
                cout << "Error: error in command cheapest" << endl;
            }
        }

        else if (command == "selection"){
            if (command_parts.size() == 2){
                // cout << "Selection command not yet implemented" << endl;
                print_selection(data_base, command_parts);
            }
            else{
                cout << "Error: error in command selection" << endl;
            }
        }

        else{
            cout << "Error: unknown command: " << command << endl;
        }
    }
}
