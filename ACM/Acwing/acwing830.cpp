#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

const int N = 1e5 + 100;

int q[N];

int main() {
    int n;
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 0; i < n; i++) cin >> q[i];

    vector<int> st;
    for (int i = 0; i < n; i++) {
        if (st.empty()) {
            st.push_back(q[i]);
            cout << -1 << " ";
        } else {
            if (q[i] > st.back()) {
                cout << st.back() << " ";
                st.push_back(q[i]);
            } else {
                while (!st.empty() && q[i] <= st.back())st.pop_back();
                if (st.empty()) {
                    cout << -1 << " ";
                } else {
                    cout << st.back() << " ";
                }
                st.push_back(q[i]);
            }
        }
    }

    return 0;
}