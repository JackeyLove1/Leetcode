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

class MagicDictionary {
private:
    vector<string> dict;
    unordered_set<string> us;
public:
    /** Initialize your data structure here. */
    MagicDictionary() {

    }

    void buildDict(vector<string> dictionary) {
        dict = std::move(dictionary);
    }

    bool search(string searchWord) {
        searchWord = static_cast<const string>(searchWord);
        for (const auto &str : dict) {
            if (str.size() != searchWord.size()) continue;
            us.clear();
            for (int i = 0; i < str.size(); ++i) {
                if (str[i] != searchWord[i]) {
                    string tmp;
                    tmp += str[i];
                    tmp += searchWord[i];
                    // cout << "tmp: " << tmp << endl;
                    us.emplace(tmp);
                }
            }
            if (us.size() == 1) return true;
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

int main() {
    MagicDictionary s;
    s.buildDict({"a", "b", "ab"});
    cout << s.search("ba") << " res: 0" << endl;

}