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

int QBird::nextAction(int x, int y, double s){
    auto e = table[y][x];

    if (s < 0 && e[0] > e[1]){
        double dif = e[0]-e[1]+2;
        double percent = s/-19.6;
        e[1] += dif*percent;
    }
    
    if (e[1] > e[0]) return 1;
    return 0;
}

void QBird::learn(int prev[2], int cur[2], int reward, int a){
    double dif = reward + (*max_element(table[cur[1]][cur[0]].begin(), table[cur[1]][cur[0]].end())*discount) - table[prev[1]][prev[0]][a];
    table[prev[1]][prev[0]][a] += dif * learnrate;
}