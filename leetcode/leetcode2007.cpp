#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <unordered_set>
#include <set>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        sort(changed.begin(),changed.end());
        queue<int> q;
        vector<int> res,empty;
        int n = changed.size();
        if(n%2)return empty;
        for(int i=0;i<n;i++){
            if(q.empty())
                q.push(changed[i]);
            else{
                if(q.front()*2 == changed[i]){
                    res.push_back(q.front());
                    q.pop();
                }
                else
                    q.push(changed[i]);
            }
        }
        if(!q.empty())
            return empty;
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {1, 3, 4, 2, 6, 8};
    auto res = s.findOriginalArray(v1);
    print(res);
    vector<int> v2 = {0, 3, 2, 4, 6, 0};
    auto r2 = s.findOriginalArray(v2);
    print(r2);
    vector<int> v3 = {2, 1, 2, 4, 2, 4};
    auto r3 = s.findOriginalArray(v3);
    print(r3);
}