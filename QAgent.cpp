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