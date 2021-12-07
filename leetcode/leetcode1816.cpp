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
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
private:
    vector<string> split(const string &str, const string &delim) {
        vector<string> res;
        if (str.empty()) return res;
        //先将要切割的字符串从string类型转换为char*类型
        char *strs = new char[str.length() + 1];
        strcpy(strs, str.c_str());

        char *d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());

        char *p = strtok(strs, d);
        while (p) {
            string s = p; //分割得到的字符串转换为string类型
            res.emplace_back(s); //存入结果数组
            p = strtok(nullptr, d);
        }

        delete[] strs;
        delete[] d;
        return res;
    }

public:
    string truncateSentence(string s, int k) {
        const string delim = " ";
        vector<string> vec = split(s, delim);
        string res;
        for (int i = 0; i < k; ++i) {
            res += vec[i] + " ";
        }
        res.pop_back();
        return res;
    }
};

int main() {
    Solution s;
    auto res = s.truncateSentence("Hello how are you Contestant", 4);
    cout << res << endl;
}