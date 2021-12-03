#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;


using PII = pair<int, int>;

int minDistance(string word1, string word2) {
    const int INF = 1e9;
    int n = word1.size(), m = word2.size();
    int len = max(n, m) + 3;
    word1 = " " + word1;
    word2 = " " + word2;
    vector<vector<int>>f(len, vector<int>(len, INF));
    f[0][0] = 0;
    for(int i = 0; i <= n; i++) f[i][0] = i;
    for(int j = 0; j <= m; j++) f[0][j] = j;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            f[i][j] = min(f[i-1][j], f[i][j-1]) + 1;
            if(word1[i] == word2[j]){
                f[i][j] = min(f[i][j], f[i-1][j-1]);
            }else{
                f[i][j] = min(f[i][j], f[i-1][j-1] + 1);
            }
        }
    }
    return f[n][m];
}

int main(){
    string word1 = "horse", word2 = "ros";
    cout << minDistance(word1, word2) << endl;
}