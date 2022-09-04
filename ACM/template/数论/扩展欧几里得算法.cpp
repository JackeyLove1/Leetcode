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

/*
int exgcd(int a, int b, int& x, int& y) {
    if(a < b) return exgcd(b, a, y, x);
    if(b == 0) {
        x = 1; y = 0;
        return a;
    } else {
        int x1;
        int d = exgcd(b, a % b, x1, x);
        y = x1 - a / b * x;
        return d;
    }
}

int exgcd(int a, int b, int& x, int& y) {
    if(a < b) return exgcd(b, a, y, x);
    int m = 0, n = 1;
    x = 1; y = 0;
    while(b != 0) {
        int d = a / b, t;
        t = m; m = x - d * t; x = t;
        t = n; n = y - d * t; y = t;
        t = a % b; a = b; b = t;
    }
    return a;
}

*/

// 中国剩余定理
using LL = long long;
const int N = 10;

int n;
int A[N], B[N];

void exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b) x = 1, y = 0;
    else
    {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

int main()
{
    scanf("%d", &n);

    LL M = 1;
    for (int i = 0; i < n; i ++ )
    {
        scanf("%d%d", &A[i], &B[i]);
        M *= A[i];
    }

    LL res = 0;
    for (int i = 0; i < n; i ++ )
    {
        LL Mi = M / A[i];
        LL ti, x;
        exgcd(Mi, A[i], ti, x);
        res += B[i] * Mi * ti;
    }

    cout << (res % M + M) % M << endl;

    return 0;
}