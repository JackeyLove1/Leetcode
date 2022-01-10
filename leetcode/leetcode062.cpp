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

static constexpr int N = 1e5 + 10;

class Trie {
private:
    int tr[N][26], cnt[N], idx;
public:
    /** Initialize your data structure here. */
    Trie() : idx(0) {
        memset(tr, 0, sizeof tr);
        memset(cnt, 0, sizeof cnt);
    }

    /** Inserts a word into the trie. */
    void insert(const string &word) {
        int p = 0;
        for (const auto ch : word) {
            int u = ch - 'a';
            if (!tr[p][u]) tr[p][u] = ++idx;
            p = tr[p][u];
        }
        cnt[p]++;
    }

    /** Returns if the word is in the trie. */
    bool search(const string &word) {
        int p = 0;
        for (const auto ch : word) {
            int u = ch - 'a';
            if (!tr[p][u]) return false;
            p = tr[p][u];
        }
        return cnt[p] > 0;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string &prefix) {
        int p = 0;
        for (const auto ch : prefix) {
            int u = ch - 'a';
            if (!tr[p][u]) return false;
            p = tr[p][u];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
    Trie *tr = new Trie();
    tr->insert("apple");
    cout << tr->search("apple") << " res: 1" << endl;
    cout << tr->search("app") << " res: 0" << endl;
    cout << tr->startsWith("app") <<" res: 1" << endl;
}