#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

//0多优先
bool cmp0(string &str1, string &str2) {
    int l1 = str1.size(), l2 = str2.size();
    if (l1 != l2)
        return l1 < l2;
    int cnt1 = count(str1.begin(), str1.end(), '0');
    int cnt2 = count(str2.begin(), str2.end(), '0');
    return cnt1 > cnt2;
}

// 1多优先
bool cmp1(string &str1, string &str2) {
    int l1 = str1.size(), l2 = str2.size();
    if (l1 != l2)
        return l1 < l2;
    int cnt1 = count(str1.begin(), str1.end(), '1');
    int cnt2 = count(str2.begin(), str2.end(), '1');
    return cnt1 > cnt2;
}

// 抛开距离，0优先
bool cmp3(string &str1, string &str2) {
    int cnt1 = count(str1.begin(), str1.end(), '0');
    int cnt2 = count(str2.begin(), str2.end(), '0');
    return cnt1 < cnt2;
}
// 抛开距离，1优先
bool cmp4(string &str1, string &str2) {
    int cnt1 = count(str1.begin(), str1.end(), '1');
    int cnt2 = count(str2.begin(), str2.end(), '1');
    return cnt1 < cnt2;
}

//void dfs(vector<string> &strs, int m, int n, int step, int &num) {
//    return;
//}

int findMaxForm(vector<string> &strs, int m, int n) {
    int maxcnt = 0;
    int m1 = m, n1 = n;
    // 按距离计算
    sort(strs.begin(), strs.end(), cmp0);
    int cnt = 0;
    for (auto str : strs) {
        int s = str.size();
        int zero = count(str.begin(), str.end(), '0');
        int one = s - zero;
        if (m + n < s || zero > m || one > n){
            continue;
        }
        m -= zero;
        n -= one;
        cnt++;
    }
    maxcnt = max(cnt, maxcnt);
    m = m1, n = n1;
    sort(strs.begin(), strs.end(), cmp3);
    cnt = 0;
    for (auto str : strs) {
        int s = str.size();
        int zero = count(str.begin(), str.end(), '0');
        int one = s - zero;
        if (m + n < s || zero > m || one > n){
            continue;
        }
        m -= zero;
        n -= one;
        cnt++;
    }
    maxcnt = max(cnt, maxcnt);
    // 不按距离计算
    m = m1, n = n1;
    sort(strs.begin(), strs.end(), cmp4);
    cnt = 0;
    for (auto str : strs) {
        int s = str.size();
        int zero = count(str.begin(), str.end(), '0');
        int one = s - zero;
        if (m + n < s || zero > m || one > n){
            continue;
        }
        m -= zero;
        n -= one;
        cnt++;
    }
    maxcnt = max(cnt, maxcnt);
    m = m1, n = n1;
    sort(strs.begin(), strs.end(), cmp3);
    cnt = 0;
    for (auto str : strs) {
        int s = str.size();
        int zero = count(str.begin(), str.end(), '0');
        int one = s - zero;
        if (m + n < s || zero > m || one > n){
            continue;
        }
        m -= zero;
        n -= one;
        cnt++;
    }
    maxcnt = max(cnt, maxcnt);
    return maxcnt;
}

template<typename T>
void print(vector<T> &vec) {
    for (auto v : vec)
        cout << v << " ";
    cout << endl;
}

int main() {
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
//    sort(strs.begin(), strs.end(), cmp0);
//    print(strs);
    cout << findMaxForm(strs, 5, 3) << endl;
    vector<string> strs2 = {"10", "0", "1"};
    cout << findMaxForm(strs2, 1, 1) << endl;
    vector<string> strs3 = {"111", "1000", "1000", "1000"};
    cout << findMaxForm(strs3, 9, 3) << endl;
//    sort(strs3.begin(), strs3.end(), cmp4);
//    print(strs3);
    vector<string> strs4 = {"1100", "100000", "011111"};
    cout << findMaxForm(strs4, 6, 6) << endl;
}