// 时间复杂度O(NlogN)
vector<int>factor[N];
void get_factors(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n / i; ++j){
            factor[i*j].push_back(i);
        }
    }
}

