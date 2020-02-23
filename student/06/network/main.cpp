#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
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

void print_subnetwork(map <string, vector <string>>& recruiters, string name, int level = 1){
    cout << name << endl;
    for (string person : recruiters[name]){
        for (int i = 0; i < level; ++i){
            cout << "..";
        }
        print_subnetwork(recruiters, person, level + 1);
    }
}

int count_subnetwork(map <string, vector <string>>& recruiters, string name){
    int total_network = 1;
    for (string person : recruiters[name]){
        total_network += count_subnetwork(recruiters, person);
    }
    return total_network;
}

int find_deepest_chain(map <string, vector <string>>& recruiters, string name){
    int deepest_chain = 0;
    int provisional = 1;
    for (string person : recruiters[name]){
        provisional += find_deepest_chain(recruiters, person);
        if(provisional > deepest_chain){
            deepest_chain = provisional;
            provisional = 1;
        }
    }
    return deepest_chain;
}

int main()
{
    // TODO: Implement the datastructure here

    map <string, vector <string>> recruiters;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            recruiters[id1].push_back(id2);


        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print_subnetwork(recruiters, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout << count_subnetwork(recruiters, id) - 1 << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            cout << find_deepest_chain(recruiters, id) + 1 << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
