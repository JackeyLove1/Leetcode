#include <bits/stdc++.h>
using namespace std;
const int N = 2020;
struct PalindromesAutomaton
{
    int tot,last,n,link[N],len[N],trans[N][26],slink[N],dif[N],s[N];
    inline void Init(void)
    {
        memset( trans , 0 , sizeof trans );
        memset( len , 0 , sizeof len );
        memset( link , 0 , sizeof link );
        len[ last = 0 ] = 0 , link[0] = 1;
        s[ n = 0 ] = len[1] = -1 , tot = 1;
    }
    inline void Extend(int c)
    {
        int p = last; s[++n] = c;
        while ( s[n] != s[ n - len[p] - 1 ] ) p = link[p];
        if ( trans[p][c] == 0 )
        {
            int cur = ++tot , q = link[p];
            len[cur] = len[p] + 2;
            while ( s[n] != s[ n - len[q] - 1 ] ) q = link[q];
            link[cur] = trans[q][c] , trans[p][c] = cur;
            dif[cur] = len[cur] - len[ link[cur] ];
            if ( dif[cur] != dif[ link[cur] ] ) slink[cur] = link[cur];
            else slink[cur] = slink[ link[cur] ];
        }
        last = trans[p][c];
    }
};
PalindromesAutomaton T;
int Case,n,f[N],g[N]; char s[N];
int main(void)
{
    scanf( "%d" , &Case );
    while ( Case --> 0 )
    {
        scanf( "%s" , s+1 );
        T.Init() , n = strlen( s + 1 );
        memset( f , 0x3f , sizeof f );
        memset( g , 0x3f , sizeof g );
        f[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            T.Extend( s[i] - 'a' );
            for (int j = T.last; j; j = T.slink[j])
            {
                g[j] = f[ i - T.len[T.slink[j]] - T.dif[j] ];
                if ( T.slink[j] ^ T.link[j] ) g[j] = min( g[j] , g[T.link[j]] );
                f[i] = min( f[i] , g[j] + 1 );
            }
        }
        printf( "%d\n" , f[n] );
    }
    return 0;
}
