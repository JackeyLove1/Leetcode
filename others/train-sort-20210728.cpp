#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void quick_sort(int l, int r, int q[]) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j){
        do i++;while (q[i] < x);
        do j--; while (q[j] > x);
        if(i < j) swap(q[i], q[j]);
    }
    quick_sort(l, j, q), quick_sort(j + 1, r, q);
}

constexpr int N = 1e6+100;
int tmp[N];
void merge_sort(int l, int  r, int q[]){
    if(l >= r) return ;
    int mid = l + r >> 1;
    merge_sort(l, mid, q), merge_sort(mid + 1, r, q);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <=r ){
        if(q[i] < q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];
    for(int i = l, j = 0; i <= r; i++, j++){
        q[i] = tmp[j];
    }
}


int main(){
    int q[] = {2,1,3,5,111,111,0,0,9,8,4,5,6,2,1};
    int l = 0, r = sizeof(q) / sizeof(q[0]) - 1;
    // quick_sort(l, r, q);
    merge_sort(l, r, q);
    for_each(q, q + r, [](int x){cout << x << " ";});
}