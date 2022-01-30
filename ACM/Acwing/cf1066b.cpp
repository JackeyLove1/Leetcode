#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int MAXN=2e5+7;
typedef long long ll;
typedef pair<int,int> PII;
int n,m,r,d,a[MAXN],h;
int main()
{
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int pre=0,last=0,ans=0;
    for(int i=1;i<=n;i++)
    {
        if(last>i)
            continue;
        int mk=0;
        for(int j=i+r-1;j>=max(1,i-r+1);j--)
        {
            if(a[j])
            {
                mk=1;
                ans++;
                last=j+r;
//                printf("%d\n",j);
                break;
            }
        }
        if(!mk)
            return 0*printf("-1\n");
    }
    printf("%d\n",ans);
    return 0;
}
