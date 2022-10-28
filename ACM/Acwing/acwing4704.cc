#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

constexpr int N = 1e5 + 100;

int nums[N];

int main(){
    int n = read(), d = read();
    for(int i = 1; i <= n; ++i){
        nums[i] = read();
    }
    int res = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if (i != j && std::abs(nums[i] - nums[j]) <= d) ++res;
        }
    }
    cout << res << endl;
}