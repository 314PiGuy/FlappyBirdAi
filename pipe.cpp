#include "pipe.hpp"

Pipe::Pipe(){
    x = 250;
    //randomly generate the bottom of the top pipe and the gap
    int gap = rand()%37+55;
    int topheight = rand()%(200-gap);
    y[0] = topheight;
    y[1] = topheight + gap;
}

void Pipe::move(){
    x -= 1;
}
