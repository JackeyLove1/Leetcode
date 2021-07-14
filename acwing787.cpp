// 归并排序

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

const int N = 1e6 + 1;

int q[N], tmp[N];

void mergeSort(int q[], int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    mergeSort(q, l, mid);
    mergeSort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (q[i] < q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }

    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (int i = l, k = 0; i <= r; i++, k++) q[i] = tmp[k];

}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> q[i];
    mergeSort(q, 0, n - 1);
    for (int i = 0; i < n; i++) cout << q[i] << " ";
    cout << endl;
    return 0;
}