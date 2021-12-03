#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int n, m;
constexpr int N = 200;
int g[N][N];
bool st[N][N];
const int debug = 0;

const int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};
void dfs(int x, int y){
    if(x >= n || x < 0 || y >= m || y < 0) return ;
    if(!g[x][y]) return ;
    g[x][y] = 0;
    for(int i = 0; i < 4; i++){
        dfs(x + dx[i], y + dy[i]);
    }
}

bool judge(int x, int y){
    int length = 0; // 计算矩形的长
    for(int i = y; i < m; i++){
        if(g[x][i]) ++length;
        else break;
    }
    int width = 0; // 计算矩形的高
    for(int i = x; i < n; i++){
        if(g[i][y]) ++width;
        else break;
    }
    bool flag = true;
    // 判断在这个长和高里面矩形是否有0
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            if(g[x + j][y + i]){
                // cout << "x+j: " << x +j <<" y+i " << y + i <<" g: "<<g[x + j][y + i]<< endl;
                continue;
            } 
            else{
                flag = false;
                break;
            };
        }
    }
    // 判断在这个长和宽的外围是否有1，有1则矩形不成立
    // up, skip
    // down
    if(x + width< n){
        for(int j = 0; j < length; j++){
            if(g[x+width][y + j]){
                flag = false;
                break;
            }
        }
    }
    // left
    if(y - 1 >= 0){
        for(int i = 0; i < width; i++){
            if(g[x+i][y-1]){
                flag = false;
                break;
            }
        }
    }
    // right
    if(y + length< m){
        for(int i = 0; i < width; i++){
            if(g[x+i][y+length]){
                flag = false;
                break;
            }
        }
    }
   if(debug){
        cout << "x: " << x <<" y: " << y << endl;
        cout << "l: " << length <<" w: " <<width<< endl;
        cout << "flag: " << flag << endl;
   }
    
    dfs(x, y);
    return flag;
}

int main() {
    cin.tie(0);
    cin >> n >> m; // 行，列
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> g[i][j];
        }
    }
    int res = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j]){
                if(judge(i, j)) ++res;
            }
        }
    }
    cout << res << endl;
    return 0;
}