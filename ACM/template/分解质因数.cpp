#include<iostream>
using namespace std;

//若x是合数，那么它的最大的质因子不会超过sqrt(x)。
void divide(int x) {
    for (int i = 2; i <= x / i; i++) {  //枚举出所有不大于sqrt(x)的质因子。
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) {
                x /= i;
                s++;
            }
            cout << i << " " << s << endl;
        }
    }
    if (x != 1) cout << x << " " << 1 << endl;  //x中说明存在大于sqrt(x)的质因子，且质因子就是它本身。
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        divide(x);
    }
    return 0;
}