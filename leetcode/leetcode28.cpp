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

int strStr(string haystack, string needle) {
    return haystack.find(needle);
}

int main() {
    cout << strStr("hello", "ll") << " res:2" << endl;
    cout << strStr("aaaa", "aab") << " res:-1" << endl;
    cout << strStr("aaaa", "bba") << " res:-1" << endl;
}