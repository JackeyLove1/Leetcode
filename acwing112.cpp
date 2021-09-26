#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<double, double> PDD;
const int N = 1010;
const double eps = 1e-6, INF = 1e10;

int n, d;
PDD seg[N];

int main()
{
    cin >> n >> d;

    bool success = true;

    for (int i = 0; i < n; i ++ )
    {
        int x, y;
        cin >> x >> y;
        if (y > d)
        {
            success = false;
            break;
        }
        auto len = sqrt(d * d - y * y);
        seg[i] = {x + len, x - len};
    }

    if (!success) puts("-1");
    else
    {
        sort(seg, seg + n);
        int res = 0;
        double last = -INF;
        for (int i = 0; i < n; i ++ )
        {
            if (seg[i].second > last + eps)
            {
                res ++ ;
                last = seg[i].first;
            }
        }
        cout << res << endl;
    }
    return 0;
}
