class Solution {
public:
    int calculate(string s) {
    int x = 1, y = 0;
    for (auto ch : s) {
        if (ch == 'A')
            x = x * 2 + y;
        else
            y = 2 * y + x;
    }
    return x + y;
}
};