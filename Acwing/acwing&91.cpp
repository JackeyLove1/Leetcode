// 高精度加法

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

vector<int> add(vector<int> &A, vector<int> &B) {
    if (A.size() < B.size()) return add(B, A);
    int carry = 0;
    vector<int> C;
    for (int i = 0; i < B.size(); i++) {
        C.push_back((A[i] + B[i] + carry) % 10);
        carry = (carry + A[i] + B[i]) / 10;
    }
    for (int i = B.size(); i < A.size(); i++) {
        carry = (carry + A[i]) / 10;
        C.push_back((A[i] + carry) % 10);
        carry = (carry + A[i]) / 10;
    }
    if (carry) C.push_back(1);
    return C;
}

int main() {
    string a, b;
    cin >> a >> b;

    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    auto C = add(A, B);
    for (int i = C.size() - 1; i >= 0; i--) {
        cout << C[i];
    }
    cout << endl;
    return 0;
}