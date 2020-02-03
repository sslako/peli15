#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector < int >& ints){
    int first = ints.at(0);
    std::vector<int>::size_type length = ints.size();
    for (long unsigned int i = 1; i < length; ++i){
        int current = ints.at(i);
        if (first != current){
            return false;
        }
    }
    return true;
}


bool is_ordered_non_strict_ascending(std::vector < int >& ints){
    std::vector<int>::size_type length = ints.size();
    for (long unsigned int i = 1; i < length; ++i){
        int previous = ints.at(i - 1), current = ints.at(i);
        if (previous > current){
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(std::vector < int >& ints){
    std::vector<int>::size_type length = ints.size();
    int current = ints.at(1), previous = ints.at(0);
    int compare_ratio = current - previous;
    for (long unsigned int i = 1; i < length; ++i){
        previous = ints.at(i - 1);
        current = ints.at(i);
        int new_ratio = current - previous;
        if (new_ratio != compare_ratio){
            return false;
        }
    }
    return true;
}


bool is_geometric_series(std::vector < int >& ints){
    std::vector<int>::size_type length = ints.size();
    int current = ints.at(1), previous = ints.at(0);
    double compare_ratio = current / previous;
    for (long unsigned int i = 1; i < length; ++i){
        previous = ints.at(i - 1);
        current = ints.at(i);
        double new_ratio = current / previous;
        if (new_ratio != compare_ratio){
            return false;
        }
    }
    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
