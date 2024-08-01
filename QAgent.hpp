#include <array>
#include <algorithm>

using namespace std;

class QBird{
    private:
        double learnrate;
        double discount;
        double explore;
    public:
        array<array<array<float, 2>, 112>, 400> table;//the q table will use integer values of the x and y distance between the bird and center of next pipe gap
        QBird(double learnrate, double discount, double explore);
        int nextAction(int x, int y);
        //learning algorithm should take the current and previous state and the reward and action taken in order to update the qtable of the previous state action i think
};