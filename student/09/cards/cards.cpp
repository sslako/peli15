#include "cards.hh"
#include <iostream>
using namespace std;

// TODO: Implement the methods here
// A dynamic structure must have a constructor
// that initializes the top item as nullptr.
Cards::Cards():top_(nullptr), bottom_(nullptr){
}

// Adds a new card with the given id as the topmost element.
void Cards::add(int id){
    Card_data* new_card = new Card_data{id, top_};
    if (bottom_ == nullptr){
        bottom_ = new_card;
    }
    top_ = new_card;
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the first element.
void Cards::print_from_top_to_bottom(std::ostream& s){
    Card_data* item_to_be_printed = top_;
    int running_number = 1;
    while ( item_to_be_printed != nullptr ) {
       s << running_number << ": " << item_to_be_printed->data<< endl;
       ++running_number;
       item_to_be_printed = item_to_be_printed->next;
    }
}

// Removes the topmost card and passes it in the reference parameter id.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id){
    if (top_ == nullptr){
        return false;
    }
    Card_data* card_to_be_removed = top_;
    top_ = card_to_be_removed->next;
    id = card_to_be_removed->data;
    delete card_to_be_removed;

    return true;
}

// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top(){
    if (top_ == nullptr){
        return false;
    }
    Card_data* second_last = top_;
    while(second_last->next != bottom_){
        second_last = second_last->next;
    }
    second_last->next = nullptr;
    bottom_->next = top_;
    top_ = bottom_;
    bottom_= second_last;

    return true;
}

// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom(){
    if (top_ == nullptr){
        return false;
    }
    Card_data* moving_card = top_;
    top_ = moving_card->next;
    bottom_->next = moving_card;
    moving_card->next = nullptr;
    bottom_ = moving_card;

    return true;
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the last element.
void print_from_bottom_to_top(std::ostream& s);

// A dynamic data structure must have a destructor
// that can be called to deallocate memory,
// when the data structure is not needed any more.
Cards::~Cards(){
    while ( top_ != nullptr ) {
       Card_data* item_to_be_released = top_;
       top_ = top_->next;

       delete item_to_be_released;
    }
}
