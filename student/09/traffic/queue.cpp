#include "queue.hh"
#include <iostream>
using namespace std;

// Implement the member functions of Queue here
// Constructor that initializes the attribute cycle_.
// (The other attibutes are initialized in the private part below.)
Queue::Queue(unsigned int cycle): cycle_(cycle){
}

// Destructor that deletes all the remaining vehicles from the queue.
Queue::~Queue(){
    while ( first_ != nullptr ) {
       Vehicle* item_to_be_released = first_;
       first_ = first_->next;

       delete item_to_be_released;
    }
}

// Inserts a vehicle, the register number of which is reg, to the queue.
void Queue::enqueue(string reg){
    if (is_green_){
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        return;
    }
    Vehicle* new_vehicle = new Vehicle{reg, nullptr};
    if (first_ == nullptr){
        first_ = new_vehicle;
        last_ = new_vehicle;
    }
    else{
        last_->next = new_vehicle;
        last_ = new_vehicle;
    }
}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light(){
    if (is_green_){
        is_green_ = false;
        print();
    }
    else{

        if (first_ == nullptr){
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
            is_green_ = true;
        }
        else{
            cout << "GREEN: Vehicle(s) ";
            deque_();
            cout << "can go on" << endl;
        }
    }
}

// Resets the attribute cycle_.
void Queue::reset_cycle(unsigned int cycle){
    cycle_ = cycle;
}

// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
void Queue::print(){
    if (is_green_){
        cout << "GREEN: ";
    }
    else{
        cout << "RED: ";
    }

    if(first_ == nullptr){
        cout << "No vehicles waiting in traffic lights" << endl;
    }
    else{
        cout << "Vehicle(s) ";
        Vehicle* next_vehicle = first_;
        while(next_vehicle != nullptr){
            cout << next_vehicle->reg_num << " ";
            next_vehicle = next_vehicle->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
}

void Queue::deque_(){
    Vehicle* current_vehicle = first_;
    for (unsigned int i = 0; i < cycle_; ++i){

        cout << current_vehicle->reg_num << " ";

        first_ = current_vehicle->next;
        delete current_vehicle;
        current_vehicle = first_;
        if (first_ == nullptr){
            return;
        }
    }
}
