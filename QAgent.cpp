#include "QAgent.hpp"

QBird::QBird(double l, double d){
    for (int i = 0; i < table.size(); i++){
        for (int j = 0; j < table[0].size(); j++){
            for (int k = 0; k < table[0][0].size(); k++){
                for (int l = 0; l < table[0][0][0].size(); l++)
                    table[i][j][k][l] = 0;
            }
        }
    }
    learnrate = l;
    discount = d;
}

int QBird::nextAction(int x, int y, int s){
    auto e = table[y][x][s];

    
    if (e[1] > e[0]) return 1;
    return 0;
}

void QBird::learn(int prev[3], int cur[3], int reward, int a){
    double dif = reward + (*max_element(table[cur[1]][cur[0]][cur[2]].begin(), table[cur[1]][cur[0]][cur[2]].end())*discount) - table[prev[1]][prev[0]][prev[2]][a];
    table[prev[1]][prev[0]][prev[2]][a] += dif * learnrate;
}