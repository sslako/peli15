#include "player.hh"
#include <string>

Player::Player(std::string name):
    name_(name) {
}

std::string Player::get_name(){
    return name_;
}

int Player::get_points(){
    return points_;
}

void Player::add_points(int points){
    points_ += points;
    if (points_ > 50){
        points_ = 25;
    }
}

bool Player::has_won(){
    if (points_ == 50){
        return 1;
    }
    else{
        return 0;
    }
}
