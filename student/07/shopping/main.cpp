#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Product {
    string product_name;
    double price;
    bool operator<(const Product& other) const
    {
        return product_name < other.product_name;
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
        cout << "Error: The input file cannot be opened." << endl;
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
            input_file.close();
            return false;
        }
    }
    input_file.close();
    return true;
}

void print_chains(map <string, map<string, vector<Product>>>& data_base){
    for (auto chain : data_base){
        cout << chain.first << endl;
    }
}

void print_stores (map <string, map<string, vector<Product>>> data_base, vector <string> command_parts){
    string chain = command_parts.at(0);
    if (data_base.find(chain) == data_base.end()){
        cout << "Error: unknown chain name" << endl;
        return;
    }

    map<string, vector<Product>> chain_locations = data_base[chain];
    for (auto location : chain_locations){
        cout << location.first << endl;
    }

}

void print_products(map <string, map<string, vector<Product>>> data_base){
    set <string> all_products;
    for (auto chain : data_base){
        for (auto store : chain.second){
            vector <Product> products;
            products = store.second;
            for (Product item : products){
                all_products.insert(item.product_name);
            }
        }
    }
    for (string product : all_products){
        cout << product << endl;
    }
}

void print_selection(map <string, map<string, vector<Product>>>& data_base, vector <string> specifications){
    string chain, store;
    chain = specifications.at(0);
    store = specifications.at(1);

    if (data_base.find(chain) == data_base.end()){
        cout << "Error: unknown chain name" << endl;
        return;
    }

    if (data_base[chain].find(store) == data_base[chain].end()){
        cout << "Error: unknown store" << endl;
        return;
    }

    vector <Product> selection = data_base[chain][store];

    cout << fixed;
    cout << setprecision(2);

    sort(selection.begin(), selection.end());
    for (Product item : selection){

        string name = item.product_name;
        double price = item.price;

        if (price == OUT_OF_STOCK){
            cout << name << " out of stock" << endl;
        }
        else{
            cout << name << " " << price << endl;
        }
    }
}

void find_cheapest(map <string, map<string, vector<Product>>> data_base, vector<string> specifications){
    string product = specifications.at(0);
    double cheapest_price = -1;
    map <string, vector<string>> stores_with_cheapest_price;
    bool is_out_of_stock = false;
    for (auto chain : data_base){
        for (auto store : chain.second){
            vector <Product> products;
            products = store.second;
            for (Product item : products){
                if (item.product_name == product){
                    double current_price = item.price;
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
    if (stores_with_cheapest_price.empty()){
        if (is_out_of_stock){
            cout << "The product is temporarily out of stock everywhere" << endl;
        }
        else{
            cout << "The product is not part of product selection" << endl;
        }
    }
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
    map <string, map<string, vector<Product>>> data_base;
    if (not read_input_file(data_base)){
        return EXIT_FAILURE;
    }

    string command;
    while (true){
        cout << "> ";
        cin >> command;

        string specifications;
        vector <string> command_parts;
        getline(cin, specifications);
        command_parts = split(specifications, ' ', true);

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
