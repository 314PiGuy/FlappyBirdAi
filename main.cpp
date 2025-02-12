#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "bird.hpp"
#include "pipe.hpp"
#include "QAgent.hpp"


using namespace std;
using namespace sf;

int cooldown = 0;
Bird bird = Bird(10); //bird class should have a flap and move method and takes the hitbox length in constructor
vector<Pipe> pipes; //pipe class represents the pipe obstacle and there will be a vector of the pipes on screen. the pipes should have a move method to move them on the screen
int score = 0;

int spawnPipeCountdown = 0; // use this to time when to add a new pipe
int nextPipe = 0; //index of the pipe in front of the bird

bool birdDown(){
    //check collisions with pipe hitboxes and top/bottom
    if (bird.pos[1] < 0 || bird.pos[1]+bird.size > 200) return true;
    Pipe p = pipes[nextPipe];
    if ( (bird.pos[0] > p.x && bird.pos[0] < p.x+p.width) || (bird.pos[0]+bird.size > p.x && bird.pos[0]+bird.size < p.x+p.width) ){
        if (bird.pos[1] < p.y[0] || bird.pos[1] + bird.size > p.y[1]){ 
            return true; 
        }
    }
    return false;
}


vector<RectangleShape> createScene(){
    vector<RectangleShape> rects;
    RectangleShape b(Vector2f(bird.size, bird.size));
    b.setPosition(Vector2f(bird.pos[0], bird.pos[1]));
    b.setFillColor(Color::Yellow);
    rects.push_back(b);
    //a rectangle to represent the bird

    int n = 0;
    for (Pipe p: pipes){
        //make a rectangle for the top and bottom pipe for each pipe object
        RectangleShape t(Vector2f(p.width, p.y[0]));
        t.setPosition(p.x, 0);
        t.setFillColor(Color::Red);
        RectangleShape b(Vector2f(p.width, 200-p.y[1]));
        b.setPosition(p.x, p.y[1]);
        b.setFillColor(Color::Red);
        rects.push_back(t);
        rects.push_back(b);
        n++;
    }

    return rects;
}

void move(){
    for (Pipe& p: pipes){
        p.move();
    }
    bird.move();
    spawnPipeCountdown--;
    if (pipes[nextPipe].x+pipes[nextPipe].width < bird.pos[0]){
        //the next pipe is the pipe after it when it passes the bird
        nextPipe++;
        score++;
    }
    if (pipes[0].x+pipes[0].width < 0){
        //remove pipes when they go off scree
        nextPipe--;
        pipes.erase(pipes.begin());
    }
    if (cooldown > 0) cooldown--;
}

void reset(){
    pipes.clear();
    spawnPipeCountdown = 0;
    cooldown = 0;
    bird.reset();
    score = 0;
}

void train(QBird& qbird){
    int flaps = 0;
    int action;
    int state0[3];
    int state1[3];
    Pipe next;
    int reward;
    while (flaps < 10000){
        if (spawnPipeCountdown == 0){
            pipes.push_back(Pipe());
            spawnPipeCountdown = 112;
        }
        if (cooldown > 0){
            move();
        }
        else{
            //get the integer values of position difference
            flaps++;
            next = pipes[nextPipe];
            state0[0] = int(next.x-bird.pos[0]);
            state0[1] = int(bird.pos[1]-(next.y[0]+next.y[1])/2+200);
            state0[2] = int(bird.vy > 0);
            action = qbird.nextAction(state0[0], state0[1], state0[2]);
            if (action == 1){
                bird.flap();
                cooldown = 20;
            }
            move();
            state1[0] = int(next.x-bird.pos[0]);
            state1[1] = int(bird.pos[1]-(next.y[0]+next.y[1])/2+200);
            state0[2] = int(bird.vy > 0);
            if (birdDown()) reward = -1000; //idk what values would yield what best results 
            else reward = 15;
            qbird.learn(state0, state1, reward, action);
            if (reward == -1000) reset();
        }
    }
    reset();
}


int main(){

    srand(time(0));

    QBird qbird = QBird(0.1, 0.4);

    for (int n = 0; n < 100000; n++) train(qbird);
    
    RenderWindow window(VideoMode(250, 200), "Bird Up");

    window.setFramerateLimit(100);
    //fps limit so it doesnt look choppy

    while (window.isOpen())
    {

        //event loop
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed){
                window.close();
            }
        }

        //flap when space pressed at maximum once every 20 cycles
        if (Keyboard::isKeyPressed(Keyboard::Space) && cooldown == 0){
            bird.flap();
            cooldown = 20;
        }

        //agent does the flapping
        if (cooldown == 0){
            Pipe next = pipes[nextPipe];
            int state0[3];
            state0[0] = int(next.x-bird.pos[0]);
            state0[1] = int(bird.pos[1]-(next.y[0]+next.y[1])/2+200);
            state0[2] = int(bird.vy > 0);
            if (qbird.nextAction(state0[0], state0[1], state0[2]) == 1){
                bird.flap();
                cooldown = 20;
            }
        }

        //this makes a pipe every 112 pixels idk why 112 it looks right i suppose
        if (spawnPipeCountdown == 0){
            pipes.push_back(Pipe());
            spawnPipeCountdown = 112;
        }

        move();
        if (birdDown()){
            cout << "Score: " << score << "\n";
            reset();
        }

        window.clear();

        //draw all rectangles that make up the current frame
        for (RectangleShape r: createScene()){
            window.draw(r);
        }
        
        window.display();
    }
    return 0;
}
