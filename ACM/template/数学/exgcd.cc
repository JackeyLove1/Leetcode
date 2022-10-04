#include <bits/stdc++.h>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int res=exgcd(b,a%b,x,y);
    int t=x;x=y;y=t-(a/b)*y;
    return res;
}
/*
LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
*/
int main()
{
    int n,m;
    int x,y;
    cin>>m>>n;
    exgcd(m,n,x,y);
    while(x<0){
        x+=n;
    }
    cout<<x<<endl;
    return 0;
}