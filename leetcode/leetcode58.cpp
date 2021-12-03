#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

int lengthOfLastWord(string s) {
    int res = 0;
    while (s.size() && s.back() == ' ') s.pop_back();
    for (auto &str : s) {
        if (str != ' ') res++;
        else res = 0;
    }
    return res;
}