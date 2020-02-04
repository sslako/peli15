#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector<std::string> split(std::string line, char separator, bool no_spaces = false){
    char current;
    std::string provisional = "";
    std::string::size_type i = 0;
    std::vector<std::string> characters;
    while (true){
        current = line.at(i);
        if (current != separator){
            provisional += current;
        }
        else{
            if (provisional != ""){
                characters.push_back(provisional);
                provisional = "";
            }
            else{
                if (no_spaces == false){
                    characters.push_back(" ");
                }
            }
        }
        i += 1;
        if (line.length() == i){
            if (line.at(i - 1) != separator){
                characters.push_back(provisional);
            }
            else if (line.at(i-2) == separator and no_spaces == false){
                characters.push_back("");
            }
            return characters;
        }


    }
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
