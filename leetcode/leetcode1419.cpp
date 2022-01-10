#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution1 {
public:
    int minNumberOfFrogs(const string &croakOfFrogs) {
        if (croakOfFrogs.empty() || croakOfFrogs[0] != 'c') return -1;
        vector<char> res;
        for (auto &ch : croakOfFrogs) {
            bool flag = false;
            if (ch == 'c') {
                for (auto &c : res) {
                    if (c == 'k') {
                        c = 'c';
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;
                res.push_back('c');
            } else if (ch == 'r') {
                for (auto &c : res) {
                    if (c == 'c') {
                        c = 'r';
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;
                return -1;
            } else if (ch == 'o') {
                for (auto &c : res) {
                    if (c == 'r') {
                        c = 'o';
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;
                return -1;
            } else if (ch == 'a') {
                for (auto &c : res) {
                    if (c == 'o') {
                        c = 'a';
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;
                return -1;
            } else if (ch == 'k') {
                for (auto &c : res) {
                    if (c == 'a') {
                        c = 'k';
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;
                return -1;
            } else {
                return -1;
            }
        }
        for (const auto ch : res) {
            if (ch != 'k') return -1;
        }
        return res.size();
    }
};

class Solution {
public:
    int minNumberOfFrogs(const string &croakOfFrogs) {
        if (croakOfFrogs.empty() || croakOfFrogs[0] != 'c') return -1;
        vector<char> res;
        unordered_map<char, int> um;
        for (auto &ch : croakOfFrogs) {
            bool flag = false;
            if (ch == 'c') {
                if (um.count('k') > 0) {
                    um['k']--;
                    um['c']++;
                    flag = true;
                }
                if (flag) continue;
                um['c']++;
            } else if (ch == 'r') {
                if (um.count('c') > 0) {
                    um['c']--;
                    um['r']++;
                    flag = true;
                }
                if (flag) continue;
                return -1;
            } else if (ch == 'o') {
                if (um.count('r') > 0) {
                    um['r']--;
                    um['o']++;
                    flag = true;
                }
                if (flag) continue;
                return -1;
            } else if (ch == 'a') {
                if (um.count('o') > 0) {
                    um['o']--;
                    um['a']++;
                    flag = true;
                }
                if (flag) continue;
                return -1;
            } else if (ch == 'k') {
                if (um.count('a') > 0) {
                    um['a']--;
                    um['k']++;
                    flag = true;
                }
                if (flag) continue;
                return -1;
            } else {
                return -1;
            }
        }

        for (const auto&[k, v] : um) {
            cout << "k: " << k << " v: " << v << endl;
            if (k != 'k' && um[k] != 0)
                return -1;
        }

        return um['k'];
    }
};


int main() {
    Solution s;
    cout << s.minNumberOfFrogs("croakcroak") << " res: 1" << endl;
    cout << s.minNumberOfFrogs("crcoakroak") << " res: 2" << endl;
    cout << s.minNumberOfFrogs("croakcrook") << " res; -1" << endl;
}