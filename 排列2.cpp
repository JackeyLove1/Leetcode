#include <iostream>
#include <vector>

using namespace std;

#define SIZE 3

// 将容器的第i个元素与第j个元素交换位置
void swap(vector<int> &v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// 生成排列算法perm, 使用回溯法
// end不会达到
void perm(vector<int> &v, int start, int end, vector<vector<int>> &dst) {
    // get the adding rule
    if (start >= end)
        dst.push_back(v);
    else {
        for (int i = start; i < end; i++) {
            swap(v, start, i);
            perm(v, start + 1, end, dst);
            // 回溯
            swap(v, start, i);
        }
    }
}

// test function
int main() {
    vector<vector<int>> dst;
    vector<int> v;
    // v元素的初始化
    for (int i = 0; i < SIZE; i++) {
        v.push_back(i);
    }
    perm(v, 0, SIZE, dst);
    int cnt = 1;
    //输出结果
    for (auto d : dst) {
        cout << cnt++ << " : ";
        for (auto it : d) {
            cout << it << " ";
        }
        cout << endl;
    }
    return 0;
}