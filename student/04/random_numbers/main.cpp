#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    std::default_random_engine rand_gen;

    std::cout << "Enter a seed value or an empty line: ";
    std::string seed_value = "";
    getline(std::cin, seed_value);

    cout << endl;

    if( seed_value == "" ) {
        // If the user did not give a seed value, use computer time as the seed value.
        rand_gen.seed( time(NULL) );
    } else {
        // If the user gave a seed value, use it.
        rand_gen.seed( stoi(seed_value) );
    }

    // Filling the board with random numbers between 0 and 4
    // These random numbers correspond to the amount of water, i.e. the possible values of CHARACTERS
    std::uniform_int_distribution<int> distribution(lower, upper);
    string keep_going;
    while (true){
        cout << "Your drawn random number is " << distribution(rand_gen) << endl;
        cout << "Press enter to continue or q to quit: ";
        getline(cin, keep_going);
        if (keep_going == "q"){
            return;
        }
        cout << endl;
    }


}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    // Reading the line feed, which was left unread by >> operator above.
    // This is necessary since the seed value will be read by getline
    // in the function produce_random_numbers.
    string line_feed = "";
    getline(cin, line_feed);

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
