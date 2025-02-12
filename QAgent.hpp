#include <array>
#include <algorithm>
#include <random>

using namespace std;

class QBird{
    private:
        double learnrate;
        double discount;
        double explore;
    public:
        array<array<array<array<float, 2>, 2>, 112>, 400> table;//the q table will use integer values of the x and y distance between the bird and center of next pipe gap
        QBird(double learnrate, double discount);
        int nextAction(int x, int y, int s);
        void learn(int prev[2], int cur[2], int reward, int a);
};