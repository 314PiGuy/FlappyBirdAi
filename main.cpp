#include <SFML/Graphics.hpp>
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
    RectangleShape bird(Vector2f(bird.size, bird.size));
    bird.setPosition(Vector2f(bird.pos[0], bird.pos[1]));
    bird.setFillColor(Color::Yellow);
    rects.push_back(bird);
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
    cout << "Score: " << score << "\n";
    score = 0
}


int main(){

    srand(time(0));
    
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

        //flap when space pressed at maximum once every 30 cycles
        if (Keyboard::isKeyPressed(Keyboard::Space) && cooldown == 0){
            bird.flap();
            cooldown = 30;
        }

        //this makes a pipe every 112 pixels idk why 112 it looks right i suppose
        if (spawnPipeCountdown == 0){
            pipes.push_back(Pipe());
            spawnPipeCountdown = 112;
        }

        move();
        if (birdDown()){
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
