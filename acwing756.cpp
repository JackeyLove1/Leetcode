#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

const int N = 1e6 + 1;

int main(){
    int n, k;
    ios::sync_with_stdio(false);
    cin >> n >> k;
    vector<int>v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    cout << v[k-1] << endl;
    return 0;
}