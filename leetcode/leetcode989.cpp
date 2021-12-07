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

class Solution {
public:
    vector<int> addToArrayForm(vector<int> &num, int k) {
        vector<int> num2;
        while (k) {
            num2.push_back(k % 10);
            k /= 10;
        }
        reverse(num.begin(), num.end());
        vector<int> num3;
        int len = max(num.size(), num2.size());
        int carry = 0;
        for (int i = 0; i < len; ++i) {
            int x = i < num.size() ? num[i] : 0;
            int y = i < num2.size() ? num2[i] : 0;
            int sum = x + y + carry;
            num3.push_back(sum % 10);
            carry = sum / 10;
        }
        if(carry) num3.push_back(carry);
        reverse(num3.begin(), num3.end());
        return num3;
    }
};

int main(){
    Solution s;
    vector<int> v1 = {1,2,0,0};
    auto res = s.addToArrayForm(v1, 34) ;
    print(res);

}