#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std ;

const int N = 110 , M = 10010 , INF = 0x3f3f3f3f ;


typedef long long LL ;
int g[N][N] , d[N][N] ;
int pos[N][N] ; //记录当前状态由哪个点转移过来
vector<int> path ;
int n , m ;

//确保顺序正确
void dfs(int i , int j )    //i->j之间的路，输出i到j之间不包括i和j的道路
{
    int k = pos[i][j] ;

    if( k == 0 )    return ;    //如果是0，说明i,j之间不经过除i，j之外的其他点

    dfs(i , k); //i->newk
    path.push_back(k);  //k
    dfs(k , j); //newk->j

}

void get_path(int i , int j , int k )
{
    path.clear() ;
    path.push_back(k);  //边界
    path.push_back(i);
    dfs(i , j) ;    //k->i->j->k
    path.push_back(j);
}

int main()
{
    cin >> n >> m ; 

    memset(g , 0x3f ,sizeof g) ;
    for(int i = 0 ; i <= n ; i++ )  g[i][i] = 0 ;

    int a , b , c ;
    for(int i = 0 ; i < m ; i++ )
    {
        cin >> a >> b >> c ;
        g[a][b] = g[b][a] = min(g[a][b] , c) ;
    }

    memcpy(d , g , sizeof d );  //原图
    long long res = INF ;

    for(int k = 1 ; k <= n ; k++ )
    {
        //至少包含三个点的环所经过的点的最大编号是k
        for(int i = 1 ; i < k ; i++ )  //至少包含三个点，i，j，k不重合
            for(int j = i + 1 ; j < k ; j ++ )
            if(res > (LL)g[i][j] + d[i][k] + d[k][j] )
            {
                res = g[i][j] + d[i][k] + d[k][j] ;
                get_path(i , j , k) ;
            }

        for(int i = 1 ; i <= n ; i++ )
            for(int j = 1 ; j <= n ; j++ )
                if(g[i][j] > g[i][k] + g[k][j])
                {
                    g[i][j] = g[i][k] + g[k][j] ;
                    pos[i][j] = k ; 
                }
    }

    if(res == INF)  
        cout << "No solution." << endl;
    else
    {
        for(auto x : path)
            cout << x << ' ' ;
        cout << endl;
    }

    return 0;
}