#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <array>
#include <memory>
#include <regex>
#include <thread>
#include <atomic>
#include <future>
#include <deque>


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

bool areOccurrencesEqual(string s) {
    unordered_map<char, int>um;
    for(auto& str : s){
        um[str]++;
    }
    int cnt = 0;
    for(auto&[k, v] : um){
        if(cnt == 0) {
            cnt = v;
            continue;
        }
        if(cnt != v) return false;
    }
    return true;
}