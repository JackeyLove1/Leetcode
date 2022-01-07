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

constexpr int N = 1e6 + 10;

class TimeMap {
private:
    using PSI = pair<string, int>;
    map<PSI, string> mp;
    unordered_map<string, vector<int>> km;
public:
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        mp[{key, timestamp}] = std::move(value);
        km[key].push_back(timestamp);
    }

    string get(string key, int timestamp) {
        // judge
        if (km.find(key) == km.end()) return "";
        // find prev timestamp
        const auto &vec = km[key];
        if (vec.front() > timestamp) return "";
        int prev;
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            // cout << *it << " " << timestamp << endl;
            if (*it <= timestamp) {
                prev = *it;
                break;
            }
        }
        // get value
        // cout << "key: " << key << " prev: " << prev << " res: " << mp[{key, prev}] << endl;
        // print(km[key]);
        return mp[{key, prev}];
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

int main() {
    TimeMap tm;
    tm.set("foo", "bar", 1);
    cout << tm.get("foo", 1) << " res: " << "bar" << endl;
    cout << tm.get("foo", 3) << " res: " << "bar" << endl;
    tm.set("foo", "bar2", 4);
    cout << tm.get("foo", 4) << " res: " << "bar2" << endl;
    cout << tm.get("foo", 5) << " res: " << "bar2" << endl;
}