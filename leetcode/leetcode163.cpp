#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    string getSmallestString(int n, int k) {
        string res;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 26; j >= 1; --j) {
                if (k >= j + i) {
                    res.push_back('a' + j - 1);
                    k -= j;
                    break;
                }
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    auto s = Solution();
    cout << s.getSmallestString(3, 27) << "  aay" << endl;
    cout << s.getSmallestString(5, 73) << "  aaszz" << endl;
}