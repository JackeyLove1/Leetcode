#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int q[N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%d", &q[i]);

    while (m -- )
    {
        int x;
        scanf("%d", &x);
        // 查询起始位置
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (q[mid] >= x) r = mid;
            else l = mid + 1;
        }

        if (q[l] != x) cout << "-1 -1" << endl;
        else
        {
            cout << l << ' ';
            // 查询终点
            int l = 0, r = n - 1;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (q[mid] <= x) l = mid;
                else r = mid - 1;
            }

            cout << l << endl;
        }
    }

    return 0;
}


// 找到第一个小于等于目标值的数
for (int i = 1; i <= n; ++i) {
        int target = a[i] + k;
        int l = i + 1, r = n;
        while (l < r) {
            // find the first idx making a[idx] <= target
            int mid = l + r + 1 >> 1;
            if (a[mid] > target) r = mid - 1;
            else l = mid;
        }
        if (a[l] > a[i] && a[l] <= target) ++res;
}

// find left and right
int find1(int c)  // <= c 
{
    int l = 0, r = a.size() - 1;
    while (l < r) 
    {
        int mid = (l + r + 1) >> 1;
        if (a[mid].first <= c) l = mid;
        else r = mid - 1;
    }
    return l;
}

int find2(int c) // >= c
{
    int l = 0, r = a.size() - 1;
    while (l < r) 
    {
        int mid = l + r >> 1;
        if (a[mid].first >= c) r = mid;
        else l = mid + 1;
    }
    return l;
}


// <= c
int find_low(vector<int> &v, int l, int r, int target) {
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (v[mid] <= target) l = mid;
        else r = mid - 1;
    }
    return l;
}

// >= c
int find_high(vector<int> &v, int l, int r, int target) {
    while (l < r) {
        int mid = l + r >> 1;
        if (v[mid] >= target) r = mid;
        else l = mid + 1;
    }
    return l;
}