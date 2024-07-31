#include <SFML/Graphics.hpp>
#include <vector>


using namespace std;
using namespace sf;

int cooldown = 0;
Bird bird = Bird(10) //bird class should have a flap and move method and takes the hitbox length in constructor
vector<Pipe> pipes; //pipe class represents the pipe obstacle and there will be a vector of the pipes on screen. the pipes should have a move method to move them on the screen

vector<RectangleShape> createScene(){
//should return all the elements(bird and pipes) as rectangle shapes to be drawn in main window loop
}

void move(){
//should call the move methods of the bird and pipes
}


int main(){
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



        window.clear();

        //draw all rectangles that make up the current frame
        for (RectangleShape r: createScene()){
            window.draw(r);
        }
        
        window.display();
    }
    return 0;
}
