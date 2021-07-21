#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

vector<string> permutation(string s) {
    sort(s.begin(), s.end());
    vector<string> res;
    do {
        res.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
    return res;
}