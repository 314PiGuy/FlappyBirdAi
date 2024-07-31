#include "bird.hpp"


Bird::Bird(double s){
    //positions the bird with its center at 25 100
    pos[0] = 25-s/2;
    pos[1] = 100-s/2;
    vy = 0;
    size = s;
}

void Bird::flap(){
    //sets its velocity
    vy = 8.0;
}

void Bird::move(){
    //messed around with these numbers until i got what resembled the game physics the most
    pos[1] -= vy*0.2;
    vy -= 1*0.2;
}

void Bird::reset(){
    //move bird to original pos and reset velocity
    pos[0] = 25-size/2;
    pos[1] = 100-size/2;
    vy = 0;
}
