for (int i = 1; i <= n; ++i){
    for (int j = 1; j * i <= n; ++j){
        factor[i*j].push_back(j);
    }
}