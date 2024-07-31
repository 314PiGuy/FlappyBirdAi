#include <random>

class Pipe{    
    private:
    public:
    double width = 12;
    double x;
    double y[2]; // since there are 2 pipes with a gap in them i will just store the x value of pipes start and the y values of both ends
    Pipe();
    void move();
};
