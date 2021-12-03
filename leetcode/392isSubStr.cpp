#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool isSubsequence(string s, string t) {
    int m = s.size(), n = t.size();
    int i = 0, j = 0;
    while (i < m || j < n){
        if(i == m) return true;
        if(j == n) return false;
        if(s[i] == t[j]){
            i++;
            j++;
        } else
            j++;
    }
    return false;
}