#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 2200;

class Solution {
public:
    bool closeStrings(const string &word1, const string &word2) {
        if (word1.size() != word2.size()) return false;
        unordered_map<char, int> u1, u2;
        vector<int> v1, v2;
        for (int i = 0; i < word1.size(); ++i) {
            ++u1[word1[i]], ++u2[word2[i]];
        }
        for (const auto&[k, v] : u1) {
            if(!u2.count(k)) return false;
            v1.push_back(v);
        }
        for (const auto&[k, v] : u2) {
            if(!u1.count(k)) return false;
            v2.push_back(v);
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());

        return v1.size() == v2.size() && equal(v1.begin(), v1.end(), v2.begin());
    }
};

int main(){
    auto s = Solution();
    cout << s.closeStrings("abbbzcf", "babzzcz") << endl;
    cout << s.closeStrings("uau", "ssx") <<" res: 0" << endl;
    return 0;
}

