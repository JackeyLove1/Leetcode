#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

// 货币的非国家化
class Solution {
public:
    inline bool isnumber(const char &ch) {
        return ch >= '0' && ch <= '9';
    }

    int numDifferentIntegers(string word) {
        word = static_cast<const string>(word);
        set<string> res;
        auto checkWord = [&](string &cur) {
            if (!cur.empty()) {
                reverse(cur.begin(), cur.end());
                while (cur.size() > 1 && cur.back() == '0') {
                    cur.pop_back();
                }
                if (!cur.empty()) {
                    // reverse(cur.begin(), cur.end());
                    res.insert(move(cur));
                }
            }
        };
        string cur;
        for (auto &ch :word) {
            if (isnumber(ch)) {
                cur.push_back(ch);
            } else {
                if (!cur.empty()) {
                    checkWord(cur);
                }
                cur = "";
            }
        }
        if (!cur.empty()) checkWord(cur);
        return res.size();
    }
};

int main() {
    Solution s;
    // cout << s.numDifferentIntegers("a1b01c001") << endl;
    // cout << s.numDifferentIntegers("leet1234code234") << endl;
    // cout << s.numDifferentIntegers("167278959591294") << endl;
    cout << s.numDifferentIntegers("xtimt5kqkz9osexe56ezwwninly"
                                   "eeqsq5m99904os3ygs12t31n1et4uwzmt5k"
                                   "vv6teisobuxt10k33v1aaxysg4y8nsivxdp3"
                                   "fo9dr7x58m8uc4ofm41ai77u8cvzr5r3s97f5"
                                   "otns59ubqk57xwl00xsp9w2oodt6yxcbscloyr"
                                   "9c2su8gca1ly6rrjufm25luhxhesxwn7bk1as9na"
                                   "4cbabxk") << endl;
}