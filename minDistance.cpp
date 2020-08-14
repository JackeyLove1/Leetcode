#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string s1 = "horse";
string s2 = "ros";

int dp(int i, int j, int distance) {
    int l1 = s1.length(), l2 = s2.length();
    // cout << "l1 = " << l1 << "l2 = " << l2 << endl;
    if (i == l1 && j == l2)
        return distance;
    else if (i == l1 && j != l2)
        return distance + l2 - l1 + 1;
    else if (i != l1 && j == l2)
        return distance + l1 - l2 + 1;
    else {
        if (s1[i] == s2[j])
            return dp(i + 1, j + 1, distance);
        else {
            return min(
                    dp(i + 1, j, distance + 1),
                    min(
                            dp(i, j + 1, distance + 1),
                            dp(i + 1, j + 1, distance + 1)
                    )
            );
        }
    }
}


int main() {
    cout << "result is " << dp(0, 0, 0) << endl;
    return 0;
}