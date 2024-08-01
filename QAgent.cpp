QBird::QBird(double l, double d, double e){
    for (int i = 0; i < table.size(); i++){
        for (int j = 0; j < table[0].size(); j++){
            for (int k = 0; k < table[0][0].size(); k++){
                table[i][j][k] = rand()%11-5; //randomize table values from -5 to 5
            }
        }
    }
    learnrate = l;
    discount = d;
    explore = e;
}

int QBird::nextAction(int x, int y){
    //this breaks it somehow?
    // if ((rand() % 11)/10.0 > explore){
    //     return rand() % 2;
    // }

    if (rand() > int(explore*32767)){
        return rand() % 2;
    }

    auto e = table[y][x];
    //something should be done to account for bird velocity to make the ai way better
    //perhaps some interpolation of the difference between the 2 actions idk
    if (e[1] > e[0]) return 1;
    return 0;
}

void QBird::learn(int prev[2], int cur[2], int reward, int a){
    double dif = reward + (*max_element(table[cur[1]][cur[0]].begin(), table[cur[1]][cur[0]].end())*discount) - table[prev[1]][prev[0]][a];
    table[prev[1]][prev[0]][a] += dif * learnrate;
}