void exgcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}


// d为最小正整数解
int exgcd(int a, int b, int &x, int &y){
    if (!b){ 
        //a∗1+b∗0=gcd(a,b),x=1,y=0 则返回的a就是gcd(a,b)
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x); // (x,y)交换为(y,x)往下传
    //当前层的x = x',当前层的y=y'-a/b*x'
    y -= a / b * x;

    return d; // a和b的最大公因数，我们所需要的是x和y
}

#include <iostream>
#include <algorithm>

using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
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
    int n;
    scanf("%d", &n);

    while (n -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        int x, y;
        exgcd(a, b, x, y);
        printf("%d %d\n", x, y);
    }

    return 0;
}