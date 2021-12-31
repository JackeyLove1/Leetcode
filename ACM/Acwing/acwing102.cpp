#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending ... " << endl;
}

const int N = 1e5 + 100;
int n, F;
double a[N], s[N];

bool check(double avg) {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i] - avg;
    double mins = 0;
    for (int k = F; k <= n; k++) {
        mins = min(mins, s[k - F]);
        if (s[k] >= mins) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> F;
    double l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        r = max(r, a[i]);
    }
    while (r - l > 1e-5) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << (int) (r * 1000) << endl;
    return 0;
}
