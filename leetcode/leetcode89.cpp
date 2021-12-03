#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

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
    cout << "ending .... " << endl;
}

vector<int> grayCode(int n) {
    vector<int> res;
    if (n == 0) return {0};
    if (n == 1) return {0, 1};
    auto tmp = grayCode(n - 1);
    res.assign(tmp.begin(), tmp.end());
    for (auto it = tmp.rbegin(); it != tmp.rend(); it++) {
        res.push_back((*it) + int(pow(2, n - 1)));
    }
    return res;
}

int main() {
    auto res = grayCode(3);
    print(res);
    // [0,1,3,2,6,7,5,4]
}