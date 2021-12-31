#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


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
    cout << "ending ... " << endl;
}
bool compare(int a, int b){
    if(a > b) return false;
    return true;
}
// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> res(1, 1);
        for(int i = 2; i <= N; i++){
            int l = 0, r = res.size() - 1;
            while (l < r){
                int mid = (l + r + 1) >> 1;
                if(compare(res[mid], i)) l = mid;
                else r = mid - 1;
            }
            res.push_back(i);
            // 往右移动
            for(int j = res.size() - 2; j > r; j--) swap(res[j], res[j+1]);
            if(compare(i, res[r])) swap(res[r], res[r+1]);
        }
        return res;
    }
};