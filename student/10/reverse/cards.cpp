#include <iostream>
#include <memory>
#include "cards.hh"
using namespace std;


Cards::Cards(): top_( nullptr ){
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr){
        return false;
    }
    shared_ptr<Card_data> temp = top_->next;
    id = top_->data;
    top_ = temp;
    return true;
}

// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
void Cards::reverse(){
    if(top_ == nullptr){
        return;
    }
    if(top_->next == nullptr){
        return;
    }
    shared_ptr<Card_data> current = top_;
    shared_ptr<Card_data> next = top_->next;
    current->next = nullptr;
    shared_ptr<Card_data> previous;
    if(next->next != nullptr)
    {
        while(true){
            previous = current;
            current = next;
            next = next->next;
            // cout << previous->data << current->data << next->data << endl;
            current->next = previous;
            if(next->next == nullptr){

                break;

            }


        }
    }
    previous = current;
    current = next;
    // cout << previous->data << current->data << next->data << endl;
    current->next = previous;
    top_ = current;

}
