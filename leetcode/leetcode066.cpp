#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class MapSum {
private:
    unordered_map<string, int> m;
public:
    /** Initialize your data structure here. */
    MapSum() {

    }

    void insert(string key, int val) {
        m[key] = val;
    }

    int sum(string prefix) {
        int res = 0;
        prefix = static_cast<const string>(prefix);
        for (auto&[k, v] : m) {
            /* C++ 20 starts_with
            if (k.starts_with(prefix)) {
                res += v;
            }
             */
            if(k.find(prefix) == 0){
                res += v;
            }
        }
        return res;
    }
};

int main() {
    MapSum s;
    s.insert("apple", 3);
    cout << s.sum("app") << endl;
}