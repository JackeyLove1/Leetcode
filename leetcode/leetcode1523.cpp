#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

int countOdds(int low, int high) {
    int res = 0;
    for (int i = low; i <= high; i++) {
        if (i % 2 != 0)
            res++;
    }
    return res;
}