#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>
#include <stdlib.h>

using namespace std;

bool oneEditAway(string first, string second) {
    int m = first.size();
    int n = second.size();
    if (abs(m - n) > 1)
        return false;
    else if (m == n) {
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            if (first[i] == second[i])
                continue;
            else
                cnt++;
        }
        if (cnt <= 1) return true;
        else return false;
    } else if (m > n) {
        int i = 0, j = 0;
        int cnt = 0;
        while (i < m && j < n) {
            if (first[i] == second[j]) {
                i++;
                j++;
            } else {
                i++;
                cnt++;
            }
        }
        if (cnt > 1) return false;
        else return true;
    } else {
        int i = 0, j = 0;
        int cnt = 0;
        while (i < m && j < n) {
            if (first[i] == second[j]) {
                i++;
                j++;
            } else {
                j++;
                cnt++;
            }
        }
        if (cnt > 1) return false;
        else return true;
    }
    return false;
}