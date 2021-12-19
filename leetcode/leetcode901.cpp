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


class StockSpanner {
    // 典型的单调栈
private:
    vector<int> prices;
    // 单调下降
    // 存放下标
    vector<int> st;
    int cnt;
public:
    StockSpanner():cnt(0) {

    }

    int next(int price) {
        if (prices.empty() || price < prices.back()) {
            st.push_back(cnt++);
            prices.push_back(price);
            return 1;
        }
        while (!st.empty() && prices[st.back()] <= price) {
            st.pop_back();
        }
        int dis = 0;
        if (st.empty()) {
            dis = cnt + 1;
        } else {
            dis = cnt - st.back();
        }
        st.push_back(cnt++);
        prices.push_back(price);
        return dis;
    }

    void clear(){
        cnt = 0;
        prices.clear();
        st.clear();
    }
};


int main(){
    StockSpanner s;
    cout << s.next(100) <<" res: 1"<< endl;
    cout << s.next(80) <<" res: 1"<< endl;
    cout << s.next(60) <<" res: 1"<< endl;
    cout << s.next(70) <<" res: 2"<< endl;
    cout << s.next(60) <<" res: 1"<< endl;
    cout << s.next(75) <<" res: 4"<< endl;
    cout << s.next(85) <<" res: 6"<< endl;

    s.clear();
    cout << s.next(31) << " res: 1"<< endl;
    cout << s.next(41) << " res: 2"<< endl;
    cout << s.next(48) << " res: 3"<< endl;
    cout << s.next(59) << " res: 4"<< endl;
}