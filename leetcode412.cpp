class Solution {
public:
    vector<string> fizzBuzz(int n) {
        string s[] = {"Fizz", "Buzz", "FizzBuzz"};
        vector<string> res;
        for (int i = 1; i <= n; ++i) {
            if (i % 3 == 0 && i % 5 == 0) {
                res.emplace_back(s[2]);
            } else if (i % 3 == 0) {
                res.emplace_back(s[0]);
            } else if (i % 5 == 0) {
                res.emplace_back(s[1]);
            } else {
                res.emplace_back(to_string(i));
            }
        }
        return res;
    }
};