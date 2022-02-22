#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int exgcd(int a, int b, int &x, int &y)
{
    //a∗1+b∗0=gcd(a,b),x=1,y=0
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

int main()
{
    int a,b;
    cin >> a >> b;
    int x,y;
    exgcd(a,b,x,y);
    cout << (x%b+b)%b << endl;
    return 0;
}