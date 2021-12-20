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
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Foo {
private:
    atomic<int> cnt;
public:
    Foo() : cnt(0) {

    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        while (true) {
            if (cnt.load() % 3 == 0) {
                printFirst();
                cnt.fetch_add(1);
                return;
            }
        }
    }

    void second(function<void()> printSecond) {

        // printSecond() outputs "second". Do not change or remove this line.
        while (true) {
            if (cnt.load() % 3 == 1) {
                printSecond();
                cnt.fetch_add(1);
                return;
            }
        }
    }

    void third(function<void()> printThird) {

        // printThird() outputs "third". Do not change or remove this line.
        while (true) {
            if (cnt.load() % 3 == 2) {
                printThird();
                cnt.fetch_add(1);
                return;
            }
        }
    }
};