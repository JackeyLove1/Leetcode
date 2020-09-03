#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

bool canMakeArithmeticProgression(vector<int> &arr) {
    if (arr.size() == 0 || arr.size() == 1) return true;
    sort(arr.begin(), arr.end());
    int tmp = arr[0];
    int diff = arr[1] - arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if(arr[i] != tmp + diff * i)
            return false;
    }
    return true;
}