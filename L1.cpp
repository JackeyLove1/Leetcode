#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

bool threeConsecutiveOdds(vector<int> &arr) {
    int n = arr.size();
    if (n < 3) return false;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if(arr[i] % 2 == 1){
            cnt++;
            if(cnt >= 3) return true;
        }
        else
            cnt = 0;
    }
    if(cnt >= 3) return true;
    else return false;
}